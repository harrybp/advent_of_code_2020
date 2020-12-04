#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

int main(){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile("input.txt");

    // Store passport info in a map
    std::map<std::string, bool>::iterator it;
    std::map<std::string, bool> passport = {
        {"byr", false},
        {"iyr", false},
        {"eyr", false},
        {"hgt", false},
        {"hcl", false},
        {"ecl", false},
        {"pid", false}
    };

    int valids = 0;
    while (getline(inputFile, inputText)) {

        // Newline indicates end of a passport record
        if(strlen(inputText.c_str()) < 2){
            bool valid = true;

            // Reset and check the passport map for any missing fields
            for(it = passport.begin(); it != passport.end(); it++ ){
                if(it->second == true){
                    it->second = false;
                } else {
                    valid = false;
                }
            }

            // If no missing fields, increment valid counter
            if(valid){
                valids++;
            }

        // Parse line containing passport record
        } else {
            std::stringstream ss(inputText);

            // Split on spaces
            while(std::getline(ss, tokenText, ' ')){
                if(tokenText.substr(0,3) != "cid"){
                    passport[tokenText.substr(0,3)] = true;
                }
            }
        }

    }
    printf("There were %d valid passports\n", valids);
    inputFile.close();
    return 1;
}
