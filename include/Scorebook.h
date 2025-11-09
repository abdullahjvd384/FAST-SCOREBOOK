#ifndef SCOREBOOK_H
#define SCOREBOOK_H

#include "Match.h"
#include "Officials.h"
#include <map>
#include <vector>
#include <string>

// Structure to hold a score entry from a user
struct ScoreEntry {
    string userId;
    string userName;
    int overNumber;
    int ballNumber;
    BallOutcome outcome;
    int runs;
    int extras;
    WicketType wicketType;
    time_t timestamp;
    
    ScoreEntry() : userId(""), userName(""), overNumber(0), ballNumber(0),
                   outcome(BallOutcome::DOT_BALL), runs(0), extras(0),
                   wicketType(WicketType::NONE), timestamp(time(0)) {}
    
    ScoreEntry(string uid, string uname, int over, int ball, BallOutcome out, 
               int r, int ext, WicketType wType)
        : userId(uid), userName(uname), overNumber(over), ballNumber(ball),
          outcome(out), runs(r), extras(ext), wicketType(wType), timestamp(time(0)) {}
    
    bool operator==(const ScoreEntry& other) const {
        return (overNumber == other.overNumber && 
                ballNumber == other.ballNumber &&
                outcome == other.outcome &&
                runs == other.runs &&
                extras == other.extras &&
                wicketType == other.wicketType);
    }
    
    bool operator!=(const ScoreEntry& other) const {
        return !(*this == other);
    }
    
    void display() const {
        cout << "User: " << userName << " | Over: " << overNumber << "." << ballNumber;
        cout << " | Runs: " << runs;
        if(extras > 0) cout << " + " << extras << " extras";
        if(wicketType != WicketType::NONE) cout << " | WICKET";
        cout << endl;
    }
};

// Conflict structure to track disagreements
struct Conflict {
    int overNumber;
    int ballNumber;
    vector<ScoreEntry> conflictingEntries;
    bool isResolved;
    ScoreEntry resolvedEntry;
    string resolvedBy;
    time_t resolutionTime;
    
    Conflict() : overNumber(0), ballNumber(0), isResolved(false), 
                 resolvedBy(""), resolutionTime(0) {}
    
    Conflict(int over, int ball)
        : overNumber(over), ballNumber(ball), isResolved(false),
          resolvedBy(""), resolutionTime(0) {}
    
    void addEntry(const ScoreEntry& entry) {
        conflictingEntries.push_back(entry);
    }
    
    void resolve(const ScoreEntry& correctEntry, string supervisor) {
        resolvedEntry = correctEntry;
        resolvedBy = supervisor;
        isResolved = true;
        resolutionTime = time(0);
    }
    
    void displayConflict() const {
        cout << "\n*** CONFLICT DETECTED ***" << endl;
        cout << "Ball: " << overNumber << "." << ballNumber << endl;
        cout << "Conflicting Entries (" << conflictingEntries.size() << "):" << endl;
        for(size_t i = 0; i < conflictingEntries.size(); i++) {
            cout << "  Entry " << (i+1) << ": ";
            conflictingEntries[i].display();
        }
        
        if(isResolved) {
            cout << "\nRESOLVED by " << resolvedBy << endl;
            cout << "Correct Entry: ";
            resolvedEntry.display();
        } else {
            cout << "\nStatus: UNRESOLVED - Requires Supervisor intervention" << endl;
        }
    }
};

// Main Scorebook class
class Scorebook {
private:
    Match* match;
    map<string, vector<ScoreEntry>> userEntries; // userId -> their entries
    vector<Conflict> conflicts;
    Supervisor* supervisor;
    bool isNetworkSyncEnabled;
    int totalConflicts;
    int resolvedConflicts;
    
    // Helper function to generate ball key
    string getBallKey(int over, int ball) const {
        return to_string(over) + "." + to_string(ball);
    }
    
public:
    Scorebook() : match(nullptr), supervisor(nullptr), 
                  isNetworkSyncEnabled(true), totalConflicts(0), resolvedConflicts(0) {}
    
    Scorebook(Match* m, Supervisor* sup)
        : match(m), supervisor(sup), isNetworkSyncEnabled(true),
          totalConflicts(0), resolvedConflicts(0) {}
    
    void addScoreEntry(const ScoreEntry& entry) {
        userEntries[entry.userId].push_back(entry);
        checkForConflicts(entry);
    }
    
