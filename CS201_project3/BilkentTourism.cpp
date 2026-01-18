// Hande Köksal 22401938

#include <iostream>
#include "BilkentTourism.h"
using namespace std;

BilkentTourism::BilkentTourism() {

}

BilkentTourism::~BilkentTourism() {

}

void BilkentTourism::addBusLine( const int lineId, const string lineName ) {
    // Function add in LinkedList returns a bool value
    // True if entry was able to be added
    bool ableToAdd = busLines.add(BusLine(lineId, lineName));

    if (ableToAdd) {
        cout << "Added bus line " << lineId << "." << endl;
    }
    else {
        cout << "Cannot add line. There is already a bus line with ID " << lineId << "." << endl;
    }
}

void BilkentTourism::removeBusLine( const int lineId ) {
    Node<BusLine>* curPtr = busLines.getHeadPtr();
    // Position starts at 1
    // Based on remove function's logic
    int position = 1;

    while (curPtr != nullptr && curPtr->getItem().getID() != lineId) {
        curPtr = curPtr->getNext();
        position++;
    }

    // Function remove from LinkedList takes the position of the entry that is to be deleted
    if (curPtr != nullptr && curPtr->getItem().getID() == lineId) {
        busLines.remove(position);
        cout << "Removed bus line " << lineId << "." << endl;
        return;
    }
    else {
        cout << "Cannot remove bus line. There is no bus line with ID " << lineId << "." << endl;
        return;
    }
}

void BilkentTourism::printBusLines() const {
    if (busLines.getHeadPtr() == nullptr) {
        cout << "There are no bus lines to show." << endl;
        return;
    }
    else {
        cout << "Bus lines in the system:" << endl;
        Node<BusLine>* curPtr = busLines.getHeadPtr();
        while(curPtr != nullptr) {
            // Line ID : name
            cout << "Line " << curPtr->getItem().getID() << " : " << curPtr->getItem().getName() << endl;
            curPtr = curPtr->getNext();
        }
    }
}

void BilkentTourism::addStop( const int stopId, const string stopName ) {
    // Add returns a bool value
    bool ableToAdd = stops.add(Stop(stopId, stopName));

        if (ableToAdd) {
            cout << "Added stop " << stopId << "." << endl;
        }
        else {
            cout << "Cannot add stop. BilkentTourism already contains stop " << stopId << "." << endl;
        }
}

void BilkentTourism::removeStop( const int stopId ) {
    Node<Stop>* curPtr = stops.getHeadPtr();
    int position = 1;

    while (curPtr != nullptr && curPtr->getItem().getID() != stopId) {
        curPtr = curPtr->getNext();
        position++;
    }

    if (curPtr != nullptr && curPtr->getItem().getID() == stopId) {
        Node<BusLine>* curBusLinePtr = busLines.getHeadPtr();
        while(curBusLinePtr != nullptr) {
            Node<Stop>* curStopPtr = curBusLinePtr->getItem().getStops().getHeadPtr();
            while (curStopPtr != nullptr) {
                // If the stop is already used by a BusLine
                if (curStopPtr->getItem().getID() == stopId) {
                    cout << "Cannot remove stop " << stopId << ". The stop is currently in use." << endl;
                    return;
                }
                curStopPtr = curStopPtr->getNext();
            }
            curBusLinePtr = curBusLinePtr->getNext();
        }

        // If no BusLine uses the specified stop
        stops.remove(position);
        cout << "Removed stop " << stopId << "." << endl;
    }
    // If stop doesn't exist
    else {
        cout << "Cannot remove stop " << stopId << ". There is no bus stop with ID " << stopId << "." << endl;
    }
}

