#ifndef OFFICIALS_H
#define OFFICIALS_H

#include "Person.h"

// Umpire class
class Umpire : public Person {
private:
    int matchesOfficiated;
    string umpireType; // On-field, Third umpire, Match referee
    
public:
    Umpire() : Person(), matchesOfficiated(0), umpireType("On-field") {}
    
    Umpire(string n, int a, string nat, string i, string type)
        : Person(n, a, nat, i), matchesOfficiated(0), umpireType(type) {}
    
    void displayInfo() const override {
        cout << "Umpire: " << name << " (" << umpireType << ")" << endl;
        cout << "Nationality: " << nationality << endl;
        cout << "Matches Officiated: " << matchesOfficiated << endl;
    }
    
    string getUmpireType() const { return umpireType; }
    void incrementMatches() { matchesOfficiated++; }
};

// Commentator class
class Commentator : public Person {
private:
    string language;
    string specialization; // TV, Radio, Digital
    
public:
    Commentator() : Person(), language("English"), specialization("TV") {}
    
    Commentator(string n, int a, string nat, string i, string lang, string spec)
        : Person(n, a, nat, i), language(lang), specialization(spec) {}
    
    void displayInfo() const override {
        cout << "Commentator: " << name << endl;
        cout << "Language: " << language << " | Platform: " << specialization << endl;
    }
};

// Ground Staff class
class GroundStaff : public Person {
private:
    string role; // Curator, Maintenance, Security, etc.
    
public:
    GroundStaff() : Person(), role("") {}
    
    GroundStaff(string n, int a, string nat, string i, string r)
        : Person(n, a, nat, i), role(r) {}
    
    void displayInfo() const override {
        cout << "Ground Staff: " << name << " (" << role << ")" << endl;
    }
};

// Supervisor for conflict resolution
class Supervisor : public Person {
private:
    string username;
    int conflictsResolved;
    
public:
    Supervisor() : Person(), username(""), conflictsResolved(0) {}
    
    Supervisor(string n, int a, string nat, string i, string uname)
        : Person(n, a, nat, i), username(uname), conflictsResolved(0) {}
    
    void displayInfo() const override {
        cout << "Supervisor: " << name << " (Username: " << username << ")" << endl;
        cout << "Conflicts Resolved: " << conflictsResolved << endl;
    }
    
    void resolveConflict() { conflictsResolved++; }
    string getUsername() const { return username; }
};

#endif
