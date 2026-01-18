// Hande Köksal 22401938

#include "Stop.h"
#include <string>
using std::string;

Stop::Stop() {

}

Stop::Stop(int ID, string name) {
    this->ID = ID;
    this->name = name;
}

int Stop::getID() const {
    return ID;
}

string Stop::getName() const {
    return name;
}

// Overloaded operators operate on ID's
bool Stop::operator>(const Stop& other) const {
    return ID > other.getID();
}

bool Stop::operator<(const Stop& other) const {
    return ID < other.getID();
}

bool Stop::operator==(const Stop& other) const {
    return ID == other.getID();
}