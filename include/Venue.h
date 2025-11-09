#ifndef VENUE_H
#define VENUE_H

#include <string>
#include <iostream>
using namespace std;

class Venue {
private:
    string stadiumName;
    string city;
    string country;
    int capacity;
    string pitchType; // Batting-friendly, Bowling-friendly, Balanced
    bool hasFloodlights;
    
public:
    Venue() : stadiumName(""), city(""), country(""), 
              capacity(0), pitchType("Balanced"), hasFloodlights(false) {}
    
    Venue(string stadium, string c, string ctry, int cap)
        : stadiumName(stadium), city(c), country(ctry), capacity(cap),
          pitchType("Balanced"), hasFloodlights(false) {}
    
    void displayVenueInfo() const {
        cout << "\n===== Venue Information =====" << endl;
        cout << "Stadium: " << stadiumName << endl;
        cout << "Location: " << city << ", " << country << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Pitch Type: " << pitchType << endl;
        cout << "Floodlights: " << (hasFloodlights ? "Yes" : "No") << endl;
    }
    
    // Getters
    string getStadiumName() const { return stadiumName; }
    string getCity() const { return city; }
    string getCountry() const { return country; }
    int getCapacity() const { return capacity; }
    
    // Setters
    void setPitchType(string type) { pitchType = type; }
    void setFloodlights(bool lights) { hasFloodlights = lights; }
};

class BroadcastAgency {
private:
    string agencyName;
    string region;
    string language;
    
public:
    BroadcastAgency() : agencyName(""), region(""), language("") {}
    
    BroadcastAgency(string name, string reg, string lang)
        : agencyName(name), region(reg), language(lang) {}
    
    void displayInfo() const {
        cout << "Broadcaster: " << agencyName 
             << " (Region: " << region << ", Language: " << language << ")" << endl;
    }
    
    string getAgencyName() const { return agencyName; }
    string getRegion() const { return region; }
};

#endif
