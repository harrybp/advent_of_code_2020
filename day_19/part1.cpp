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

// Print out a node's ID and children
void printNode(Node node){
    printf("%d : %s :\nA: ",node.id, node.value.c_str());
    for(int i = 0; i < node.childrenA.size(); i++){
        printf("%d, ", node.childrenA[i]);
    }
    printf("\nB: ");
    for(int i = 0; i < node.childrenB.size(); i++){
        printf("%d, ", node.childrenB[i]);
    }
    printf("\n\n");
}

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
    for(int i = 0; i < 2; i++){

        // For each set of children
        std::vector<int> children = (i == 0)? node.childrenA : node.childrenB;
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

int main(){
    // Initialise nodes vector
    int numberOfNodes = 150;
    for(int i = 0; i < numberOfNodes; i++){
        Node newNode;
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
            nodes[newNode.id] = newNode;
        }

        // Read in the strings to try and match
        else if(inputText.size() > 0){
            messages.push_back(inputText);
        }

    }
    inputFile.close();

    // Check each message against the list of all possible messages
    std::vector<std::string> allCombos = getAllCombos(0);
    std::sort(allCombos.begin(), allCombos.end());
    int matches = 0;
    for(int j = 0; j < messages.size(); j++){
        if(std::binary_search(allCombos.begin(), allCombos.end(), messages[j])){
            matches++;
        }
    }
    printf("%d messages match\n", matches);
    return 1;
}

