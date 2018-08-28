//
//  main.cpp
//  Dictionary-Assignment-01-Version
//
//  Created by Cris on 6/21/18.
//  Copyright © 2018 Cristobal Padilla. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iomanip>

// Global
enum partOfSpeech { NOUN,  VERB, ADJECTIVE, NOTVALID, DEFAULT};
static const char * partOfSpeechEnumStrings [] = {"NOUN", "VERB", "ADJECTIVE", "NOTVALID", "DEFAULT"};
static const std::string QUIT_SEARCH = "!Q";
static const std::string CLEAR = "CLEAR";

struct wordDescription {
    std::string wordNamePrintVersion;
    std::vector<std::string> nouns;
    std::vector<std::string> verbs;
    std::vector<std::string> adjectives;
};

// Function Declarations.
void printResults(const std::map<std::string, wordDescription>::iterator , partOfSpeech);
void printAll(const std::map<std::string, wordDescription>::iterator);
void printNouns(const std::map<std::string, wordDescription>::iterator);
void printVerbs(const std::map<std::string, wordDescription>::iterator);
void printAdjectives(const std::map<std::string, wordDescription>::iterator);
void printAll(const std::map<std::string, wordDescription>::iterator);
void printInvalidInput();
void printSourceFileNotFoundMessage();
void printWordNotFound();
void printInvalidPartOfSpeech();
void clear();
void clearXCodeConsole();
void exitMessage();
bool isEqual(const std::string&, const std::string&);
bool fillDictionary(std::map<std::string, wordDescription> * , std::string &);
bool checkDictionary(const std::map<std::string, wordDescription> * , const std::map<std::string, wordDescription>::iterator);
bool validPartOfSpeech(std::string);
const char* getStringForEnum(partOfSpeech);
partOfSpeech getPartOfSpeechString(std::string);

int main() {
    
    std::map<std::string, wordDescription>* dictionary = new std::map<std::string, wordDescription>();
    std::map<std::string, wordDescription>::iterator wordItr;
    std::string sourceFile("/Users/cristobalpadilla/Desktop/SFSU/SFSU-Projects/Computer_Science/CS-Courses/CSC 340(Programming Methodology)/SFSU-CSC340/Dictionary-Assignment-01-Version/Dictionary-Assignment-01-Version/Data.CS.SFSU.txt");
    std::stringstream tokens;
    std::string line, inputWord, inputPartOfSpeech, inputExcess;
    bool keepSearching = true;
    
    // Clear screen for program
    clear();
    
    if(fillDictionary(dictionary, sourceFile)){
        while(keepSearching) {                      // Begin Searching
            std::cout << "Search: ";                // Ask for input
            getline(std::cin, line);                // Parse input
            tokens << line;
            tokens >> inputWord;
            tokens >> inputPartOfSpeech;
            tokens >> inputExcess;
        
            if (isEqual(inputWord, QUIT_SEARCH)) {        // Quit program
                keepSearching = false;
                continue;
            }
        
            else if (isEqual(inputWord, CLEAR)) {       // Clear screen
                clear();
                //clearXCodeConsole();
            }
        
            else {
                std::transform(inputWord.begin(), inputWord.end(), inputWord.begin(), toupper);
                wordItr = dictionary->find(inputWord);
                std::cout << "\t|" << std::endl;
                if (inputWord.empty() || !inputExcess.empty()) {           // No entries, or way to many entries.
                    printInvalidInput();
                
                } else if (inputPartOfSpeech.empty()) {                    // Only one entry, check dictionary
                    if (checkDictionary(dictionary, wordItr))
                        printResults(wordItr, partOfSpeech::DEFAULT);
                    else
                        printWordNotFound();
                
                } else if (!validPartOfSpeech(inputPartOfSpeech)){         // Two entries, check part of speech
                    printInvalidPartOfSpeech();
                
                } else if (checkDictionary(dictionary, wordItr))                     // Two entries, parf of speech correct, check word
                    printResults(wordItr, getPartOfSpeechString(inputPartOfSpeech));
            
                else
                    printWordNotFound();
            
                std::cout << "\t|" << std::endl;
            }
            // Reset all streams to read next line.
            tokens.ignore(INT8_MAX, '\n');
            tokens.clear();
            std::cin.clear();
            inputWord.clear();
            inputPartOfSpeech.clear();
            inputExcess.clear();
            wordItr = dictionary->end();                // Set wordItr to "null"
        }
    } else
        printSourceFileNotFoundMessage();
    
    wordItr = dictionary->end();
    delete dictionary;
    dictionary = nullptr;
    exitMessage();
    return 0;
}

