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
        if((password.c_str()[startNumber - 1] == character) ^ (password.c_str()[endNumber - 1] == character)){
            valids++;
        }
    }
    printf("%d are valid\n", valids);
    inputFile.close();
    return 1;
}
