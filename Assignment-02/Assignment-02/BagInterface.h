//  BagInterface.h
//  Created by Frank M. Carrano and Timothy M. Henry.
//  Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#pragma once
#include <vector>

//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

template<typename ItemType>
class BagInterface {
public:
	/*--------------------------CSC340------------------------------*/
	// Remove the second node
	virtual bool removeSecondNode340() = 0;

	// Add a node to the end of the linked list
	virtual bool addEnd340(const ItemType&) = 0;

	// getCurrentSize() - Iterative
	virtual int getCurrentSize340Iterative() const = 0;

	// getCurrentSize() - Recursive
	virtual int getCurrentSize340Recursive() const = 0;

	// getFrequencyOf340Recursive() - Recursive
	virtual int getFrequencyOf340Recursive(const ItemType&) const = 0;

	// Remove a random node
	virtual ItemType removeRandom340() = 0;
	/*--------------------------------------------------------------*/

    // Gets the current number of entries in this bag.
	virtual int getCurrentSize() const = 0;

	// Sees whether this bag is empty.
	virtual bool isEmpty() const = 0;

	// Adds a new entry to this bag.
	virtual bool add(const ItemType&) = 0;

	// Removes one occurrence of a given entry from this bag, if possible.
	virtual bool remove(const ItemType&) = 0;

	// Removes all entries from this bag.
	virtual void clear() = 0;

	// Counts the number of times a given entry appears in bag.
	virtual int getFrequencyOf(const ItemType&) const = 0;

	// Tests whether this bag contains a given entry.
	virtual bool contains(const ItemType&) const = 0;

	// Empties and then fills a given vector with all entries that are in this bag.
	virtual std::vector<ItemType> toVector() const = 0;

	// Destroys object and frees memory allocated by object.
	virtual ~BagInterface() { }
}; // end BagInterface