void BilkentTourism::addStopToLine( const int stopId, const int lineId ) {
    Node<BusLine>* busLinePtr = getBusLineFromID(lineId);
    if (busLinePtr == nullptr) {
        cout << "Cannot add stop. There is no line with ID " << lineId << "." << endl;
        return;
    }

    Node<Stop>* stopPtr = stops.getHeadPtr();
    while (stopPtr != nullptr && stopPtr->getItem().getID() != stopId) {
        stopPtr = stopPtr->getNext();
    }

    if (stopPtr == nullptr) {
        cout << "Cannot add stop. There is no stop with ID " << stopId << "." << endl;
        return;
    }

    Node<Stop>* lineStopPtr = busLinePtr->getItem().getStops().getHeadPtr();
    while (lineStopPtr != nullptr) {
        // If the line already contains the stop
        if (lineStopPtr->getItem().getID() == stopId) {
            cout << "Cannot add stop. Line " << lineId << " already contains stop " << stopId << "." << endl;
            return;
        }
        lineStopPtr = lineStopPtr->getNext();
    }

    // Able to add the stop to the BusLine
    busLinePtr->getItem().getStops().add(stopPtr->getItem());
    cout << "Added stop " << stopId << " to line " << lineId << " (" << busLinePtr->getItem().getName() << ")." << endl;
}

void BilkentTourism::removeStopFromLine( const int stopId, const int lineId ) {
    Node<BusLine>* busLinePtr = getBusLineFromID(lineId);

    if (busLinePtr == nullptr) {
        cout << "Cannot remove stop. There is no line with ID " << lineId << "." << endl;
        return;
    } // Line doesn't exist

    // This condition wasn't specified in the hw pdf
    /*Node<Stop>* stopPtr = stops.getHeadPtr();
    while (stopPtr != nullptr && stopPtr->getItem().getID() != stopId) {
        stopPtr = stopPtr->getNext();
    }

    if (stopPtr == nullptr) {
        cout << "Cannot remove stop. There is no stop with ID " << stopId << "." << endl;
        return;
    } // Line exists, stop doesn't exist*/

    LinkedList<Stop>& lineStops = busLinePtr->getItem().getStops();

    Node<Stop>* lineStopPtr = lineStops.getHeadPtr();
    int position = 1;

    while (lineStopPtr != nullptr) {
        if (lineStopPtr->getItem().getID() == stopId) {
            lineStops.remove(position);
            cout << "Removed stop " << stopId << " from line " << lineId << "." << endl;
            return;
        } // Line exists, stop exists
        lineStopPtr = lineStopPtr->getNext();
        position++;
    }

    cout << "Cannot remove stop. Line " << lineId << " does not have stop " << stopId << "." << endl;
    // Line exists but doesn't contain stop
}

void BilkentTourism::printStops( const int lineId ) const {
    const Node<BusLine>* busLinePtr = getBusLineFromID(lineId);

    if (busLinePtr == nullptr) {
        cout << "Cannot print stops. There is no line with ID " << lineId << "." << endl;
        return;
    }

    busLinePtr->getItem().printStops();
}

void BilkentTourism::assignBus( const int busId, const string driverName, const int lineId) {
    Node<BusLine>* busLinePtr = getBusLineFromID(lineId);

    if (busLinePtr == nullptr) {
        cout << "Cannot assign bus. There is no line with ID " << lineId << "." << endl;
        return;
    }

    bool busAssigned = checkIfBusAssigned(busId);

    if (busAssigned) {
        cout << "Cannot assign bus. Bus " << busId << " is already assigned to a line." << endl;
        return;
    }

    Node<Bus>* busPtr = busLinePtr->getItem().getBusses().getHeadPtr();
    while (busPtr != nullptr && busPtr->getItem().getID() != busId) {
        busPtr = busPtr->getNext();
    }

    // Adding to line's busses LinkedList
    if (busPtr == nullptr) {
        busLinePtr->getItem().getBusses().add(Bus(busId, driverName));
        cout << "Bus " << busId << " with driver " << driverName << " is assigned to line " << lineId << " (" << busLinePtr->getItem().getName() << ")." << endl;
        return;
    }
}

