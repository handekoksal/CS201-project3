// Hande Köksal 22401938

#include "Bus.h"
#include <string>
using std::string;

Bus::Bus() {

}

Bus::Bus(int ID, string name) {
    this->ID = ID;
    this->name = name;
}

int Bus::getID() const {
    return ID;
}

string Bus::getName() const {
    return name;
}

// Overloaded operators operate on ID's
bool Bus::operator>(const Bus& other) const {
    return ID > other.getID();
}

bool Bus::operator<(const Bus& other) const {
    return ID < other.getID();
}

bool Bus::operator==(const Bus& other) const {
    return ID == other.getID();
}