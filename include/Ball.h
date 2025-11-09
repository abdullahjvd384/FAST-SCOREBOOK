#ifndef BALL_H
#define BALL_H

#include "Player.h"
#include <string>
#include <ctime>

// Enum for ball outcomes
enum class BallOutcome {
    DOT_BALL,
    SINGLE,
    DOUBLE,
    TRIPLE,
    FOUR,
    SIX,
    WICKET,
    WIDE,
    NO_BALL,
    BYE,
    LEG_BYE,
    WICKET_AND_RUNS
};

// Enum for wicket types
enum class WicketType {
    NONE,
    BOWLED,
    CAUGHT,
    LBW,
    RUN_OUT,
    STUMPED,
    HIT_WICKET,
    CAUGHT_AND_BOWLED,
    CAUGHT_BEHIND,
    OBSTRUCTING_FIELD,
    HIT_BALL_TWICE,
    TIMED_OUT
};

class Ball {
private:
    int overNumber;
    int ballNumber; // 1-6 for regular balls
    Player* bowler;
    Player* batsman;
    Player* nonStriker;
    int runs;
    int extras;
    BallOutcome outcome;
    WicketType wicketType;
    Player* fielderInvolved; // For catches, run-outs
    bool isValid; // false for wides, no-balls
    string commentary;
    time_t timestamp;
    
public:
    Ball() : overNumber(0), ballNumber(0), bowler(nullptr), batsman(nullptr),
             nonStriker(nullptr), runs(0), extras(0), outcome(BallOutcome::DOT_BALL),
             wicketType(WicketType::NONE), fielderInvolved(nullptr), 
             isValid(true), commentary(""), timestamp(time(0)) {}
    
    Ball(int over, int ball, Player* bow, Player* bat, Player* nonStrk)
        : overNumber(over), ballNumber(ball), bowler(bow), batsman(bat),
          nonStriker(nonStrk), runs(0), extras(0), outcome(BallOutcome::DOT_BALL),
          wicketType(WicketType::NONE), fielderInvolved(nullptr),
          isValid(true), commentary(""), timestamp(time(0)) {}
    
    void recordBall(BallOutcome out, int r, int ext = 0) {
        outcome = out;
        runs = r;
        extras = ext;
        
        // Set validity
        if(outcome == BallOutcome::WIDE || outcome == BallOutcome::NO_BALL) {
            isValid = false;
        }
    }
    
    void recordWicket(WicketType type, Player* fielder = nullptr) {
        wicketType = type;
        fielderInvolved = fielder;
        outcome = BallOutcome::WICKET;
    }
    
    string getOutcomeString() const {
        switch(outcome) {
            case BallOutcome::DOT_BALL: return "Dot Ball";
            case BallOutcome::SINGLE: return "1 Run";
            case BallOutcome::DOUBLE: return "2 Runs";
            case BallOutcome::TRIPLE: return "3 Runs";
            case BallOutcome::FOUR: return "FOUR!";
            case BallOutcome::SIX: return "SIX!";
            case BallOutcome::WICKET: return "WICKET!";
            case BallOutcome::WIDE: return "Wide";
            case BallOutcome::NO_BALL: return "No Ball";
            case BallOutcome::BYE: return "Bye";
            case BallOutcome::LEG_BYE: return "Leg Bye";
            case BallOutcome::WICKET_AND_RUNS: return "Wicket + Runs";
            default: return "Unknown";
        }
    }
    
    string getWicketTypeString() const {
        switch(wicketType) {
            case WicketType::NONE: return "Not Out";
            case WicketType::BOWLED: return "Bowled";
            case WicketType::CAUGHT: return "Caught";
            case WicketType::LBW: return "LBW";
            case WicketType::RUN_OUT: return "Run Out";
            case WicketType::STUMPED: return "Stumped";
            case WicketType::HIT_WICKET: return "Hit Wicket";
            case WicketType::CAUGHT_AND_BOWLED: return "Caught & Bowled";
            case WicketType::CAUGHT_BEHIND: return "Caught Behind";
            default: return "Other";
        }
    }
    
    void displayBall() const {
        cout << overNumber << "." << ballNumber << " - "
             << bowler->getName() << " to " << batsman->getName() << ": ";
        
        if(wicketType != WicketType::NONE) {
            cout << "WICKET! " << batsman->getName() << " " << getWicketTypeString();
            if(wicketType == WicketType::BOWLED || wicketType == WicketType::CAUGHT_AND_BOWLED) {
                cout << " b " << bowler->getName();
            } else if(wicketType == WicketType::CAUGHT && fielderInvolved) {
                cout << " c " << fielderInvolved->getName() << " b " << bowler->getName();
            }
        } else {
            cout << getOutcomeString();
            if(runs > 0 || extras > 0) {
                cout << " (" << (runs + extras) << " runs)";
            }
        }
        
        if(!commentary.empty()) {
            cout << " - " << commentary;
        }
        cout << endl;
    }
    
    // Getters
    int getOverNumber() const { return overNumber; }
    int getBallNumber() const { return ballNumber; }
    Player* getBowler() const { return bowler; }
    Player* getBatsman() const { return batsman; }
    int getRuns() const { return runs; }
    int getExtras() const { return extras; }
    int getTotalRuns() const { return runs + extras; }
    BallOutcome getOutcome() const { return outcome; }
    WicketType getWicketType() const { return wicketType; }
    bool getIsValid() const { return isValid; }
    time_t getTimestamp() const { return timestamp; }
    
    // Setters
    void setCommentary(string comm) { commentary = comm; }
};

#endif
