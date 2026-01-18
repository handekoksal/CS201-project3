// Hande Köksal
// Taken from the lecture slides

#ifndef LIST_INTERFACE_
#define lIST_INTERFACE_

template<class ItemType>
class ListInterface {
public:
    virtual bool isEmpty() const = 0;
    virtual int getCount() const = 0;
    virtual bool add(const ItemType& newEntry) = 0;
    virtual bool remove(int position) = 0;
    virtual void clear() = 0;
    virtual ItemType getEntry(int position) const = 0;
    virtual ~ListInterface() { }
};

#endif