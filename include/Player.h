#ifndef PLAYER_H
#define PLAYER_H

#include "Person.h"
#include <vector>

// Enum for player roles
enum class PlayerRole {
    BATSMAN,
    BOWLER,
    ALLROUNDER,
    WICKETKEEPER,
    WICKETKEEPER_BATSMAN,
    CAPTAIN,
    VICE_CAPTAIN
};

// Player statistics structure
struct PlayerStats {
    int matchesPlayed;
    int runsScored;
    int ballsFaced;
    int fours;
    int sixes;
    int wicketsTaken;
    int ballsBowled;
    int runsConceded;
    int catches;
    int stumpings;
    double battingAverage;
    double bowlingAverage;
    double strikeRate;
    double economy;
    
    PlayerStats() : matchesPlayed(0), runsScored(0), ballsFaced(0), 
                    fours(0), sixes(0), wicketsTaken(0), ballsBowled(0),
                    runsConceded(0), catches(0), stumpings(0),
                    battingAverage(0.0), bowlingAverage(0.0), 
                    strikeRate(0.0), economy(0.0) {}
};

class Player : public Person {
private:
    vector<PlayerRole> roles;
    int jerseyNumber;
    string battingStyle;  // Right-handed, Left-handed
    string bowlingStyle;  // Fast, Medium, Spin, Off-spin, Leg-spin
    PlayerStats stats;
    bool isPlaying;

public:
    Player() : Person(), jerseyNumber(0), battingStyle(""), 
               bowlingStyle(""), isPlaying(false) {}
    
    Player(string n, int a, string nat, string i, int jersey)
        : Person(n, a, nat, i), jerseyNumber(jersey), 
          battingStyle("Right-handed"), bowlingStyle(""), isPlaying(false) {}
    
    void addRole(PlayerRole role) {
        roles.push_back(role);
    }
    
    bool hasRole(PlayerRole role) const {
        for(const auto& r : roles) {
            if(r == role) return true;
        }
        return false;
    }
    
    bool isCaptain() const {
        return hasRole(PlayerRole::CAPTAIN);
    }
    
    void displayInfo() const override {
        cout << "Player: " << name << " (#" << jerseyNumber << ")" << endl;
        cout << "Age: " << age << " | Nationality: " << nationality << endl;
        cout << "Batting Style: " << battingStyle;
        if(!bowlingStyle.empty()) {
            cout << " | Bowling Style: " << bowlingStyle;
        }
        cout << endl;
        cout << "Roles: ";
        for(const auto& role : roles) {
            cout << getRoleString(role) << " ";
        }
        cout << endl;
    }
    
    string getRoleString(PlayerRole role) const {
        switch(role) {
            case PlayerRole::BATSMAN: return "Batsman";
            case PlayerRole::BOWLER: return "Bowler";
            case PlayerRole::ALLROUNDER: return "All-Rounder";
            case PlayerRole::WICKETKEEPER: return "Wicket-Keeper";
            case PlayerRole::WICKETKEEPER_BATSMAN: return "WK-Batsman";
            case PlayerRole::CAPTAIN: return "Captain";
            case PlayerRole::VICE_CAPTAIN: return "Vice-Captain";
            default: return "Unknown";
        }
    }
    
    // Getters and Setters
    int getJerseyNumber() const { return jerseyNumber; }
    string getBattingStyle() const { return battingStyle; }
    string getBowlingStyle() const { return bowlingStyle; }
    PlayerStats& getStats() { return stats; }
    const PlayerStats& getStats() const { return stats; }
    bool getIsPlaying() const { return isPlaying; }
    
    void setBattingStyle(string style) { battingStyle = style; }
    void setBowlingStyle(string style) { bowlingStyle = style; }
    void setIsPlaying(bool playing) { isPlaying = playing; }
    
    // Update statistics
    void updateBattingStats(int runs, int balls, int fours, int sixes) {
        stats.runsScored += runs;
        stats.ballsFaced += balls;
        stats.fours += fours;
        stats.sixes += sixes;
        if(stats.ballsFaced > 0) {
            stats.strikeRate = (stats.runsScored * 100.0) / stats.ballsFaced;
        }
    }
    
    void updateBowlingStats(int runs, int balls, int wickets) {
        stats.runsConceded += runs;
        stats.ballsBowled += balls;
        stats.wicketsTaken += wickets;
        if(stats.ballsBowled > 0) {
            stats.economy = (stats.runsConceded * 6.0) / stats.ballsBowled;
        }
        if(stats.wicketsTaken > 0) {
            stats.bowlingAverage = stats.runsConceded / (double)stats.wicketsTaken;
        }
    }
};

// Support Staff class
class SupportStaff : public Person {
private:
    string role; // Coach, Physio, Analyst, Manager, etc.
    
public:
    SupportStaff() : Person(), role("") {}
    
    SupportStaff(string n, int a, string nat, string i, string r)
        : Person(n, a, nat, i), role(r) {}
    
    void displayInfo() const override {
        cout << "Support Staff: " << name << " (" << role << ")" << endl;
        cout << "Nationality: " << nationality << endl;
    }
    
    string getRole() const { return role; }
};

#endif
