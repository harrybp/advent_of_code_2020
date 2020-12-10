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
    bool newGroup = true;

    // Loop through numbers in file
    while (getline(inputFile, inputText)) {
        std::set<char> newAnswers;

        // Add characters to the new set only if they also appeared before
        // or if this is the first person in the group
        for(int i = 0; i < inputText.size(); i++){
            char newChar = inputText.c_str()[i];
            if((answers.count(newChar) > 0) || newGroup){
                newAnswers.insert(newChar);
            }
        }

        // If we reach the end of a group, add on the total
        if(inputText.size() < 1){
            total += answers.size();
            answers.clear();
            newGroup = true;

        // Otherwise, replace the set with the new set
        } else {
            newGroup = false;
            answers = newAnswers;
        }
    }
    printf("The total is %d\n", total);
    inputFile.close();
    return 1;
}

// 3406 too high
