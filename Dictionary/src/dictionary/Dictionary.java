/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dictionary;

import java.util.HashMap;
import java.util.Map;

/**
 *
 * @author cristobalpadilla
 */
public class Dictionary extends HashMap<String, Dictionary.Word>{

    /**
     * Value used to show entry not found.
     */
    protected static final String ENTRY_NOT_FOUND_VALUE = "<Not found>";        
    protected static final String ENTRY_NOT_PART_OF_SPEECH = "<2nd argument must be part of speech>";
    
    // All possible combinations of nouns, verbs, and adjectives.
    protected enum PrintOrder {NAV, NVA, ANV, AVN, VAN, VNA}   
    
    // Enum used for holding all the word used in the dictionary. 
    protected enum Word {
        CSC210("CSC210", new String[] {"Intro to Java"}, new String[] {"To learn Java"}, new String[] {"Comforable with Objects and Classes","Ready for CSC 220"}, PrintOrder.NVA),
        CSC220("CSC220", new String[] {"Data Structures"}, new String[] {"To create data structures"}, new String[] {"Ready to create complex data structures"}, PrintOrder.NAV),
        CSC340("CSC340", new String[] {"A CS upper division course", "Many hours outside of class"}, null, new String[] {"= C++ version of CSC210 + CSC 220 + more"}, PrintOrder.AVN),
        BOOK("Book", new String[] {"A set of pages"}, new String[] {"To arrange something on a particular date"}, null,PrintOrder.NAV),
        BOOKBINDER("BookBinder", new String[] {"A person who fastens the pages of books"}, null, null,PrintOrder.NAV),
        BOOKABLE("Bookable", null, null, new String[] {"Can be ordered"}, PrintOrder.NAV),
        BOOKCASE("Bookcase", new String[] {"A piece of furniture with shelves"}, null, null, PrintOrder.NAV);
        
        private String name;              // Printable. 
        private String[] nouns;           // Array to hold nouns.
        private String[] verbs;           // Array to hold verbs.
        private String[] adjectives;      // Array to hold adjectives.
        private PrintOrder printOrder;    // Variable for Ordr of Print.
        
        private Word(String name, String[] nouns, String[] verbs, String[] adjectives, PrintOrder printOrder){
            this.name = name;
            this.nouns = nouns;
            this.verbs = verbs;
            this.adjectives = adjectives;
            this.printOrder = printOrder;
        }
        
        public String getName(){
            return name;
        }
        
        public String[] getNouns(){
            return nouns;
        }
            
        public String[] getVerbs(){
            return verbs;
        }
            
        public String[] getAdjectives(){
            return adjectives;
        } 
        
        public PrintOrder getPrintOrder(){
            return printOrder;
        }
        
        public void setName(String name){
            this.name = name;
        }
        
        public void setNouns(String[] nouns){
            this.nouns = nouns;
        }
        
        public void setVerbs(String[] verbs){
            this.verbs = verbs;
        }
        
        public void setAdjetives(String[] adjectives){
            this.adjectives = adjectives;
        }
        
        public void setPrintOrder(PrintOrder printOrder){
            this.printOrder = printOrder;
        }
    }       
    
    public Dictionary(){
        super();
        fillDictionary();
    }
    
    public Dictionary(int initialCapacity){
        super(initialCapacity);
        fillDictionary();
    }
    
    public Dictionary(Map<String, Word> m){
        super(m);
    }
    
    /**
     * Load the dictionary HashMap with words from the Word enum.
     */
    private void fillDictionary(){
        for(Word w : Word.values()){
            this.put(w.name(), w);
        }
    }
}