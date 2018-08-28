//	LinkedBagClientSP340.cpp
//	Created by: Duc Ta

#include <iostream>
#include <string>
#include <vector>
#include "LinkedBag.cpp"
#include "LinkedBag340.cpp"

//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

void displayBag(std::unique_ptr<LinkedBag<std::string>>&);

int main() {

	std::cout << "----- LINKED BAG 340 C++-----" << std::endl << std::endl;

	// 1. Create a bag and add initial nodes
	std::cout << "--->>>>> Test 1 --->>>>>" << std::endl;
	auto bag = std::make_unique <LinkedBag<std::string>>();
	
	// A mall vector of small objects to test the bag
	std::vector<std::string> items { "#-END", "5-FIVE", "4-FOUR", "4-FOUR", "3-THREE", "2-TWO", "1-ONE", "0-ZERO", "#-BEGIN" };
	std::cout << " !add()...     ";
	std::vector<std::string>::const_iterator cItr;
	for (cItr = items.begin(); cItr  != items.end(); cItr++) {
		std::cout << *cItr << " ";
		bool success = bag->add(*cItr);
		if ( !success) {
			std::cout << " !add() FAILED: " << *cItr << std::endl;
		}
	}
	displayBag(bag);

	// 2. Remove the second node
	std::cout << "\n--->>>>> Test 2 --->>>>>";
	std::cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	std::cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	displayBag(bag);
	std::cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	std::cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	displayBag(bag);

	// 3. Add a node to the end of the linked list
	std::cout << "\n--->>>>> Test 3 --->>>>>";
	std::cout << "\n !addEnd340()... ";
	bag->addEnd340("9-NINE");
	std::cout << "\n !addEnd340()... ";
	bag->addEnd340("4-FOUR"); 
	displayBag(bag);
	std::cout << "\n !addEnd340()... ";
	bag->addEnd340("9-NINE");
	std::cout << "\n !addEnd340()... ";
	bag->addEnd340("0-ZERO");
	displayBag(bag);

	// 4. getCurrentSize() - Iterative
	std::cout << "\n--->>>>> Test 4 --->>>>>";
	std::cout << "\n !getCurrentSize340Iterative - Iterative... ";
	std::cout << "\n  ---> Current size: " << bag->getCurrentSize340Iterative();
	displayBag(bag);

	// 5. getCurrentSize() - Recursive
	std::cout << "\n--->>>>> Test 5 --->>>>>";
	std::cout << "\n !getCurrentSize340Recursive() - Recursive... ";
	std::cout << "\n  ---> Current size: " << bag->getCurrentSize340Recursive();
	displayBag(bag);

	// 6. getFrequencyOf340Recursive() - Recursive
	std::cout << "\n--->>>>> Test 6 --->>>>>";
	std::cout << "\n !getFrequencyOf340Recursive() - Recursive... ";
	std::cout << "\n  ---> 0-ZERO:  " << bag->getFrequencyOf340Recursive("0-ZERO");
	std::cout << "\n  ---> 1-ONE:   " << bag->getFrequencyOf340Recursive("1-ONE");
	std::cout << "\n  ---> 2-TWO:   " << bag->getFrequencyOf340Recursive("2-TWO");
	std::cout << "\n  ---> 4-FOUR:  " << bag->getFrequencyOf340Recursive("4-FOUR");
	std::cout << "\n  ---> 9-NINE:  " << bag->getFrequencyOf340Recursive("9-NINE");
	displayBag(bag);

	std::cout << "\n !getFrequencyOf()... ";
	std::cout << "\n  ---> 0-ZERO:  " << bag->getFrequencyOf("0-ZERO");
	std::cout << "\n  ---> 1-ONE:   " << bag->getFrequencyOf("1-ONE");
	std::cout << "\n  ---> 2-TWO:   " << bag->getFrequencyOf("2-TWO");
	std::cout << "\n  ---> 4-FOUR:  " << bag->getFrequencyOf("4-FOUR");
	std::cout << "\n  ---> 9-NINE:  " << bag->getFrequencyOf("9-NINE");
	displayBag(bag);
	

	// 7. Remove a random node
	std::cout << "\n--->>>>> Test 7 --->>>>>";
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	displayBag(bag);
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	displayBag(bag);
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	displayBag(bag);
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	std::cout << "\n !removeRandom340() ---> " << bag->removeRandom340();
	displayBag(bag);

	std::cout << std::endl;
	return 0;
}

// Display the current contents in the bag
void displayBag(std::unique_ptr<LinkedBag<std::string>>& bag) {
	std::cout << "\n !Display bag: ";
	auto bagItems = std::make_unique<std::vector<std::string>>(bag->toVector());

	std::vector<std::string>::const_iterator cItr;
	for (cItr = bagItems->begin(); cItr  != bagItems->end(); cItr++) {
		std::cout << *cItr << " ";
	}
	
	std::cout << "\n  -----------> " << bagItems->size() << " item(s) total";
	std::cout << std::endl;
}