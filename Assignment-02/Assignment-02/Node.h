//	Node.h
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#pragma once
#include <memory>
//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

template<typename ItemType>
class Node {
public:
	Node();
	Node(const ItemType&);
	Node(const ItemType&, Node<ItemType>*);
	void setItem(const ItemType&);
	void setNext(Node<ItemType>*);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;

private:
	ItemType  item;			 // A data item
    Node<ItemType>* next {nullptr}; // Pointer to next node
};
