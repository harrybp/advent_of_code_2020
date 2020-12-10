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
    int xSteps[5] = {1, 3, 5, 7, 1};
    int ySteps[5] = {1, 1, 1, 1, 2};

    int total = 1;
    for(int i = 0; i < 5; i++){
        int xStep = xSteps[i];
        int yStep = ySteps[i];

        // Back to start of file
        inputFile.clear();
        inputFile.seekg(0);

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
        total *= trees;
    }

    // Done
    printf("Multiplied result is %d\n", total);
    inputFile.close();
    return 1;
}
