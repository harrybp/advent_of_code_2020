#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

int main(){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile("input.txt");
    int valids = 0;

    // Loop through numbers in file
    while (getline(inputFile, inputText)) {
        std::stringstream ss(inputText);

        // Get components one by one
        std::getline(ss, tokenText, '-');       // Start number
        int startNumber = std::stoi(tokenText);
        std::getline(ss, tokenText, ' ');       // End number
        int endNumber = std::stoi(tokenText);
        std::getline(ss, tokenText, ':');       // Character
        char character = tokenText.c_str()[0];
        std::getline(ss, tokenText, ' ');
        std::getline(ss, tokenText);            // Password
        std::string password = tokenText;

        // Count occurences and check if valid
        size_t occurences = std::count(password.begin(), password.end(), character);
        if((occurences <= endNumber) && (occurences >= startNumber)){
            valids++;
        }
    }
    printf("%d are valid\n", valids);
    inputFile.close();
    return 1;
}
