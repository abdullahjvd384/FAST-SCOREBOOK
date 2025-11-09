#ifndef MATCH_H
#define MATCH_H

#include "Innings.h"
#include "Team.h"
#include "Venue.h"
#include "Officials.h"
#include <vector>
#include <ctime>

// Match Type enum
enum class MatchType {
    TEST_MATCH,
    ODI,
    T20,
    FIRST_CLASS,
    THREE_DAY,
    LIST_A
};

// Match Status enum
enum class MatchStatus {
    NOT_STARTED,
    IN_PROGRESS,
    INNINGS_BREAK,
    COMPLETED,
    ABANDONED,
    DRAWN
};

// Base Match class (Abstract)
class Match {
protected:
    string matchId;
    MatchType matchType;
    MatchStatus status;
    Team* team1;
    Team* team2;
    Venue* venue;
    vector<Innings*> allInnings;
    vector<Umpire*> umpires;
    vector<Commentator*> commentators;
    vector<BroadcastAgency*> broadcasters;
    string tossWinner;
    string tossDecision; // "bat" or "bowl"
    time_t matchDate;
    string result;
    Team* winner;
    int maxOversPerInnings;
    int maxInnings;
    
public:
    Match() : matchId(""), matchType(MatchType::ODI), status(MatchStatus::NOT_STARTED),
              team1(nullptr), team2(nullptr), venue(nullptr), 
              tossWinner(""), tossDecision(""), matchDate(time(0)),
              result(""), winner(nullptr), maxOversPerInnings(50), maxInnings(2) {}
    
    Match(string id, MatchType type, Team* t1, Team* t2, Venue* v)
        : matchId(id), matchType(type), status(MatchStatus::NOT_STARTED),
          team1(t1), team2(t2), venue(v), tossWinner(""), tossDecision(""),
          matchDate(time(0)), result(""), winner(nullptr),
          maxOversPerInnings(50), maxInnings(2) {}
    
    virtual ~Match() {
        for(auto innings : allInnings) {
            delete innings;
        }
    }
    
    // Pure virtual functions
    virtual void displayMatchInfo() const = 0;
    virtual bool checkInningsComplete(Innings* innings) const = 0;
    virtual void applyMatchRules() = 0;
    
    void setToss(string winnerTeam, string decision) {
        tossWinner = winnerTeam;
        tossDecision = decision;
    }
    
    void addUmpire(Umpire* umpire) {
        umpires.push_back(umpire);
    }
    
    void addCommentator(Commentator* comm) {
        commentators.push_back(comm);
    }
    
    void addBroadcaster(BroadcastAgency* agency) {
        broadcasters.push_back(agency);
    }
    
    Innings* startNewInnings(Team* batTeam, Team* bowlTeam) {
        int inningsNum = allInnings.size() + 1;
        Innings* newInnings = new Innings(inningsNum, batTeam, bowlTeam);
        allInnings.push_back(newInnings);
        status = MatchStatus::IN_PROGRESS;
        return newInnings;
    }
    
    void displayMatchSummary() const {
        cout << "\n========================================" << endl;
        cout << "       MATCH SUMMARY" << endl;
        cout << "========================================" << endl;
        cout << "Match ID: " << matchId << endl;
        cout << "Type: " << getMatchTypeString() << endl;
        cout << "Venue: " << venue->getStadiumName() << ", " << venue->getCity() << endl;
        cout << "Status: " << getStatusString() << endl;
        cout << "\nToss: " << tossWinner << " won and chose to " << tossDecision << endl;
        
        cout << "\n--- SCORECARD ---" << endl;
        for(auto innings : allInnings) {
            innings->displayInningsScore();
        }
        
        if(status == MatchStatus::COMPLETED) {
            cout << "\nResult: " << result << endl;
        }
        cout << "========================================" << endl;
    }
    
    void displayFullMatch() const {
        displayMatchSummary();
        cout << "\n\n--- BALL BY BALL COMMENTARY ---" << endl;
        for(auto innings : allInnings) {
            innings->displayFullInnings();
        }
    }
    
