#ifndef INNINGS_H
#define INNINGS_H

#include "Ball.h"
#include "Team.h"
#include <vector>

class Over {
private:
    int overNumber;
    Player* bowler;
    vector<Ball*> balls;
    int runsInOver;
    int wicketsInOver;
    bool isMaidenOver;
    
public:
    Over() : overNumber(0), bowler(nullptr), runsInOver(0), 
             wicketsInOver(0), isMaidenOver(false) {}
    
    Over(int num, Player* bow) 
        : overNumber(num), bowler(bow), runsInOver(0),
          wicketsInOver(0), isMaidenOver(false) {}
    
    ~Over() {
        for(auto ball : balls) {
            delete ball;
        }
    }
    
    void addBall(Ball* ball) {
        balls.push_back(ball);
        runsInOver += ball->getTotalRuns();
        if(ball->getWicketType() != WicketType::NONE) {
            wicketsInOver++;
        }
    }
    
    bool isComplete() const {
        int validBalls = 0;
        for(auto ball : balls) {
            if(ball->getIsValid()) validBalls++;
        }
        return validBalls >= 6;
    }
    
    void checkMaidenOver() {
        if(runsInOver == 0 && wicketsInOver == 0 && isComplete()) {
            isMaidenOver = true;
        }
    }
    
    void displayOver() const {
        cout << "\nOver " << overNumber << " (" << bowler->getName() << "): ";
        for(auto ball : balls) {
            if(ball->getWicketType() != WicketType::NONE) {
                cout << "W ";
            } else if(ball->getOutcome() == BallOutcome::WIDE) {
                cout << "Wd ";
            } else if(ball->getOutcome() == BallOutcome::NO_BALL) {
                cout << "Nb ";
            } else {
                cout << ball->getRuns() << " ";
            }
        }
        cout << " | " << runsInOver << " runs";
        if(isMaidenOver) cout << " (Maiden)";
        cout << endl;
    }
    
    // Getters
    int getOverNumber() const { return overNumber; }
    Player* getBowler() const { return bowler; }
    const vector<Ball*>& getBalls() const { return balls; }
    int getRunsInOver() const { return runsInOver; }
    int getWicketsInOver() const { return wicketsInOver; }
    bool getIsMaidenOver() const { return isMaidenOver; }
};

class Innings {
private:
    int inningsNumber; // 1, 2, 3, or 4
    Team* battingTeam;
    Team* bowlingTeam;
    vector<Over*> overs;
    Player* currentBatsman1;
    Player* currentBatsman2;
    bool striker1; // true if batsman1 is on strike
    int totalRuns;
    int totalWickets;
    int totalExtras;
    int wides;
    int noBalls;
    int byes;
    int legByes;
    bool isCompleted;
    bool isAllOut;
    
public:
    Innings() : inningsNumber(0), battingTeam(nullptr), bowlingTeam(nullptr),
                currentBatsman1(nullptr), currentBatsman2(nullptr), striker1(true),
                totalRuns(0), totalWickets(0), totalExtras(0), wides(0), noBalls(0),
                byes(0), legByes(0), isCompleted(false), isAllOut(false) {}
    
    Innings(int num, Team* batTeam, Team* bowlTeam)
        : inningsNumber(num), battingTeam(batTeam), bowlingTeam(bowlTeam),
          currentBatsman1(nullptr), currentBatsman2(nullptr), striker1(true),
          totalRuns(0), totalWickets(0), totalExtras(0), wides(0), noBalls(0),
          byes(0), legByes(0), isCompleted(false), isAllOut(false) {}
    
    ~Innings() {
        for(auto over : overs) {
            delete over;
        }
    }
    
    void startOver(Player* bowler) {
        int overNum = overs.size() + 1;
        Over* newOver = new Over(overNum, bowler);
        overs.push_back(newOver);
    }
    
    void recordBall(Ball* ball) {
        if(overs.empty()) return;
        
        Over* currentOver = overs.back();
        currentOver->addBall(ball);
        
        // Update innings statistics
        totalRuns += ball->getTotalRuns();
        
        if(ball->getOutcome() == BallOutcome::WIDE) {
            wides++;
            totalExtras++;
        } else if(ball->getOutcome() == BallOutcome::NO_BALL) {
            noBalls++;
            totalExtras++;
        } else if(ball->getOutcome() == BallOutcome::BYE) {
            byes += ball->getRuns();
            totalExtras += ball->getRuns();
        } else if(ball->getOutcome() == BallOutcome::LEG_BYE) {
            legByes += ball->getRuns();
            totalExtras += ball->getRuns();
        }
        
        if(ball->getWicketType() != WicketType::NONE) {
            totalWickets++;
            if(totalWickets >= 10) {
                isAllOut = true;
                isCompleted = true;
            }
        }
        
        // Change strike on odd runs (1, 3, 5)
        if(ball->getRuns() % 2 == 1 && ball->getIsValid()) {
            striker1 = !striker1;
        }
        
        // Change strike at end of over
        if(currentOver->isComplete()) {
            striker1 = !striker1;
        }
    }
    
    void setBatsmen(Player* bat1, Player* bat2) {
        currentBatsman1 = bat1;
        currentBatsman2 = bat2;
        striker1 = true;
    }
    
    Player* getStriker() {
        return striker1 ? currentBatsman1 : currentBatsman2;
    }
    
    Player* getNonStriker() {
        return striker1 ? currentBatsman2 : currentBatsman1;
    }
    
    void displayInningsScore() const {
        cout << "\n===== Innings " << inningsNumber << " =====" << endl;
        cout << battingTeam->getTeamName() << ": " << totalRuns << "/" << totalWickets;
        cout << " (" << overs.size() << " overs)" << endl;
        cout << "Extras: " << totalExtras << " (wd " << wides << ", nb " << noBalls 
             << ", b " << byes << ", lb " << legByes << ")" << endl;
    }
    
    void displayFullInnings() const {
        displayInningsScore();
        cout << "\nOver by Over:" << endl;
        for(auto over : overs) {
            over->displayOver();
        }
    }
    
    // Getters
    int getInningsNumber() const { return inningsNumber; }
    Team* getBattingTeam() const { return battingTeam; }
    Team* getBowlingTeam() const { return bowlingTeam; }
    int getTotalRuns() const { return totalRuns; }
    int getTotalWickets() const { return totalWickets; }
    int getTotalExtras() const { return totalExtras; }
    const vector<Over*>& getOvers() const { return overs; }
    bool getIsCompleted() const { return isCompleted; }
    bool getIsAllOut() const { return isAllOut; }
    double getCurrentRunRate() const {
        if(overs.empty()) return 0.0;
        double oversPlayed = overs.size();
        // Account for incomplete over
        if(!overs.back()->isComplete()) {
            int validBalls = 0;
            for(auto ball : overs.back()->getBalls()) {
                if(ball->getIsValid()) validBalls++;
            }
            oversPlayed = oversPlayed - 1 + (validBalls / 6.0);
        }
        return oversPlayed > 0 ? totalRuns / oversPlayed : 0.0;
    }
    
    void setCompleted(bool completed) { isCompleted = completed; }
};

#endif