    void checkForConflicts(const ScoreEntry& newEntry) {
        string ballKey = getBallKey(newEntry.overNumber, newEntry.ballNumber);
        
        // Check if any existing entry for this ball differs
        vector<ScoreEntry> entriesForThisBall;
        
        for(auto& userPair : userEntries) {
            for(auto& entry : userPair.second) {
                if(entry.overNumber == newEntry.overNumber && 
                   entry.ballNumber == newEntry.ballNumber) {
                    entriesForThisBall.push_back(entry);
                }
            }
        }
        
        // If we have multiple entries, check if they agree
        if(entriesForThisBall.size() > 1) {
            bool hasConflict = false;
            for(size_t i = 1; i < entriesForThisBall.size(); i++) {
                if(entriesForThisBall[i] != entriesForThisBall[0]) {
                    hasConflict = true;
                    break;
                }
            }
            
            if(hasConflict) {
                // Check if conflict already exists
                bool conflictExists = false;
                for(auto& conflict : conflicts) {
                    if(conflict.overNumber == newEntry.overNumber &&
                       conflict.ballNumber == newEntry.ballNumber) {
                        conflictExists = true;
                        break;
                    }
                }
                
                if(!conflictExists) {
                    Conflict newConflict(newEntry.overNumber, newEntry.ballNumber);
                    for(auto& entry : entriesForThisBall) {
                        newConflict.addEntry(entry);
                    }
                    conflicts.push_back(newConflict);
                    totalConflicts++;
                    
                    cout << "\n!!! CONFLICT DETECTED for ball " 
                         << newEntry.overNumber << "." << newEntry.ballNumber << " !!!" << endl;
                }
            }
        }
    }
    
    void displayUnresolvedConflicts() const {
        cout << "\n========== UNRESOLVED CONFLICTS ==========" << endl;
        int unresolvedCount = 0;
        for(const auto& conflict : conflicts) {
            if(!conflict.isResolved) {
                conflict.displayConflict();
                unresolvedCount++;
            }
        }
        
        if(unresolvedCount == 0) {
            cout << "No unresolved conflicts!" << endl;
        }
        cout << "===========================================" << endl;
    }
    
    void displayAllConflicts() const {
        cout << "\n========== ALL CONFLICTS ==========" << endl;
        cout << "Total Conflicts: " << totalConflicts << endl;
        cout << "Resolved: " << resolvedConflicts << endl;
        cout << "Unresolved: " << (totalConflicts - resolvedConflicts) << endl;
        
        for(const auto& conflict : conflicts) {
            conflict.displayConflict();
            cout << "---" << endl;
        }
        cout << "===================================" << endl;
    }
    
    bool resolveConflict(int over, int ball, const ScoreEntry& correctEntry) {
        for(auto& conflict : conflicts) {
            if(conflict.overNumber == over && conflict.ballNumber == ball) {
                if(!conflict.isResolved) {
                    conflict.resolve(correctEntry, supervisor->getName());
                    supervisor->resolveConflict();
                    resolvedConflicts++;
                    
                    cout << "\n✓ Conflict for ball " << over << "." << ball 
                         << " resolved by " << supervisor->getName() << endl;
                    return true;
                }
            }
        }
        return false;
    }
    
    // Voting mechanism - majority wins
    ScoreEntry resolveByVoting(int over, int ball) {
        for(auto& conflict : conflicts) {
            if(conflict.overNumber == over && conflict.ballNumber == ball) {
                map<string, int> votes; // entry signature -> count
                
                for(const auto& entry : conflict.conflictingEntries) {
                    string signature = to_string(entry.runs) + "_" + 
                                     to_string(entry.extras) + "_" +
                                     to_string((int)entry.outcome);
                    votes[signature]++;
                }
                
                // Find entry with most votes
                int maxVotes = 0;
                ScoreEntry mostVotedEntry;
                for(const auto& entry : conflict.conflictingEntries) {
                    string signature = to_string(entry.runs) + "_" + 
                                     to_string(entry.extras) + "_" +
                                     to_string((int)entry.outcome);
                    if(votes[signature] > maxVotes) {
                        maxVotes = votes[signature];
                        mostVotedEntry = entry;
                    }
                }
                
                return mostVotedEntry;
            }
        }
        return ScoreEntry();
    }
    
    void displayScorebookSummary() const {
        cout << "\n========== SCOREBOOK SUMMARY ==========" << endl;
        cout << "Match: " << match->getMatchId() << endl;
        cout << "Supervisor: " << supervisor->getName() << endl;
        cout << "Network Sync: " << (isNetworkSyncEnabled ? "Enabled" : "Disabled") << endl;
        cout << "\nContributors: " << userEntries.size() << endl;
        for(const auto& userPair : userEntries) {
            cout << "  User: " << userPair.first 
                 << " - Entries: " << userPair.second.size() << endl;
        }
        
        cout << "\nConflict Statistics:" << endl;
        cout << "  Total Conflicts: " << totalConflicts << endl;
        cout << "  Resolved: " << resolvedConflicts << endl;
        cout << "  Pending: " << (totalConflicts - resolvedConflicts) << endl;
        cout << "========================================" << endl;
    }
    
    // Getters
    Match* getMatch() const { return match; }
    const vector<Conflict>& getConflicts() const { return conflicts; }
    int getTotalConflicts() const { return totalConflicts; }
    int getResolvedConflicts() const { return resolvedConflicts; }
    bool hasUnresolvedConflicts() const { 
        return resolvedConflicts < totalConflicts; 
    }
};

#endif
