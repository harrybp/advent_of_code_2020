#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>


int getSeatID(std::string pass){

    // Read the row and column strings and convert to binary
    std::string row = pass.substr(0,7);
    std::replace(row.begin(), row.end(), 'B', '1');
    std::replace(row.begin(), row.end(), 'F', '0');

    std::string col = pass.substr(7,10);
    std::replace(col.begin(), col.end(), 'R', '1');
    std::replace(col.begin(), col.end(), 'L', '0');

    int row_number = stoi(row, 0, 2);
    int col_number = stoi(col, 0, 2);

    int id = (row_number * 8) + col_number;
    return id;
}

int main(){
    // Input file
    std::string inputText;
    std::string tokenText;
    std::ifstream inputFile("input.txt");
    int highestID = 0;

    // Loop through boarding passes
    while (getline(inputFile, inputText)) {

        // Calculate ID and check if its highest
        int id = getSeatID(inputText);
        if(id > highestID){
            highestID = id;
        }
    }
    printf("The highest ID was %d\n", highestID);
    inputFile.close();
    return 1;
}
