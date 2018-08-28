//	LinkedBag340.cpp
//	Created by: Cristobal Padilla

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include "LinkedBag.h"
#include <time.h>

const int NODE_POSITION_TO_BE_REMOVED = 2 ;

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340(){
    bool canRemoveItem = (getCurrentSize340Iterative() >= NODE_POSITION_TO_BE_REMOVED) ;
    
    if(canRemoveItem){
        Node<ItemType>* nodeToRemovePtr = headPtr;             // Reference to first node.
        headPtr->getNext()->setItem(headPtr->getItem());       // Override second node object.
        headPtr = headPtr->getNext();                          // Advance header to second node.
        
        // Delete first node and all associated data.
        nodeToRemovePtr->setNext(nullptr);
        delete nodeToRemovePtr;
        nodeToRemovePtr = nullptr;
        itemCount--;
    }
    return canRemoveItem;
}

template<typename ItemType>
bool LinkedBag<ItemType>::addEnd340(const ItemType& newEntry) {
    Node<ItemType>* cursorPtr = headPtr;                       // Rerefence to first node.
    
    while(cursorPtr->getNext() != nullptr)                     // Move cursor to last node.
        cursorPtr = cursorPtr->getNext();
    
    Node<ItemType>* nextNodePtr = new Node<ItemType>();        // Add node to the end.
    nextNodePtr->setItem(newEntry);
    cursorPtr->setNext(nextNodePtr);
    itemCount++;
    
    return true;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Iterative() const {
    int count = 0;
    Node<ItemType>* cursorPtr = headPtr;                       // Reference to first node.
    
    while(cursorPtr != nullptr) {                              // Move cursor to end of list,
        cursorPtr = cursorPtr->getNext();                      // counting each iteration.
        count++;
    }
    
    return count;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    static Node<ItemType>* cursor = headPtr;
    int count = 0;

    if (cursor != nullptr) {
        count++;
        cursor = cursor->getNext();
        count += getCurrentSize340Recursive();
    }
    else
        cursor = headPtr;
    
    return count;
}

/***********************************************************
  getCurrentSize340Recursive() using the helper function.
***********************************************************/
/*
template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const {
    Node<ItemType>* cursorPtr = headPtr;                       // Reference to first node.
    
    return getCurrentSize340RecursiveHelper(cursorPtr);        // Return value from helper function.
}
*/

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& item) const {
    static Node<ItemType>* cursor = headPtr;
    int count = 0;
    
    if (cursor != nullptr){
        if (cursor->getItem() == item) {
            count++;
        }
        cursor = cursor->getNext();
        count += getFrequencyOf340Recursive(item);
    }
    cursor = headPtr;
    return count;
}

/***********************************************************
  getFrequencyOf340Recursive() using the helper function.
***********************************************************/
/*
template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType& item) const {
    Node<ItemType>* cursorPtr = headPtr;                       // Reference to first node.
    
    return getFrequencyOf340RecursiveHelper(cursorPtr, item);  // Return value from helper function.
}
*/

template<typename ItemType>
ItemType LinkedBag<ItemType>::removeRandom340() {
    Node<ItemType>* cursorPtr = headPtr;                       // Reference to first node.
    srand(time(NULL));                                         // Set up random integer.
    int randNodeToRemovePosition = std::rand() % getCurrentSize340Iterative() + 1;
    int cursorPosition = 1;
    
    while (cursorPosition < randNodeToRemovePosition) {        // Move cursor to node to be removed.
        cursorPtr = cursorPtr->getNext();
        cursorPosition++;
    }
    
    /* Override Object at nth position with object in the first position */
    ItemType tmp = cursorPtr->getItem();                       // Capture object from selected node.
    cursorPtr->setItem(headPtr->getItem());                    // Override cursor object.
    Node<ItemType>* nodeToRemovePtr = headPtr;
    headPtr = headPtr->getNext();
    
    /* Delete the node at the first position */
    nodeToRemovePtr->setNext(nullptr);
    delete nodeToRemovePtr;
    nodeToRemovePtr = nullptr;
    itemCount--;
    
    return tmp;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* nodePtr) const {
    int count = 0;                                             // Variable used to keep instance count
    
    if (nodePtr == nullptr)                                    // Base Case: end of list (nullptr).
        return count;
    
    else {                                                     // Else, increase count variable and return
        count++;                                               // recursive call passing next node.
        return count += getCurrentSize340RecursiveHelper(nodePtr->getNext());
    }
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>* nodePtr, const ItemType& item) const {
    int count = 0;

    // Base Case: end of list nullptr.
    // If node is not last in the list, then do recursive call passing next node until end of list is reached.
    if(nodePtr->getNext() != nullptr)
        count += getFrequencyOf340RecursiveHelper(nodePtr->getNext(), item);
    
    // Increase counter if item is "equal" to item stored in node.
    if (nodePtr->getItem() == item) {
        count++;
    }
    
    return count;
}
