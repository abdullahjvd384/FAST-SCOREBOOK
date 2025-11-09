#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
using namespace std;

// Base class for all people involved in cricket
class Person {
protected:
    string name;
    int age;
    string nationality;
    string id;

public:
    Person() : name(""), age(0), nationality(""), id("") {}
    
    Person(string n, int a, string nat, string i) 
        : name(n), age(a), nationality(nat), id(i) {}
    
    virtual ~Person() {}
    
    // Pure virtual function - makes Person abstract
    virtual void displayInfo() const = 0;
    
    // Getters
    string getName() const { return name; }
    int getAge() const { return age; }
    string getNationality() const { return nationality; }
    string getId() const { return id; }
    
    // Setters
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setNationality(string nat) { nationality = nat; }
};

#endif
