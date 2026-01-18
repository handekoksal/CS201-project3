// Hande Köksal 22401938
// Partially taken from the lecture slides

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"
#include <stdexcept> // for std::out_of_range
#include <cstddef>

template<class ItemType>
class LinkedList {
private:
    Node<ItemType>* headPtr;
    int count;

    Node<ItemType>* getNodeAt(int position) const;

public:
    LinkedList();
    LinkedList(const LinkedList<ItemType>& aList);
    ~LinkedList();

    bool isEmpty() const;
    int getCount() const;

    bool add(const ItemType& newEntry);
    bool remove(int position);
    void clear();

    ItemType getEntry(int position) const;

    Node<ItemType>* getHeadPtr() const;
};

// Implementations

template<class ItemType>
LinkedList<ItemType>::LinkedList() {
    headPtr = nullptr;
    count = 0;
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const {
    if (position >= 1 && position <= count)
        return getNodeAt(position)->getItem();

    throw std::out_of_range("Invalid index");
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const {
    if (position < 1 || position > count)
        return nullptr;

    Node<ItemType>* curPtr = headPtr;
    for (int i = 1; i < position; i++)
        curPtr = curPtr->getNext();

    return curPtr;
}

template<class ItemType>
bool LinkedList<ItemType>::add(const ItemType& newEntry) {
    Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
    Node<ItemType>* curPtr = headPtr;
    Node<ItemType>* prevPtr = nullptr;

    while (curPtr != nullptr && curPtr->getItem() < newEntry) {
        prevPtr = curPtr;
        curPtr = curPtr->getNext();
    }

    if (curPtr != nullptr && curPtr->getItem() == newEntry) {
        delete newNodePtr;
        return false;
    }

    if (prevPtr == nullptr) {
        newNodePtr->setNext(headPtr);
        headPtr = newNodePtr;
    }
    else {
        newNodePtr->setNext(curPtr);
        prevPtr->setNext(newNodePtr);
    }

    count++;
    return true;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position) {
    if (position < 1 || position > count)
        return false;

    Node<ItemType>* curPtr = nullptr;

    if (position == 1) {
        curPtr = headPtr;
        headPtr = headPtr->getNext();
    }
    else {
        Node<ItemType>* prevPtr = getNodeAt(position - 1);
        curPtr = prevPtr->getNext();
        prevPtr->setNext(curPtr->getNext());
    }

    delete curPtr;
    count--;
    return true;
}

template<class ItemType>
void LinkedList<ItemType>::clear() {
    while (!isEmpty())
        remove(1);
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList() {
    clear();
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const {
    return count == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getCount() const {
    return count;
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) {
    count = aList.count;

    if (aList.headPtr == nullptr) {
        headPtr = nullptr;
        return;
    }

    headPtr = new Node<ItemType>(aList.headPtr->getItem());

    Node<ItemType>* newChainPtr = headPtr;
    Node<ItemType>* origChainPtr = aList.headPtr->getNext();

    while (origChainPtr != nullptr) {
        Node<ItemType>* newNode = new Node<ItemType>(origChainPtr->getItem());
        newChainPtr->setNext(newNode);
        newChainPtr = newNode;
        origChainPtr = origChainPtr->getNext();
    }

    newChainPtr->setNext(nullptr);
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getHeadPtr() const {
    return headPtr;
}

#endif