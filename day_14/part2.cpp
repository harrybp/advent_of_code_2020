#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// Recursive function to expand a string with X's in to all possible
// combinations of replacing the X's with either 0's or 1's
std::vector<std::string> getAllCombos(std::string bitMask){
    std::vector<std::string> combos;
    bool foundX = false;
    for(int i = 0; i < bitMask.size(); i++){

        // When an X is found
        if(bitMask[i] == 'X'){
            foundX = true;

            // Create two versions of the string, where the X is either 0 or 1
            std::string newMask0 = bitMask;
            std::string newMask1 = bitMask;
            newMask0[i] = '0';
            newMask1[i] = '1';

            // Call the function again on each of these strings and append result
            std::vector<std::string> newMasks0 = getAllCombos(newMask0);
            std::vector<std::string> newMasks1 = getAllCombos(newMask1);
            combos.insert(combos.end(), newMasks0.begin(), newMasks0.end());
            combos.insert(combos.end(), newMasks1.begin(), newMasks1.end());
            break;
        }
    }

    // Base case
    if(!foundX){
        combos.push_back(bitMask);
    }

    return combos;
}

int main(){

    std::map<unsigned long, unsigned long> memory;
    std::vector<unsigned long> orMasks;
    std::string mask;

    // Read file
    std::string inputText;
    std::ifstream inputFile("input.txt");
    while (getline(inputFile, inputText)) {

        // MASK
        if(inputText[1] == 'a'){
            std::string bitMask = inputText.substr(7, inputText.size());
            std::string orMaskStr = bitMask;
            mask = bitMask;

        // MEM WRITE
        } else if(inputText[1] == 'e'){
            // Get addr and data strings
            int closeBracket = inputText.find(']');
            std::string addrStr = inputText.substr(4, closeBracket - 4);
            std::string dataStr = inputText.substr(closeBracket + 4, inputText.size());
            unsigned long addr = stol(addrStr);
            unsigned long data = stol(dataStr);

            // Convert address to binary string and do a manual OR
            addrStr = std::bitset<36>(addr).to_string();
            for(int i = 0; i < addrStr.size(); i++){
                if((mask[i] == '1') || (mask[i] == 'X')){
                    addrStr[i] = mask[i];
                }
            }

            // Expand the address into all possible combinations
            std::vector<std::string> allCombos = getAllCombos(addrStr);
            for(int i = 0; i < allCombos.size(); i++){

                // Insert data into memory at this address
                unsigned long newAddr = stol(allCombos[i], 0, 2);
                if(!memory.insert(std::make_pair<unsigned long, unsigned long>(newAddr, data)).second){
                    memory[newAddr] = data;
                }
            }
        }
    }

    // Total up all the data in memory
    unsigned long total = 0;
    std::map<unsigned long, unsigned long>::iterator it;
    for(it = memory.begin(); it != memory.end(); it++){
        total += it->second;
    }

    printf("The total of all data in memory is %ld\n", total);
    inputFile.close();
    return 1;
}
