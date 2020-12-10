#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main(){
    int preambleSize = 25;

    // Read file into vector of longs
    std::string inputText;
    std::ifstream inputFile("input.txt");
    std::vector<long> numbers;
    while (getline(inputFile, inputText)) {
        long newNumber = std::stol(inputText);
        numbers.push_back(newNumber);
    }

    // For each number, sum it up with the 25 numbers that follow it and
    // store these sums to be checked later
    std::vector<std::vector<long> > sums;
    for(int i = 0; i < numbers.size(); i++){
        int next = i + preambleSize;
        next = next >= numbers.size()? numbers.size() : next;
        std::vector<long> newSums;
        for(int j = i + 1; j < next; j++){
            newSums.push_back(numbers[i] + numbers[j]);
        }
        sums.push_back(newSums);
    }

    // Loop over the numbers, check the stored sums for each of the preceding
    // 25 numbers to see if they contain the number
    for(int i = preambleSize; i < numbers.size(); i++){
        bool found = false;
        for(int j = i - preambleSize; j < i; j++){
            for(int k = 0; k < sums[j].size(); k++){
                if(numbers[i] == sums[j][k]){
                    found = true;
                    break;
                }
            }
        }
        if(!found){
            printf("Failed at %ld\n", numbers[i]);
            break;
        }
    }

    inputFile.close();
    return 1;
}
