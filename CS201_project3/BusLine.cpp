// Hande Köksal 22401938

#include "BusLine.h"
#include <iostream>
using namespace std;

BusLine::BusLine() {

}

BusLine::BusLine(int ID, string name) {
    this->ID = ID;
    this->name = name;
}

BusLine::~BusLine() {

}

int BusLine::getID() const {
    return ID;
}

string BusLine::getName() const {
    return name;
}

LinkedList<Stop>& BusLine::getStops() {
    return stops;
}

LinkedList<Bus>& BusLine::getBusses() { 
    return busses; 
}

const LinkedList<Bus>& BusLine::getBusses() const { 
    return busses; 
}

// Overloaded operators operate on ID's
bool BusLine::operator>(const BusLine& other) const {
    return ID > other.getID();
}

bool BusLine::operator<(const BusLine& other) const {
    return ID < other.getID();
}

bool BusLine::operator==(const BusLine& other) const {
    return ID == other.getID();
}

// For printing stops
void BusLine::printStops() const {
    Node<Stop>* curStopPtr = stops.getHeadPtr();

    if (curStopPtr == nullptr) {
        cout << "Cannot print stops. There is no stop to show." << endl;
        return;
    }

    cout << "Stops in bus line " << ID << " (" << name << ") :" << endl;
    while (curStopPtr != nullptr) {
        cout << "Stop " << curStopPtr->getItem().getID() << " : " << curStopPtr->getItem().getName() << endl;
        curStopPtr = curStopPtr->getNext();
    }
}

// For printing busses and their drivers
void BusLine::printBusses() const {
    Node<Bus>* curBusPtr = busses.getHeadPtr();

    if (curBusPtr == nullptr) {
        cout << "There are no bus to show in line " << ID << " (" << name << ")." << endl;
        return;
    }

    cout << "Busses and their drivers assigned to the line " << ID << " (" << name << "):" << endl;
    while (curBusPtr != nullptr) {
        cout << "Bus " << curBusPtr->getItem().getID() << " : " << curBusPtr->getItem().getName() << endl;
        curBusPtr = curBusPtr->getNext();
    }
}

// For printing the list of busses
void BusLine::printBussesList() const {
    const Node<Bus>* curBusPtr = busses.getHeadPtr();

    if (curBusPtr == nullptr) {
        cout << "Line " << ID << " (" << name << " ) : None" << endl;
        return;
    }

    cout << "Line " << ID << " (" << name << ") : [";
    while (curBusPtr != nullptr) {
        if (curBusPtr->getNext() == nullptr) {
            cout << curBusPtr->getItem().getID() << "]" << endl;
            return;
        }
        cout << curBusPtr->getItem().getID() << ",";
        curBusPtr = curBusPtr->getNext();
    }
}