#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <regex>
#include <cstring>

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

    // Validation regexes for the fields
    std::map<std::string, std::string> regexes = {
        {"byr", "(19[2-8][0-9]|199[0-9]|200[0-2])"},                    // 1920 - 2002
        {"iyr", "(201[0-9]|2020)"},                                     // 2010 - 2020
        {"eyr", "(202[0-9]|2030)"},                                     // 2020 - 2030
        {"hgt", "((1[5-8][0-9]|19[0-3])cm)|((59|6[0-9]|7[0-6])in)"},    // 150 - 193cm | 59 - 76in
        {"ecl", "(amb|blu|brn|gry|grn|hzl|oth)"},
        {"hcl", "#[a-f0-9]{6}"},                                        // # + 6 hex digits
        {"pid", "[0-9]{9}"}                                             // 9 digit number
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

                // Get code:value pair
                std::string code = tokenText.substr(0,3);
                std::string value = tokenText.substr(4, strlen(tokenText.c_str()));
                if(code != "cid"){

                    // Validate the value using the regex
                    if(std::regex_match(value.c_str(), std::regex(regexes[code]))){
                        passport[code] = true;
                    }
                }
            }
        }

    }
    printf("There were %d valid passports\n", valids);
    inputFile.close();
    return 1;
}
