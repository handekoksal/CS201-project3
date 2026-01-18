// Hande Köksal 22401938

#ifndef BILKENTTOURISM_H
#define BILKENTTOURISM_H

#include <string>
#include "LinkedList.h"
#include "BusLine.h"
using std::string;

class BilkentTourism {
public:
    LinkedList<BusLine> busLines;
    LinkedList<Stop> stops;
    BilkentTourism();
    ~BilkentTourism();

    void addBusLine( const int lineId, const string lineName );
    void removeBusLine( const int lineId );
    void printBusLines() const;

    void addStop( const int stopId, const string stopName );
    void removeStop( const int stopId );
    void addStopToLine( const int stopId, const int lineId );
    void removeStopFromLine( const int stopId, const int lineId );
    void printStops( const int lineId ) const;

    void assignBus( const int busId, const string driverName, const int lineId);
    void unassignBus( const int busId );
    void printBussesInLine( const int lineId ) const;
    void printBussesPassingStop( const int stopId ) const;

    // My added functions
    Node<BusLine>* getBusLineFromID(int lineId);
    const Node<BusLine>* getBusLineFromID(int lineId) const;
    bool checkIfBusAssigned(int busId);
};

#endif