/**
 * Function used to confirm that the word is inside the dictionary.
 * Since one of the parameters in an iterator pointer obtained from
 * calling the 'find' method, this function does not conduct another
 * search. So, if the iterator pointer is not pointing to 'end()',
 * then the word is in the dictionary, and the function returns true,
 * and false otherwise.
 * @param dictionary is a pointer to a map.
 * @param wordPtr is an iterator pointer given from the 'find' function.
 * @rethrn true if the word is in the dictionary, false otherwise.
 */
bool checkDictionary(const std::map<std::string, wordDescription>* dictionary, const std::map<std::string, wordDescription>::iterator wordPtr) {
    if(wordPtr != dictionary->end())
        return true;
    else
        return false;
}

/**
 * Function used to extract data from text file and populate the dictionary map.
 * @param dictionary is a pointer to a map.
 * @param source is the path to the source file.
 * @return true operation was succesful, false otherwise.
 */
bool fillDictionary (std::map<std::string, wordDescription>* dictionary, std::string &source) {
    std::fstream ioFile (source);
    std::stringstream ssLine, ssPOfSpeech;
    std::string line, sentence, wordName, pOfSpeech, description, definition;
    long position = 0;
    if(ioFile.is_open()) {
    while(getline(ioFile, line)) {
        ssLine << line;
        getline(ssLine, wordName, '|');
        wordDescription def;
        
        while(getline(ssLine, sentence, '|')){
            ssPOfSpeech << sentence;
            
            getline(ssPOfSpeech, pOfSpeech, ' ');
            getline(ssPOfSpeech, description, '.');
            position = description.find(">");
            definition = description.substr(position + 2);
            
            // fill def structure vectors.
            if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::NOUN))){
                def.nouns.push_back(definition);
            }
            else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::VERB))){
                def.verbs.push_back(definition);
            }
            else if (isEqual(pOfSpeech, getStringForEnum(partOfSpeech::ADJECTIVE))){
                def.adjectives.push_back(definition);
            }
        }
        
        if (wordName[0] != 'c') {
            std::transform(wordName.begin(), wordName.end(), wordName.begin(), tolower);
            wordName[0] = toupper(wordName[0]);
            def.wordNamePrintVersion = wordName;
        } else {
            std::transform(wordName.begin(), wordName.end(), wordName.begin(), toupper);
        }
        def.wordNamePrintVersion = wordName;
        std::transform(wordName.begin(), wordName.end(), wordName.begin(), toupper);
        dictionary->emplace(wordName, def);
        ssLine.ignore();
        ssPOfSpeech.ignore();
        ssPOfSpeech.clear();
        ssLine.clear();
    }
    ioFile.close();
        return true;
    } else
        return false;
}

/**
 * Validate part of speech
 * @param inputPartOfSpeech is a string representing part of speech input.
 * @return true if part of speech is true, false otherwise.
 */
bool validPartOfSpeech(const std::string inputPartOfSpeech) {
    for(int i = 0; i < 5; i++){
        if(isEqual(inputPartOfSpeech, partOfSpeechEnumStrings[i])) {
            return true;
        }
    }
    return false;
}

/**
 * Get part of speech value from partOfSpeech enum
 * @param pOfSpeech is string representing part of speech input.
 * @return partOfSpeech value.
 */
partOfSpeech getPartOfSpeechString(const std::string pOfSpeech) {
    if(isEqual(pOfSpeech, getStringForEnum(partOfSpeech::NOUN)))
        return partOfSpeech::NOUN;
    else if(isEqual(pOfSpeech, getStringForEnum(partOfSpeech::VERB)))
        return partOfSpeech::VERB;
    else if(isEqual(pOfSpeech, getStringForEnum(partOfSpeech::ADJECTIVE)))
        return partOfSpeech::ADJECTIVE;
    else if(isEqual(pOfSpeech, getStringForEnum(partOfSpeech::DEFAULT)))
        return partOfSpeech::DEFAULT;
    else
        return partOfSpeech::NOTVALID;
}

/**
 * Function used to get string value of partOfSpeech.
 * @param pOfSpeech to be converted to string
 * @return char* representing the string value of a particluar part of
 *         speech value.
 */
const char* getStringForEnum(partOfSpeech pOfSpeech){
    switch(pOfSpeech)
    {
        case partOfSpeech::NOUN:        return partOfSpeechEnumStrings[0];
        case partOfSpeech::VERB:        return partOfSpeechEnumStrings[1];
        case partOfSpeech::ADJECTIVE:   return partOfSpeechEnumStrings[2];
        case partOfSpeech::NOTVALID:    return partOfSpeechEnumStrings[3];
        case partOfSpeech::DEFAULT:     return partOfSpeechEnumStrings[4];
    };
}

