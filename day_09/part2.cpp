#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main(){
    // This is our answer from part1
    int faultyNumber = 41682220;

    // Read file into vector of longs
    std::string inputText;
    std::ifstream inputFile("input.txt");
    std::vector<long> numbers;
    while (getline(inputFile, inputText)) {
        long newNumber = std::stol(inputText);
        numbers.push_back(newNumber);
    }

    // Keep incrementing the start point until we find the range
    bool found = false;
    int startPoint = 0;
    while(!found){
        int total = 0;
        int index = startPoint;

        // Increase the size of the range until we find or exceed the number
        while(total < faultyNumber){
            total += numbers[index];
            index++;
        }

        // If we find the number, get the largest and smallest numbers from range
        if(total == faultyNumber){
            long smallest = LONG_MAX;
            long largest = 0;
            for(int i = startPoint; i < index; i++){
                if(numbers[i] > largest){
                    largest = numbers[i];
                }
                if(numbers[i] < smallest){
                    smallest = numbers[i];
                }
            }
            printf("Sum: %ld\n", largest+smallest);
            found = true;
        }
        startPoint++;
    }
    inputFile.close();
    return 1;
}
