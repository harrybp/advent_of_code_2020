#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

int main(){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile("input.txt");

    // Question info
    int lineWidth = 31;
    int xStep = 3;
    int yStep = 1;

    // Tracking variables
    int xPos = 0;
    int yPos = 0;
    int lineNumber = 0;
    int trees = 0;

    // Loop through lines in file
    while (getline(inputFile, inputText)) {
        if(lineNumber == yPos){

            // Check for a tree
            if(inputText.c_str()[xPos % lineWidth] == '#'){
                trees++;
            }

            // Move
            xPos += xStep;
            yPos += yStep;
        }
        lineNumber++;
    }

    // Done
    printf("We hit %d trees\n", trees);
    inputFile.close();
    return 1;
}
