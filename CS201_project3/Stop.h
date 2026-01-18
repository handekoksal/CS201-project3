// Hande Köksal 22401938

#ifndef STOP_
#define STOP_

#include <string>
using std::string;

class Stop {
private:
    int ID;
    string name;
public:
    Stop();
    Stop(int ID, string name);
    int getID() const;
    string getName() const;

    // Operator overloading
    bool operator>(const Stop& other) const;
    bool operator<(const Stop& other) const;
    bool operator==(const Stop& other) const;
};

#endif