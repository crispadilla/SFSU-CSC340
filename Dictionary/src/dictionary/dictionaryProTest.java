/*
 * Program simulates a dictionary.
 * Takes String input from user to be searched for 
 * in the dictionary. Program prints either the nouns, verbs,
 * or adjectives associated with the word if found, or a 'not found'
 * message otherwise.
 */
package dictionary;

import java.util.Scanner;

/**
 *
 * @author cristobalpadilla
 */
public class dictionaryProTest {
    private Dictionary dictionary;
    private enum PartOfSpeech { NOUN, VERB, ADJECTIVE, DEFAULT}; 
    
    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args) {
        // TODO code application logic here
        dictionaryProTest test = new dictionaryProTest();
        test.dictionary = new Dictionary();
        Scanner in = new Scanner(System.in);
        String line;
        String delims = "[ ]+";
        String[] tokens;
        boolean keepSearching = true;
   
        System.out.println("-----DICTIONARY 340 PRO-----" + "\n");
        while(keepSearching){
            System.out.print("Search: ");
            line = in.nextLine();
            tokens = line.split(delims);
            
            if(!line.isEmpty() && tokens[0].equalsIgnoreCase("!q")){
                keepSearching = false;
                continue;
            } else if(!line.isEmpty()) {
                System.out.printf("%9s\n", "|");
                test.checkInput(test.dictionary, tokens);
                System.out.printf("%9s\n", "|");
            }
        }
        System.out.println("\n" + "-----THANK YOU-----");
    }
    
    /**
     * Checks input given by the user for correctness, namely the 
     * the word to be searched and the 'part of speech' entry.
     * @param dictionary Repository to be searched.
     * @param tokens String array used to hold user's input.
     */
    public void checkInput(Dictionary dictionary, String[] tokens){
        if(tokens.length == 1){
            if(searchDictionary(dictionary, tokens[0]))
                //printResult(dictionary, tokens[0], PartOfSpeech.DEFAULT.name());
                printResult(dictionary.get(tokens[0].toUpperCase()), PartOfSpeech.DEFAULT);
            else
                printNoEntryFoundMessage();
        }    
        else {
            if(!validatePartOfSpeech(tokens[1])){
                printInvalidPartOfSpeechMessage();
            } 
            else if(searchDictionary(dictionary, tokens[0]))
                printResult(dictionary.get(tokens[0].toUpperCase()), PartOfSpeech.valueOf(tokens[1].toUpperCase()));
            else
                printNoEntryFoundMessage();
        }
    }
    
    /**
     * Searches for user input in the dictionary. 
     * @param dictionary Repository to be searched.
     * @param entry String to be searched for in the dictionary.
     * @return True if entry is in the dictionary; false otherwise.
     */
    public boolean searchDictionary(Dictionary dictionary, String entry){
        if(dictionary.containsKey(entry.toUpperCase()))
            return true;    
        else 
            return false;
    }
    
    /**
     * Validates 'part of speech' entry.
     * @param pOfSpeech String denoting 'part of speech'.
     * @return True if 'part of speech' is correct; false otherwise.
     */
    private boolean validatePartOfSpeech(String pOfSpeech){
        for(PartOfSpeech p : PartOfSpeech.values()){
            if(pOfSpeech.equalsIgnoreCase(p.name()))
                return true;
        }
        return false;
    }
    
    /**
     * Prints the nouns, verbs, and adjectives, if found, associated with
     * the input given by the user, in that order.
     * @param word String to be searched for in the dictionary.
     * @param pOfSpeech String denoting 'part of speech'.
     */
    public void printResult(Dictionary.Word word, PartOfSpeech pOfSpeech){
        switch (pOfSpeech){
            case NOUN:      printNouns(word);
                            break;
            case VERB:      printVerbs(word);
                            break;
            case ADJECTIVE: printAdjectives(word);
                            break;
            case DEFAULT:   printAllAvailable(word);
                            break;    
        }
    }
    
    /** 
     * Prints all the nouns associated with the word.
     * @param word
     */
    private void printNouns(Dictionary.Word word){
        String str = "";
        if(word.getNouns() != null){
            for(int i = 0; i < word.getNouns().length; i++){
                if(i == (word.getNouns().length - 1))
                    str += word.getNouns()[i] + ".";
                else
                    str += word.getNouns()[i] + ", ";
            }
            System.out.println("\t " + word.getName() + " [noun] : " + str);
        } else {
            printNoEntryFoundMessage();
        }
    }
    
    /**
     * Prints all the verbs associated with the word.
     * @param word  
     */
    private void printVerbs(Dictionary.Word word){
        String str = "";
        if(word.getVerbs() != null){
            for(int i = 0; i < word.getVerbs().length; i++){
                if(i == (word.getVerbs().length - 1))
                    str += word.getVerbs()[i] + ".";
                else
                    str += word.getVerbs()[i] + ", ";
            }
            System.out.println("\t " + word.getName() + " [verb] : " + str);
        } else {
            printNoEntryFoundMessage();
        }
    }
    
    /**
     * Prints the adjectives associated with the word.
     * @param word 
     */
    private void printAdjectives(Dictionary.Word word){
        String str = "";
        if(word.getAdjectives() != null){
            for(int i = 0; i < word.getAdjectives().length; i++){
                if(i == (word.getAdjectives().length - 1))
                    str += word.getAdjectives()[i] + ".";
                else
                    str += word.getAdjectives()[i] + ", ";
            }
            System.out.println("\t " + word.getName() + " [adjective] : " + str);
        } else {
            printNoEntryFoundMessage();
        }
    }
    
    /**
     * Prints all available data associated with the word (verbs, nouns, adjectives).
     * @param word 
     */
    private void printAllAvailable(Dictionary.Word word){
        if(word.getVerbs() != null)
            printVerbs(word);
        
        if(word.getNouns() != null)
            printNouns(word);
        
        if(word.getAdjectives() != null)
            printAdjectives(word);
    }
    
    /**
     * Used to print the "No Entry Found" message.
     */
    private void printNoEntryFoundMessage(){
        System.out.println("\t " + Dictionary.ENTRY_NOT_FOUND_VALUE);
    }
    
    /**
     * Used to print the "Invalid Part of Speech" message.
     */
    private void printInvalidPartOfSpeechMessage(){
        System.out.println("\t " + Dictionary.ENTRY_NOT_PART_OF_SPEECH);
    }
}
