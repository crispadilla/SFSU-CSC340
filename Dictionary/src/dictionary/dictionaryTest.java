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
 * @author cristobalpadilla
 */
public class dictionaryTest {
    private Dictionary dictionary;
    /**
     * @param args the command line arguments
     */
    
    public static void main(String[] args) {
        // TODO code application logic here
        dictionaryTest test = new dictionaryTest();
        test.dictionary = new Dictionary();
        Scanner in = new Scanner(System.in);
        String input = "search";
        System.out.println("-----DICTIONARY 340 Standard-----" + "\n");
        
        while(!input.equalsIgnoreCase("!q")){
            System.out.print("Search: ");
            input = in.next();
            if(test.searchDictionary(test.dictionary, input))
                test.printResult(test.dictionary.get(input.toUpperCase()));
            else if(!input.equalsIgnoreCase("!q"))
                test.printNoEntryFoundMessage();
        }
        
        System.out.println("\n" + "-----THANK YOU-----");
    }
    
    /** 
     * Searches dictionary to see if entry is a member.
     * @param dictionary Repository to be searched.
     * @param entry Entry to be found.
     * @return boolean True if entry inside dictionary, false otherwise.
     */
    public boolean searchDictionary(Dictionary dictionary, String entry){
        if(dictionary.containsKey(entry.toUpperCase()))
            return true;    
        else 
            return false;
    }
    
    /** 
     * Print all the available nouns, verbs, and adjectives associated
     * with the word using the word's print order.
     * @param word 
     */
    public void printResult(Dictionary.Word word){
        System.out.printf("%9s\n", "|");
        if(word.getPrintOrder() == Dictionary.PrintOrder.NVA) {
            printNouns(word);
            printVerbs(word);
            printAdjectives(word);
        } else if(word.getPrintOrder() == Dictionary.PrintOrder.AVN) {
            printAdjectives(word);
            printVerbs(word);
            printNouns(word);
        } else {
            printNouns(word);
            printAdjectives(word);
            printVerbs(word);
        }
        System.out.printf("%9s\n", "|");
    }
    
    /** 
     * Prints all the nouns associated with the word.
     * @param word
     */
    private void printNouns(Dictionary.Word word){
        if(word.getNouns() != null){
            for(int i = 0; i < word.getNouns().length; i++){
                System.out.println("\t " + word.getName() + " : " + word.getNouns()[i] + ".");
            }
        }
    }
    
    /**
     * Prints all the verbs associated with the word.
     * @param word  
     */
    private void printVerbs(Dictionary.Word word){
        if(word.getVerbs() != null){
            for(int i = 0; i < word.getVerbs().length; i++){
                System.out.println("\t " + word.getName() + " : " + word.getVerbs()[i] + ".");
            }
        }
    }
    
    /**
     * Prints the adjectives associated with the word.
     * @param word 
     */
    private void printAdjectives(Dictionary.Word word){
        if(word.getAdjectives() != null){
            for(int i = 0; i < word.getAdjectives().length; i++){
                System.out.println("\t " + word.getName() + " : " + word.getAdjectives()[i] + ".");
            }
        }
    }
    
    /**
     * Used to print the "No Entry Found" message.
     */
    private void printNoEntryFoundMessage(){
        System.out.printf("%9s\n", "|");
        System.out.println("\t " + Dictionary.ENTRY_NOT_FOUND_VALUE);
        System.out.printf("%9s\n", "|");
    }
}