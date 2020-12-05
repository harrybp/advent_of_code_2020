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
    std::vector<int> idLog;

    // Loop through boarding passes
    while (getline(inputFile, inputText)) {
        int id = getSeatID(inputText);
        idLog.push_back(id);
    }

    // Sort all the IDs
    std::sort(idLog.begin(), idLog.end());

    // Loop through the IDs until we find the missing one
    int prevId = idLog[0] - 1;
    for(int id : idLog){
        if(id != (prevId + 1)){
            printf("Missing ID is %d\n", prevId + 1);
            break;
        } else {
            prevId = id;
        }
    }
    inputFile.close();
    return 1;
}
