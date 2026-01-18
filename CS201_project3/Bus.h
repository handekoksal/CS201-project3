// Hande Köksal 22401938

#ifndef BUS_
#define BUS_

#include <string>
using std::string;

class Bus {
private:
    int ID;
    string name; // Driver's name
public:
    Bus();
    Bus(int ID, string name);
    int getID() const;
    string getName() const;

    // Operator overloading
    bool operator>(const Bus& other) const;
    bool operator<(const Bus& other) const;
    bool operator==(const Bus& other) const;
};

#endif