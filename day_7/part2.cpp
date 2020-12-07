#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

struct Contents {
    std::string name;
    int amount;
};

std::map<std::string,std::vector<Contents>> bagInfo;

// Parse Input
void getBagInfo(std::string filename){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile(filename);
    std::map<std::string,std::vector<Contents>> newBagInfo;

    // Loop through lines in file
    while (getline(inputFile, inputText)) {
        if(inputText.size() > 0){

            std::string bag;
            std::vector<Contents> contents;

            // Get bag name
            int index = inputText.find("s contain ");
            bag = inputText.substr(0, index);

            // Get bag contents
            if(inputText.find("other bags") == std::string::npos){

                // Get amount of this bag
                int amount = stoi(inputText.substr(index + 10, 1));
                inputText = inputText.substr(index + 12, inputText.size());

                index = inputText.find(", ");
                while(index != std::string::npos){

                    // Get name of this bag
                    std::string newBag = inputText.substr(0, index);

                    // Replace bags with bag
                    if(newBag.find("bags") != std::string::npos){
                        newBag = newBag.substr(0, newBag.size() - 1);
                    }
                    contents.push_back({newBag, amount});

                    // Get amount of next bag
                    amount = stoi(inputText.substr(index + 2, 1));
                    inputText = inputText.substr(index + 4, inputText.size());
                    index = inputText.find(", ");

                }

                // Get name of final bag
                std::string newBag = inputText.substr(0, inputText.size() - 1);

                // Replace bags with bag
                if(newBag.find("bags") != std::string::npos){
                    newBag = newBag.substr(0, newBag.size() - 1);
                }
                contents.push_back({newBag, amount});
            }
            newBagInfo.insert(std::make_pair(bag, contents));
        }
    }
    bagInfo = newBagInfo;
}

// Recursive bag counting method
int bagContains(std::string bag){
    int contains = 1;
    std::vector<Contents> contents = bagInfo[bag];
    for(Contents contained : contents){
       contains += contained.amount * bagContains(contained.name);
    }
    return contains;
}


int main(){
    // Get bag info
    getBagInfo("input.txt");
    std::map<std::string,std::vector<Contents>>::iterator it;

    // Search all bags for gold bag
    std::string searchString = "shiny gold bag";
    int amount = bagContains(searchString);

    printf("%s contains %d bags\n", searchString.c_str(), amount - 1);
    return 1;
}
