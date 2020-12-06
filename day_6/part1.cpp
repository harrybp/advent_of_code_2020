#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <set>

int main(){
    // Input file
    std::string inputText;
    std::ifstream inputFile("input.txt");
    std::set<char> answers;
    int total = 0;

    // Loop through numbers in file
    while (getline(inputFile, inputText)) {

        // Add characters to a set
        for(int i = 0; i < inputText.size(); i++){
            answers.insert(inputText.c_str()[i]);
        }

        // If we reach the end of a group
        if(inputText.size() < 1){
            total += answers.size();
            answers.clear();
        }

    }
    printf("The total is %d\n", total);
    inputFile.close();
    return 1;
}