void BilkentTourism::unassignBus( const int busId ) {
    Node<BusLine>* curBusLinePtr = busLines.getHeadPtr();

    while(curBusLinePtr != nullptr) {
        Node<Bus>* curBusPtr = curBusLinePtr->getItem().getBusses().getHeadPtr();

        int position = 1;
        while (curBusPtr != nullptr && curBusPtr->getItem().getID() != busId) {
            position++;
            curBusPtr = curBusPtr->getNext();
        }

        // Removing from line's busses LinkedList
        if (curBusPtr != nullptr && curBusPtr->getItem().getID() == busId) {
            curBusLinePtr->getItem().getBusses().remove(position);
            cout << "Bus " << busId << " is unassigned from line " << curBusLinePtr->getItem().getID() << " (" << curBusLinePtr->getItem().getName() << ")." << endl;
            return;
        }

        curBusLinePtr = curBusLinePtr->getNext();
    }

    cout << "Cannot unassign bus. There is no bus with ID " << busId << "." << endl;
}

void BilkentTourism::printBussesInLine( const int lineId ) const {
    const Node<BusLine>* busLinePtr = getBusLineFromID(lineId);

    if (busLinePtr == nullptr) {
        cout << "Cannot print busses. There is no line with ID " << lineId << "." << endl;
        return;
    }

    busLinePtr->getItem().printBusses();
}

void BilkentTourism::printBussesPassingStop( const int stopId ) const {
    Node<Stop>* curStopPtr = stops.getHeadPtr();

    while (curStopPtr != nullptr && curStopPtr->getItem().getID() != stopId) {
        curStopPtr = curStopPtr->getNext();
    }

    // To check if any of the lines pass through the stop
    bool aLinePasses = false;
    bool titleShown = false;
    if (curStopPtr != nullptr && curStopPtr->getItem().getID() == stopId) {
        Node<BusLine>* curBusLinePtr = busLines.getHeadPtr();
        while(curBusLinePtr != nullptr) {
            Node<Stop>* curStop = curBusLinePtr->getItem().getStops().getHeadPtr();
            while (curStop != nullptr) {
                // If a line passes through the stop
                if (curStop->getItem().getID() == stopId) {
                    if (!titleShown) {
                        cout << "Buses and their assigned lines passing the stop " << curStop->getItem().getID() << " (" << curStop->getItem().getName() << "):" << endl;
                        titleShown = true;
                    }
                    // Print accordingly and update aLinePasses
                    curBusLinePtr->getItem().printBussesList();
                    aLinePasses = true;
                    break;
                }
                curStop = curStop->getNext();
            }
            curBusLinePtr = curBusLinePtr->getNext();
        }
        titleShown = false;

        if (!aLinePasses) {
            cout << "Cannot print buses. No lines pass through the stop." << endl;
            return;
        }
    }
    else {
        cout << "Cannot print buses. There is no stop with ID " << stopId << "." << endl;
    }
}

// Returns the node of the bus line based on its ID
// Non const version
Node<BusLine>* BilkentTourism::getBusLineFromID(int lineId) {
    Node<BusLine>* curPtr = busLines.getHeadPtr();
    while (curPtr != nullptr && curPtr->getItem().getID() != lineId)
        curPtr = curPtr->getNext();
    return curPtr;
}

// Const version
const Node<BusLine>* BilkentTourism::getBusLineFromID(int lineId) const {
    const Node<BusLine>* curPtr = busLines.getHeadPtr();
    while (curPtr != nullptr && curPtr->getItem().getID() != lineId)
        curPtr = curPtr->getNext();
    return curPtr;
}
// Both const and non const versions were needed to use in const and non const functions respectively


// Checks if a bus has been assigned to a bus line
bool BilkentTourism::checkIfBusAssigned(int busId) {

    Node<BusLine>* curBusLinePtr = busLines.getHeadPtr();

    while(curBusLinePtr != nullptr) {
        Node<Bus>* curBusPtr = curBusLinePtr->getItem().getBusses().getHeadPtr();

        while (curBusPtr != nullptr && curBusPtr->getItem().getID() != busId) {
            curBusPtr = curBusPtr->getNext();
        }

        if (curBusPtr != nullptr && curBusPtr->getItem().getID() == busId) {
            return true;
        }

        curBusLinePtr = curBusLinePtr->getNext();
    }

    return false;
}