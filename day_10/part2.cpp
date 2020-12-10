#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<int> adaptors;
std::vector<long> savedPaths;

// Recursive path length function
long getNumberOfPaths(int index){

    // Zero is the base case
    if(adaptors[index] == 0){
        return 1;
    }

    // Recursive case
    long paths = 0;
    int iterator = index + 1;

    // Loop over the adaptors which are within the 3 joltage
    while((adaptors[iterator] >= adaptors[index] - 3) && (iterator < adaptors.size())){

        // Check the saved paths before calling recursively
        if(savedPaths[iterator] > 0){
            paths += savedPaths[iterator];
        } else {
            paths += getNumberOfPaths(iterator);
        }
        iterator++;
    }

    // Save paths to limit repeated calls
    savedPaths[index] = paths;
    return paths;
}

int main(){

    // Read file into vector of ints
    std::string inputText;
    std::ifstream inputFile("input.txt");
    while (getline(inputFile, inputText)) {
        int newAdaptor = std::stoi(inputText);
        adaptors.push_back(newAdaptor);
        savedPaths.push_back(-1);
    }

    // Make sure 0 is in the list (used as recursive base case)
    adaptors.push_back(0);
    savedPaths.push_back(-1);

    // Reverse sort the vector
    std::sort(adaptors.rbegin(), adaptors.rend());

    // Count the differences
    long paths = getNumberOfPaths(0);
    printf("There are %ld paths\n", paths);

    inputFile.close();
    return 1;
}
