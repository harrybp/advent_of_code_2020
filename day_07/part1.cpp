#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

std::map<std::string,std::vector<std::string>> bagInfo;

void getBagInfo(std::string filename){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile(filename);
    std::map<std::string,std::vector<std::string>> newBagInfo;

    // Loop through lines in file
    while (getline(inputFile, inputText)) {
        if(inputText.size() > 0){

            std::string bag;
            std::vector<std::string> contents;

            // Get bag name
            int index = inputText.find("s contain ");
            bag = inputText.substr(0, index);
            inputText = inputText.substr(index + 12, inputText.size());

            // Get bag contents
            if(inputText.find("other bags") == std::string::npos){

                index = inputText.find(", ");
                while(index != std::string::npos){
                    std::string newBag = inputText.substr(0, index);

                    // Replace bags with bag
                    if(newBag.find("bags") != std::string::npos){
                        newBag = newBag.substr(0, newBag.size() - 1);
                    }
                    contents.push_back(newBag);
                    inputText = inputText.substr(index + 4, inputText.size());
                    index = inputText.find(", ");

                }
                std::string newBag = inputText.substr(0, inputText.size() - 1);

                // Replace bags with bag
                if(newBag.find("bags") != std::string::npos){
                    newBag = newBag.substr(0, newBag.size() - 1);
                }
                contents.push_back(newBag);
            }
            newBagInfo.insert(std::make_pair(bag, contents));
        }
    }
    bagInfo = newBagInfo;
}

// Recursive Bag Search
bool bagContains(std::string bag, std::string target){

    // Base case (this is the target bag)
    if(bag == target){
        return true;
    }

    // Recursive case, check each contained bag
    std::vector<std::string> contents = bagInfo[bag];
    for(std::string contained : contents){
        if(bagContains(contained, target)){
            return true;
        }
    }

    // Fail otherwise
    return false;
}


int main(){
    // Get bag info
    getBagInfo("input.txt");
    std::map<std::string,std::vector<std::string>>::iterator it;

    // Search all bags for gold bag
    int total = 0;
    std::string searchString = "shiny gold bag";
    for(it = bagInfo.begin(); it != bagInfo.end(); it++){
        if(bagContains(it->first, searchString)){
            total++;
        }
    }

    printf("%d bags contain a %s\n", total - 1, searchString.c_str());
    return 1;
}
