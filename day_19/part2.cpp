#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

struct Node {
    int id;
    std::vector<int> childrenA;
    std::vector<int> childrenB;
    std::string value;
};

std::vector<Node> nodes;

// Get all the possible strings which match a given NODE recursively
std::vector<std::string> getAllCombos(int nodeID){
    Node node = nodes[nodeID];
    std::vector<std::string> combos;

    // Base case
    if(node.childrenA.empty() && node.childrenB.empty()){
        combos.push_back(node.value);
        return(combos);
    }

    // Recursive case
    std::vector<std::string> recursiveCombos;
    std::vector<std::string> newRecursiveCombos;
    for(int n = 0; n < 2; n++){

        // For each set of children
        std::vector<int> children = (n == 0)? node.childrenA : node.childrenB;
        if(!children.empty()){
            recursiveCombos.push_back("");

            // For each child in the list
            for(int i = 0; i < children.size(); i++){
                std::vector<std::string> childCombos = getAllCombos(children[i]);

                // Add all the combos of the child to all the combos found so far
                for(int j = 0; j < recursiveCombos.size(); j++){
                    for(int k = 0; k < childCombos.size(); k++){
                        std::string newCombo = recursiveCombos[j] + childCombos[k];
                        newRecursiveCombos.push_back(newCombo);
                    }
                }
                recursiveCombos = newRecursiveCombos;
                newRecursiveCombos.clear();
            }
        }
        if(recursiveCombos.size() > 0)
        combos.insert(combos.end(), recursiveCombos.begin(), recursiveCombos.end());
        recursiveCombos.clear();
    }
    return combos;
}

// Parse an input line representing a node
Node parseNode(std::string inputText){
    Node newNode;

    // Read in ID
    int colonPos = inputText.find(":");
    newNode.id = stoi(inputText.substr(0, colonPos));
    std::string rest = inputText.substr(colonPos + 2, inputText.size());

    // Read in value for terminating nodes
    newNode.value = "";
    if(inputText.find("\"") != std::string::npos){
        int quotePos = rest.find('"');
        newNode.value = rest.substr(quotePos + 1, rest.size() - quotePos - 2);
    }

    // Read in sequence
    else {
        std::stringstream ss(rest);
        std::string tokenText;
        bool second = false;
        while(std::getline(ss, tokenText, ' ')){
            if(tokenText == "|"){
                second = true;
            } else {
                int newNumber = stoi(tokenText);
                if(second){
                    newNode.childrenB.push_back(newNumber);
                } else {
                    newNode.childrenA.push_back(newNumber);
                }
            }
        }
    }
    return newNode;
}

// All combinations for rules 42 and 31
std::vector<std::string> all42s;
std::vector<std::string> all31s;

// Check if a string exactly matches rule 42 or 31
bool is42(std::string message){
    return std::find(all42s.begin(), all42s.end(), message) != all42s.end();
}
bool is31(std::string message){
    return std::find(all31s.begin(), all31s.end(), message) != all31s.end();
}

// Check if a string has one or more 31s
bool checkMatch31(std::string message, int count42, int count31){
    if(count42 <= count31 + 1){
        return false;
    }
    if(count42 <= 1){
        return false;
    }

    // Base case
    if(is31(message)){
        return true;
    }

    // Recursive case
    int index = 0;
    while(index <= message.size()){
        std::string possible31 = message.substr(0, index);
        if(is31(possible31)){

            // Found a possibility
            std::string remainingString = message.substr(index, message.size());
            bool rest31 = checkMatch31(remainingString, count42, count31+1);
            if(rest31){
                return true;
            }
        }
        index++;
    }
    return false;
}

// Check if a string has 1 or more 42s followed by 1 or more 31s
bool checkMatch42(std::string message, int count42){

    // Base case - message must end with 31
    if(is42(message)){
        return false;
    }

    // Recursive case
    int index = 0;
    while(index <= message.size()){
        std::string possible42 = message.substr(0, index);
        if(is42(possible42)){

            // Found a possibility
            std::string remainingString = message.substr(index, message.size());
            if(checkMatch31(remainingString, count42+1, 0)){
                return true;
            }
            if(checkMatch42(remainingString, count42+1)){
                return true;
            }

        }
        index++;
    }
    return false;
}

int main(){
    // Initialise nodes vector
    int numberOfNodes = 150;
    for(int i = 0; i < numberOfNodes; i++){
        Node newNode;
        newNode.id = -1;
        nodes.push_back(newNode);
    }

    // Read in file
    std::vector<std::string> messages;
    std::string inputText;
    std::ifstream inputFile("input.txt");
    while (getline(inputFile, inputText)) {

        // Read in a node
        if(inputText.find(":") != std::string::npos){
            Node newNode = parseNode(inputText);
            //printf("ID%d\n", newNode.id);
            nodes[newNode.id] = newNode;
        }

        // Read in the strings to try and match
        else if(inputText.size() > 0){
            messages.push_back(inputText);
        }

    }
    inputFile.close();

    // Get all the possible combinations for rules 42 and 31
    all42s = getAllCombos(42);
    all31s = getAllCombos(31);

    // Check each message
    int matches = 0;
    for(int j = 0; j < messages.size(); j++){
        if(checkMatch42(messages[j],0)){
            matches++;
        }
    }
    printf("%d / %lu messages match\n", matches, messages.size());
    return 1;
}
