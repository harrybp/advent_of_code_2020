#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main(){

    // Read file into vector of ints
    std::string inputText;
    std::ifstream inputFile("input.txt");
    std::vector<int> adaptors;
    while (getline(inputFile, inputText)) {
        int newAdaptor = std::stoi(inputText);
        adaptors.push_back(newAdaptor);
    }

    // Sort the vector
    std::sort(adaptors.begin(), adaptors.end());

    // Count the differences
    int oneJolt = 0;
    int threeJolt = 1;
    int previousJoltage = 0;
    for(int i = 0; i < adaptors.size(); i++){
        int difference = adaptors[i] - previousJoltage;
        previousJoltage = adaptors[i];
        if(difference == 1){
            oneJolt++;
        } else if(difference == 3){
            threeJolt++;
        }
    }

    printf("One Jolt: %d, Three Jolt: %d. Answer: %d\n", oneJolt, threeJolt, oneJolt*threeJolt);
    inputFile.close();
    return 1;
}