    string getMatchTypeString() const {
        switch(matchType) {
            case MatchType::TEST_MATCH: return "Test Match";
            case MatchType::ODI: return "One Day International";
            case MatchType::T20: return "T20 International";
            case MatchType::FIRST_CLASS: return "First Class Match";
            case MatchType::THREE_DAY: return "3-Day Match";
            case MatchType::LIST_A: return "List A Match";
            default: return "Unknown";
        }
    }
    
    string getStatusString() const {
        switch(status) {
            case MatchStatus::NOT_STARTED: return "Not Started";
            case MatchStatus::IN_PROGRESS: return "In Progress";
            case MatchStatus::INNINGS_BREAK: return "Innings Break";
            case MatchStatus::COMPLETED: return "Completed";
            case MatchStatus::ABANDONED: return "Abandoned";
            case MatchStatus::DRAWN: return "Drawn";
            default: return "Unknown";
        }
    }
    
    // Getters
    string getMatchId() const { return matchId; }
    MatchType getMatchType() const { return matchType; }
    MatchStatus getStatus() const { return status; }
    Team* getTeam1() const { return team1; }
    Team* getTeam2() const { return team2; }
    Venue* getVenue() const { return venue; }
    const vector<Innings*>& getAllInnings() const { return allInnings; }
    Team* getWinner() const { return winner; }
    int getMaxOversPerInnings() const { return maxOversPerInnings; }
    
    // Setters
    void setStatus(MatchStatus s) { status = s; }
    void setResult(string res) { result = res; }
    void setWinner(Team* w) { winner = w; }
};

// ODI Match class
class ODIMatch : public Match {
private:
    int powerplayOvers;
    
public:
    ODIMatch() : Match(), powerplayOvers(10) {
        matchType = MatchType::ODI;
        maxOversPerInnings = 50;
        maxInnings = 2;
    }
    
    ODIMatch(string id, Team* t1, Team* t2, Venue* v)
        : Match(id, MatchType::ODI, t1, t2, v), powerplayOvers(10) {
        maxOversPerInnings = 50;
        maxInnings = 2;
    }
    
    void displayMatchInfo() const override {
        cout << "\n===== ODI MATCH =====" << endl;
        cout << team1->getTeamName() << " vs " << team2->getTeamName() << endl;
        cout << "Venue: " << venue->getStadiumName() << endl;
        cout << "Max Overs: " << maxOversPerInnings << " per innings" << endl;
    }
    
    bool checkInningsComplete(Innings* innings) const override {
        if(innings->getIsCompleted()) return true;
        if(innings->getIsAllOut()) return true;
        if(innings->getOvers().size() >= maxOversPerInnings) {
            return true;
        }
        return false;
    }
    
    void applyMatchRules() override {
        // ODI specific rules
        // Powerplay restrictions, fielding restrictions, etc.
    }
};

// T20 Match class
class T20Match : public Match {
private:
    int powerplayOvers;
    int strategicTimeout;
    
public:
    T20Match() : Match(), powerplayOvers(6), strategicTimeout(2) {
        matchType = MatchType::T20;
        maxOversPerInnings = 20;
        maxInnings = 2;
    }
    
    T20Match(string id, Team* t1, Team* t2, Venue* v)
        : Match(id, MatchType::T20, t1, t2, v), powerplayOvers(6), strategicTimeout(2) {
        maxOversPerInnings = 20;
        maxInnings = 2;
    }
    
    void displayMatchInfo() const override {
        cout << "\n===== T20 MATCH =====" << endl;
        cout << team1->getTeamName() << " vs " << team2->getTeamName() << endl;
        cout << "Venue: " << venue->getStadiumName() << endl;
        cout << "Max Overs: " << maxOversPerInnings << " per innings" << endl;
    }
    
    bool checkInningsComplete(Innings* innings) const override {
        if(innings->getIsCompleted()) return true;
        if(innings->getIsAllOut()) return true;
        if(innings->getOvers().size() >= maxOversPerInnings) {
            return true;
        }
        return false;
    }
    
