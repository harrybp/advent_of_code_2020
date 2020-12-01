#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main(){
    // Input file
    std::string inputText;
    std::ifstream inputFile("input.txt");

    // Store numbers seen so far
    std::vector<int> numbers;

    // Loop through numbers in file
    while (getline(inputFile, inputText)) {
        int newNumber = std::stoi(inputText);

        // Loop through numbers seen so far
        for(int number1 : numbers){
            if((newNumber + number1) < 2020){

                // If potential first pair identified, loop through numbers again
                for(int number2 : numbers){

                    // Check if they add up to 2020
                    if((number2 != number1) && ((newNumber + number1 + number2) == 2020)){
                        printf("Result: %d\n", newNumber * number1 * number2);
                        inputFile.close();
                        return 1;

                    }
                }
            }
        }

        // Add number to numbers seen so far
        numbers.push_back(newNumber);
    }
    inputFile.close();
    return 1;
}
