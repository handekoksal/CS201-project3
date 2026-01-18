// Hande Köksal 22401938

#ifndef BUSLINE_
#define BUSLINE_

#include <iostream>
#include "LinkedList.h"
#include "Stop.h"
#include "Bus.h"
using namespace std;

class BusLine {
private:
    int ID;
    string name;
    LinkedList<Stop> stops; // BusLine's stops
    LinkedList<Bus> busses; // BusLine's busses
public:
    BusLine();
    BusLine(int ID, string name);
    ~BusLine();
    int getID() const;
    string getName() const;
    LinkedList<Stop>& getStops();
    LinkedList<Bus>& getBusses();
    const LinkedList<Bus>& getBusses() const;

    // Operator overloading
    bool operator>(const BusLine& other) const;
    bool operator<(const BusLine& other) const;
    bool operator==(const BusLine& other) const;

    // Functions for the three printing operators in BilkentTourism
    void printStops() const;
    void printBusses() const;
    void printBussesList() const;
};

#endif