    void applyMatchRules() override {
        // T20 specific rules
    }
};

// Test Match class
class TestMatch : public Match {
private:
    int maxDays;
    int currentDay;
    int minOversPerDay;
    
public:
    TestMatch() : Match(), maxDays(5), currentDay(1), minOversPerDay(90) {
        matchType = MatchType::TEST_MATCH;
        maxOversPerInnings = 999; // Unlimited overs
        maxInnings = 4; // Each team plays 2 innings
    }
    
    TestMatch(string id, Team* t1, Team* t2, Venue* v)
        : Match(id, MatchType::TEST_MATCH, t1, t2, v), 
          maxDays(5), currentDay(1), minOversPerDay(90) {
        maxOversPerInnings = 999;
        maxInnings = 4;
    }
    
    void displayMatchInfo() const override {
        cout << "\n===== TEST MATCH =====" << endl;
        cout << team1->getTeamName() << " vs " << team2->getTeamName() << endl;
        cout << "Venue: " << venue->getStadiumName() << endl;
        cout << "Format: " << maxDays << " Day Test" << endl;
        cout << "Current Day: " << currentDay << endl;
    }
    
    bool checkInningsComplete(Innings* innings) const override {
        if(innings->getIsCompleted()) return true;
        if(innings->getIsAllOut()) return true;
        // In test match, captain can declare
        return false;
    }
    
    void applyMatchRules() override {
        // Test match specific rules
        // Follow-on, declaration, etc.
    }
    
    void declareInnings(Innings* innings) {
        innings->setCompleted(true);
        status = MatchStatus::INNINGS_BREAK;
    }
};

// First Class Match
class FirstClassMatch : public Match {
private:
    int maxDays;
    
public:
    FirstClassMatch() : Match(), maxDays(4) {
        matchType = MatchType::FIRST_CLASS;
        maxOversPerInnings = 999;
        maxInnings = 4;
    }
    
    FirstClassMatch(string id, Team* t1, Team* t2, Venue* v, int days = 4)
        : Match(id, MatchType::FIRST_CLASS, t1, t2, v), maxDays(days) {
        maxOversPerInnings = 999;
        maxInnings = 4;
    }
    
    void displayMatchInfo() const override {
        cout << "\n===== FIRST CLASS MATCH =====" << endl;
        cout << team1->getTeamName() << " vs " << team2->getTeamName() << endl;
        cout << "Venue: " << venue->getStadiumName() << endl;
        cout << "Format: " << maxDays << " Day Match" << endl;
    }
    
    bool checkInningsComplete(Innings* innings) const override {
        return innings->getIsCompleted() || innings->getIsAllOut();
    }
    
    void applyMatchRules() override {
        // First class match rules
    }
};

// Series class to group multiple matches
class Series {
private:
    string seriesName;
    string seriesType; // Bilateral, Tri-series, Tournament
    vector<Match*> matches;
    vector<Team*> participatingTeams;
    time_t startDate;
    time_t endDate;
    
public:
    Series() : seriesName(""), seriesType("Bilateral"), startDate(time(0)), endDate(time(0)) {}
    
    Series(string name, string type)
        : seriesName(name), seriesType(type), startDate(time(0)), endDate(time(0)) {}
    
    ~Series() {
        // Note: Matches should be managed carefully to avoid double deletion
    }
    
    void addMatch(Match* match) {
        matches.push_back(match);
    }
    
    void addTeam(Team* team) {
        participatingTeams.push_back(team);
    }
    
    void displaySeriesInfo() const {
        cout << "\n========== " << seriesName << " ==========" << endl;
        cout << "Type: " << seriesType << endl;
        cout << "Participating Teams: ";
        for(size_t i = 0; i < participatingTeams.size(); i++) {
            cout << participatingTeams[i]->getTeamName();
            if(i < participatingTeams.size() - 1) cout << ", ";
        }
        cout << endl;
        cout << "Total Matches: " << matches.size() << endl;
    }
    
    string getSeriesName() const { return seriesName; }
    const vector<Match*>& getMatches() const { return matches; }
};

#endif
