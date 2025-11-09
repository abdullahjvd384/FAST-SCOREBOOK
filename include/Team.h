#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include <vector>
#include <algorithm>

class Team {
private:
    string teamName;
    string country;
    vector<Player*> squad;
    vector<Player*> playingXI;
    vector<SupportStaff*> supportStaff;
    Player* captain;
    Player* viceCaptain;
    string teamColor;
    int worldRanking;
    
public:
    Team() : teamName(""), country(""), captain(nullptr), 
             viceCaptain(nullptr), teamColor(""), worldRanking(0) {}
    
    Team(string name, string ctry) 
        : teamName(name), country(ctry), captain(nullptr),
          viceCaptain(nullptr), teamColor(""), worldRanking(0) {}
    
    ~Team() {
        // Note: In a real system, use smart pointers or proper memory management
    }
    
    void addPlayer(Player* player) {
        squad.push_back(player);
    }
    
    void addToPlayingXI(Player* player) {
        if(playingXI.size() < 11) {
            playingXI.push_back(player);
            player->setIsPlaying(true);
        } else {
            cout << "Playing XI is full!" << endl;
        }
    }
    
    void addSupportStaff(SupportStaff* staff) {
        supportStaff.push_back(staff);
    }
    
    void setCaptain(Player* player) {
        if(captain) {
            // Remove captain role from previous captain
        }
        captain = player;
        player->addRole(PlayerRole::CAPTAIN);
    }
    
    void setViceCaptain(Player* player) {
        viceCaptain = player;
        player->addRole(PlayerRole::VICE_CAPTAIN);
    }
    
    Player* findPlayerByName(string name) {
        for(auto player : squad) {
            if(player->getName() == name) {
                return player;
            }
        }
        return nullptr;
    }
    
    void displayTeam() const {
        cout << "\n===== " << teamName << " (" << country << ") =====" << endl;
        cout << "World Ranking: " << worldRanking << endl;
        cout << "Captain: " << (captain ? captain->getName() : "Not assigned") << endl;
        cout << "\nPlaying XI:" << endl;
        for(size_t i = 0; i < playingXI.size(); i++) {
            cout << (i+1) << ". ";
            playingXI[i]->displayInfo();
            cout << endl;
        }
    }
    
    void displayFullSquad() const {
        cout << "\n===== Full Squad: " << teamName << " =====" << endl;
        for(size_t i = 0; i < squad.size(); i++) {
            cout << (i+1) << ". ";
            squad[i]->displayInfo();
            cout << endl;
        }
        
        cout << "\nSupport Staff:" << endl;
        for(auto staff : supportStaff) {
            staff->displayInfo();
        }
    }
    
    // Getters
    string getTeamName() const { return teamName; }
    string getCountry() const { return country; }
    const vector<Player*>& getPlayingXI() const { return playingXI; }
    const vector<Player*>& getSquad() const { return squad; }
    Player* getCaptain() const { return captain; }
    int getWorldRanking() const { return worldRanking; }
    
    // Setters
    void setTeamColor(string color) { teamColor = color; }
    void setWorldRanking(int rank) { worldRanking = rank; }
};

#endif
