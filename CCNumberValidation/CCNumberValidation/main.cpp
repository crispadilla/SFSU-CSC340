//
//  main.cpp
//  CCNumberValidation
//
//  Created by Cris on 6/19/18.
//  Copyright © 2018 Cristobal Padilla. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>

bool isvalidcc(const std::string&);

int main()
{
    //
    // PLEASE DO NOT CHANGE main()
    //
    std::vector <std::string> cardnumbers = {
        "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
        "4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
        "5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
        "4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
        "5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
        "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
        "4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
        "5556551555555557", "6011316011016011"
    };
    
    int i;
    std::vector <std::string>::iterator itr;
    
    for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
        std::cout << std::setw(2)  << i << " "
        << std::setw(17) << *itr
        << ((isvalidcc(*itr)) ? " is valid" : " is not valid") << std::endl;
        
    }
    
    return 0;
}

 /**
 * Test credit card number pattern to see if it is valid.
  Step 1: Double every second digit from right to left. If doubling of a digit results in a two-digit number,
          add the two digits to get a single digit number.
  Step 2: Add all single-digit numbers from step 1.
  Step 3: Add all digits in the odd places from right to left in the credit card number.
  Step 4: Sum the results from step 2 and step 3.
  Step 5: If the result of step 4 is divisible by 10, the card number is valid; otherwhise, it is invalid.
 */

bool isvalidcc(const std::string& s){
    int     tmp = 0,
      sum_evens = 0,
       sum_odds = 0,
          total = 0;
    
    for(int even = (s.size() - 2), odd = (s.size() - 1) ; 0 <= even || 0 <= odd; even -= 2, odd -= 2) {
        // Step 1
        if(even >= 0) {
            tmp = 2 * std::stoi(s.substr(even, 1));
    
            // Step 2
            if(tmp >= 10){
                tmp = 1 + (tmp % 10);
                sum_evens += tmp;
            }
            else
                sum_evens += tmp;
        }
        // Step 3
        sum_odds += std::stoi(s.substr(odd, 1));
    }
    // Step 4
    total = sum_evens + sum_odds;

    // Step 5
    if(total % 10 == 0)
        return true;
    else
        return false;
}
