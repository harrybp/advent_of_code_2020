#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>


int main(){

    std::map<int, unsigned long> memory;
    unsigned long orMask = 0;
    unsigned long andMask = 0;

    // Read file
    std::string inputText;
    std::ifstream inputFile("input.txt");
    while (getline(inputFile, inputText)) {

        // MASK
        if(inputText[1] == 'a'){
            std::string bitMask = inputText.substr(7, inputText.size());
            std::string orMaskStr = bitMask;
            std::string andMaskStr = bitMask;

            // Create and and or mask
            std::replace(orMaskStr.begin(), orMaskStr.end(), 'X', '0');
            std::replace(andMaskStr.begin(), andMaskStr.end(), 'X', '1');
            andMask = stol(andMaskStr,0, 2);
            orMask = stol(orMaskStr,0, 2);

        // MEM WRITE
        } else if(inputText[1] == 'e'){
            // Get addr and data write
            int closeBracket = inputText.find(']');
            std::string addrStr = inputText.substr(4, closeBracket - 4);
            std::string dataStr = inputText.substr(closeBracket + 4, inputText.size());
            int addr = stoi(addrStr);
            unsigned long data = stol(dataStr);

            // Apply masks
            data = data | orMask;
            data = data & andMask;

            // Insert into memory
            if(!memory.insert(std::make_pair<int, unsigned long>(addr, data)).second){
                memory[addr] = data;
            }
        }
    }

    // Total up all the data in memory
    unsigned long total = 0;
    std::map<int, unsigned long>::iterator it;
    for(it = memory.begin(); it != memory.end(); it++){
        total += it->second;
    }

    printf("The total of all data in memory is %ld\n", total);

    inputFile.close();
    return 1;
}
