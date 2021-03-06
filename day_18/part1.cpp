#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// Solve a sum in the form X * Y or X + Y
std::string solve(std::string simpleSum){

    // Parse the string to find, X, Y and operator
    int firstSpace = simpleSum.find(" ");
    std::string firstNumber = simpleSum.substr(0, firstSpace);
    std::string secondPart = simpleSum.substr(firstSpace+1, simpleSum.size());
    int secondSpace = secondPart.find(" ");
    std::string op = secondPart.substr(0, secondSpace);
    std::string secondNumber = secondPart.substr(secondSpace + 1, secondPart.size());

    // Do the operation
    long long operandA = stoll(firstNumber);
    long long operandB = stoll(secondNumber);
    long long result = (op == "*")? operandA * operandB : operandA + operandB;
    //printf("> %s = %lld\n", simpleSum.c_str(), result);

    // Convert back to string and return
    return std::to_string(result);
}

// Recursively reduce the maths sum down to a single number
std::string reduce(std::string sum){
    int operatorsFound = 0;     // If only one operator found, its the base case
    char theOperator = 'x';     // Track operator for the base case
    bool foundBrackets = false; // If we see brackets, we must reduce them first
    int startBracketIndex = 0;  // Track start and end of outermost brackets
    int endBracketIndex = 0;
    int bracketDepth = 0;       // Track bracket depth to ensure only outer brackets
    int firstSumEnd = 0;        // Identify end of first reducible sum for other case

    // Evaluate sum to choose which case to apply
    for(int i = 0; i < sum.size(); i++){
        char c = sum[i];

        // Count up how many operators remain
        if((c == '+') || (c == '*')){
            operatorsFound++;
            theOperator = c;
            if(operatorsFound == 2){ // Identify end of first reducible sum
                firstSumEnd = i - 1;
            }
        }

        // Find bracket beginning
        if(c == '('){
            bracketDepth++;
            if(!foundBrackets){
                foundBrackets = true;
                startBracketIndex = i;
            }
        }

        // Find bracket end
        if(c == ')'){
            bracketDepth--;
            if(bracketDepth == 0){
                endBracketIndex = i;
                break;
            }
        }
    }

    // Brackets case, must be done first cause we break on a close bracket
    if(foundBrackets){
        std::string bracketString = sum.substr(startBracketIndex + 1, endBracketIndex - startBracketIndex - 1);
        std::string beforeString = sum.substr(0, startBracketIndex);
        std::string endString = sum.substr(endBracketIndex+1, sum.size());
        return reduce(beforeString + reduce(bracketString) + endString);
    }

    // Base case
    if(operatorsFound == 1){
        return solve(sum);
    }

    // Other case (reduce first sum)
    std::string beforeString = sum.substr(0, firstSumEnd);
    std::string afterString = sum.substr(firstSumEnd, sum.size());
    return(reduce(solve(beforeString) + afterString));
}


int main(){

    // Read file, going to leave the sums as strings
    std::string inputText;
    std::ifstream inputFile("input.txt");
    long long total = 0;
    while (getline(inputFile, inputText)) {
        long long result = stoll(reduce(inputText));
        total += result;
        //printf("%s = %lld\n", inputText.c_str(), result);
    }
    printf("Final answer: %lld\n", total);
    inputFile.close();
    return 1;
}