/**
 * Function used to see if two strings are equal.
 * @param s1 string to be compared.
 * @param s2 string to be compared.
 * @return true if strings are equal, false otherwise.
 */
bool isEqual(const std::string& s1, const std::string& s2) {
    if(s1.size() != s2.size())
        return false;
    for (int i = 0; i < s1.size(); i++ ){
        if(toupper(s1[i]) != toupper(s2[i]))
            return false;
    }
    return true;
}

/**
 * Function used to control print output.
 * @param word iterator pointer for the word to be printed.
 * @param pOfSpeech part of speech value to be printed, if any.
 */
void printResults(const std::map<std::string, wordDescription>::iterator word, partOfSpeech pOfSpeech){
    switch (pOfSpeech) {
        case NOUN:        if (word->second.nouns.empty())
                              printWordNotFound();
                          else
                              printNouns(word);
                          break;
        case VERB:        if (word->second.verbs.empty())
                              printWordNotFound();
                          else
                              printVerbs(word);
                          break;
        case ADJECTIVE:   if (word->second.adjectives.empty())
                              printWordNotFound();
                          else
                              printAdjectives(word);
                          break;
        case NOTVALID:    printInvalidPartOfSpeech();
                          break;
        case DEFAULT:     printAll(word);
                          break;
    }

}

/**
 * Function used to print nouns.
 * @param word iterator pointer for the word to be printed.
 */
void printNouns(const std::map<std::string, wordDescription>::iterator word) {
    for(std::vector<std::string>::iterator nounItr = word->second.nouns.begin(); nounItr != word->second.nouns.end(); ++nounItr){
        std::cout << "\t" << word->second.wordNamePrintVersion << " [noun] : " << *nounItr << "." << std::endl;
    }
}

/**
 * Function used to print verbs.
 * @param word iterator pointer for the word to be printed.
 */
void printVerbs(const std::map<std::string, wordDescription>::iterator word) {
    for(std::vector<std::string>::iterator verbItr = word->second.verbs.begin(); verbItr != word->second.verbs.end(); ++verbItr){
        std::cout << "\t" << word->second.wordNamePrintVersion << " [verb] : " << *verbItr << "." << std::endl;
    }
}

/**
 * Function used to print adjectives.
 * @param word iterator pointer for the word to be printed.
 */
void printAdjectives(const std::map<std::string, wordDescription>::iterator word){
    for(std::vector<std::string>::iterator adjItr = word->second.adjectives.begin(); adjItr != word->second.adjectives.end(); ++adjItr){
        std::cout << "\t" << word->second.wordNamePrintVersion << " [adjective] : " << *adjItr << "." << std::endl;
    }
}

/**
 * Function used to print all data associated with the word.
 * @param word iterator pointer for the word to be printed.
 */
void printAll(const std::map<std::string, wordDescription>::iterator word) {
    if (!word->second.adjectives.empty()){
        printAdjectives(word);
    }
    if (!word->second.nouns.empty()){
        printNouns(word);
    }
    if (!word->second.verbs.empty()){
        printVerbs(word);
    }
}

/**
 * Function used to print the 'not found' message.
 */
void printWordNotFound() {
    std::cout << "\t<Not found>" << std::endl;
}

/**
 * Function used to print 'invalid part of speech' message.
 */
void printInvalidPartOfSpeech() {
    std::cout << "\t<2nd argument must be a part of speech>" << std::endl;
}

/**
 * Function used to print 'invalid input' message.
 */
void printInvalidInput() {
    std::cout << "\t<Please enter a search key (and a part of speech)>" << std::endl;
}

/**
 * Function used to 'clear' the screen.
 */
void clear(){
    std::cout << "\033\143" << std::endl;
    std::cout << "----- DICTIONARY 340 C++ ------" << "\n" << std::endl;
}

/**
 * Function used to print the 'thank you' message.
 */
void exitMessage() {
    std::cout << "\033\143" << std::endl;
    std::cout << "---------- THANK YOU ----------" << "\n" << std::endl;
}

/**
 * Function used to print the 'source file not found' message.
 */
void printSourceFileNotFoundMessage() {
    std::cout << "<Source file not found>" << std::endl;
}

/**
 * Function used to clear the screen in XCode.
 */
void clearXCodeConsole() {
    std::system("clear");
}

/**
 * Function used to print the 'exit' message.
 */
void exit(int number) {
    std::system("pause");
    _Exit(EXIT_SUCCESS);
}
