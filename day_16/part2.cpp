#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

struct Rule {
    std::string name;
    int max1;
    int min1;
    int max2;
    int min2;
};

// Extract the rule for a field from a line
Rule readRule(std::string rule){
    int colonPos = rule.find(":");
    int dashPos = rule.find("-");
    int orPos = rule.find(" or ");
    std::string name = rule.substr(0, colonPos);
    std::string min1 = rule.substr(colonPos+2, (dashPos - colonPos - 2));
    std::string max1 = rule.substr(dashPos+1, (orPos - dashPos - 1));
    std::string range2 = rule.substr(orPos+1, rule.size());
    dashPos = range2.find("-");
    std::string min2 = range2.substr(2, dashPos-2);
    std::string max2 = range2.substr(dashPos + 1, range2.size());
    //printf(">%s< >%s< >%s< >%s< >%s<\n", name.c_str(), min1.c_str(), max1.c_str(), min2.c_str(), max2.c_str());
    Rule newFeild = {
        name, stoi(max1), stoi(min1), stoi(max2), stoi(min2)
    };
    return newFeild;
}

// Extract a ticket from a line
std::vector<int> readTicket(std::string ticketString){
    std::vector<int> ticket;
    std::stringstream ss(ticketString);
    std::string tokenText;
    while(std::getline(ss, tokenText, ',')){
        ticket.push_back(stoi(tokenText));
    }
    return ticket;
}

// Get a mapping from rules to ticket columns
std::vector<int> getRuleMapping(std::vector<Rule> rules, std::vector<std::vector<int> > validTickets){

    int numRules = rules.size();
    int rulesMapped = 0;                  // Once all rules are mapped to columns, we stop
    std::vector<bool> ticketColumnMapped; // Track which ticket columns have been mapped to
    std::vector<int> ruleMap;             // Track which rule maps to which column

    // Initialise ruleMap[] to -1, and ticketColumMapped[] to false
    for(int i = 0; i < numRules; i++){
        ruleMap.push_back(-1);
        ticketColumnMapped.push_back(false);
    }

    // Loop until we have mapped all but one
    while(rulesMapped < numRules - 1){

        // Track the possible columns which each rule could map to and count how
        // many rules could match to each column
        std::vector<std::vector<bool> > allPossibilities;
        std::vector<int> possibilityCount;
        for(int i = 0; i < numRules; i++){
            possibilityCount.push_back(0);
        }

        // Loop over the ticket columns
        for(int i = 0; i < numRules; i++){

            // Skip it if we have already done it
            if(ticketColumnMapped[i]){
                continue;
            }

            // Initialise possibilities vector
            // This represents all the possible columns for this ticket rule
            std::vector<bool> possibilities;
            for(int i = 0; i < numRules; i++){
                if(ruleMap[i] < 0){
                    possibilities.push_back(true);
                } else {
                    possibilities.push_back(false);
                }
            }

            // Loop over tickets
            for(int t = 0; t < validTickets.size(); t++){
                int thisTicket = validTickets[t][i]; // Get the column we are checking

                // Loop through the rules
                for(int r = 0; r < numRules; r++){

                    // Skip if this rule is already mapped or this column has been ruled out
                    if((ruleMap[r] > -1) || !possibilities[r]){
                        continue;
                    }

                    Rule rule = rules[r];

                    // Check if column i, of ticket t, matches rule r
                    bool valid = false;
                    if(((thisTicket <= rule.max1) && (thisTicket >= rule.min1)) ||
                       ((thisTicket <= rule.max2) && (thisTicket >= rule.min2))){
                        valid = true;
                    }

                    // If it doesnt match, this column cannot possibly be this rule
                    if(!valid){
                        possibilities[r] = false;
                    }
                } // End loop over rules (r)
            } // End loop over tickets (t)

            // Check how many possible rules this column could match
            int possibleCount = 0;
            int possibleOne = 0;
            for(int p = 0; p < numRules; p++){
                if(possibilities[p]){
                    possibilityCount[p]++;
                    possibleCount++;
                    possibleOne = p;
                }
            }

            // If this column only matches one rule then add this info to the maps
            if(possibleCount == 1){
                ticketColumnMapped[i] = true;
                ruleMap[possibleOne] = i;
                rulesMapped++;
            }

            allPossibilities.push_back(possibilities);

        } // End loop over ticket columns (i)


        // If any column has one possibile rule that no other columns have, then
        // that column must map to that rule
        for(int i = 0; i < allPossibilities.size(); i++){
            std::vector<bool> colPossibilities = allPossibilities[i];
            for(int j = 0; j < colPossibilities.size(); j++){

                // If this column mapped to this rule and it was the only column to do so
                // then thats a match, add this info to the maps
                if(colPossibilities[j] && (possibilityCount[j] == 1)){
                    ticketColumnMapped[i] = true;
                    ruleMap[j] = i;
                    rulesMapped++;
                }
            }
        }
    } // End big while


    // Get the final mapping by elimination
    for(int i = 0; i < ruleMap.size(); i++){

        // Find the one unmapped rule
        if(ruleMap[i] == -1){
            for(int j = 0; j < ticketColumnMapped.size(); j++){

                // Match it the one unmapped column
                if(!ticketColumnMapped[j]){
                    ruleMap[i] = j;
                    break;
                }
            }
        }
    }

    return ruleMap;
}

int main(){

    std::vector<Rule> rules;
    std::vector<std::vector<int> > tickets;
    std::vector<int> myTicket;

    bool readAllInputs = false;
    bool readMyTicket = false;

    // Read file
    std::string inputText;
    std::ifstream inputFile("input.txt");
    while (getline(inputFile, inputText)) {

        if(!readAllInputs){ // Read in the rules
            if(inputText.size() == 0){
                readAllInputs = true;
            } else {
                Rule newRule = readRule(inputText);
                rules.push_back(newRule);
            }

        } else if(!readMyTicket){ // Read in my ticket
            if(inputText.size() == 0){
                readMyTicket = true;
            } else if(inputText[0] != 'y'){
                myTicket = readTicket(inputText);
            }

        } else { // Read in the other tickets
            if(inputText[0] != 'n'){
                std::vector<int> newTicket = readTicket(inputText);
                tickets.push_back(newTicket);
            }
        }
    }

    // Loop through the tickets to filter out the valid ones
    std::vector<std::vector<int> > validTickets;
    for(int i = 0; i < tickets.size(); i++){
        std::vector<int> ticket = tickets[i];
        bool invalidTicket = false;

        // Loop through the fields in the ticket
        for(int j = 0; j < ticket.size(); j++){
            bool foundRule = false;

            // Loop through the rules
            for(int k = 0; k < rules.size(); k++){

                // Check range 1
                if((ticket[j] <= rules[k].max1) && (ticket[j] >= rules[k].min1)){
                    foundRule = true;
                    break;
                }

                // Check range 2
                if((ticket[j] <= rules[k].max2) && (ticket[j] >= rules[k].min2)){
                    foundRule = true;
                    break;
                }
            }

            // If the field didnt match any rules
            if(!foundRule){
                invalidTicket = true;
                break;
            }
        }

        if(!invalidTicket){
            validTickets.push_back(ticket);
        }
    }

    // Multiply up the column values which map to the departure info
    std::vector<int> fieldMap = getRuleMapping(rules, validTickets);
    long long total = 1;
    for(int i = 0; i < 6; i++){
        total *= myTicket[fieldMap[i]];
    }

    printf("Multiplied departure info: %lld\n", total);

    inputFile.close();
    return 1;
}
