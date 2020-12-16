#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

struct Field {
    std::string name;
    int max1;
    int min1;
    int max2;
    int min2;
};

// Extract the rule for a field from a line
Field readRule(std::string rule){
    int colonPos = rule.find(":");
    int dashPos = rule.find("-");
    int orPos = rule.find(" or ");
    std::string name = rule.substr(0, colonPos);
    std::string min1 = rule.substr(colonPos+2, (dashPos - colonPos - 2));
    std::string max1 = rule.substr(dashPos+1, (orPos - dashPos - 2));
    std::string range2 = rule.substr(orPos+1, rule.size());
    dashPos = range2.find("-");
    std::string min2 = range2.substr(2, dashPos-2);
    std::string max2 = range2.substr(dashPos + 1, range2.size());
    Field newFeild = {
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

int main(){

    std::vector<Field> rules;
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
                Field newField = readRule(inputText);
                rules.push_back(newField);
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

    // Loop through the tickets
    int invalidTotal = 0;
    for(int i = 0; i < tickets.size(); i++){
        std::vector<int> ticket = tickets[i];

        // Loop through the fields in the ticket
        for(int j = 0; j < ticket.size(); j++){
            bool foundField = false;

            // Loop through the rules
            for(int k = 0; k < rules.size(); k++){

                // Check range 1
                if((ticket[j] <= rules[k].max1) && (ticket[j] >= rules[k].min1)){
                    foundField = true;
                    break;
                }

                // Check range 2
                if((ticket[j] <= rules[k].max2) && (ticket[j] >= rules[k].min2)){
                    foundField = true;
                    break;
                }
            }

            // If the field didnt match any rules
            if(!foundField){
                invalidTotal += ticket[j];
                break;
            }
        }
    }

    printf("The invalid fields add up to %d\n", invalidTotal);
    inputFile.close();
    return 1;
}
