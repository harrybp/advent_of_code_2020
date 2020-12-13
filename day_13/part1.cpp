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

    // Get leave time
    getline(inputFile, inputText);
    int time = stoi(inputText);

    // Get bus times
    getline(inputFile, inputText);
    std::stringstream ss(inputText);
    std::vector<int> busTimes;
    while(std::getline(ss, tokenText, ',')){
        if(tokenText != "x"){
            busTimes.push_back(stoi(tokenText));
        }
    }

    // Find the shortest wait
    int lowestWait = INT_MAX;
    int lowestId = 0;
    for(int i = 0; i < busTimes.size(); i++){
        int waitTime = busTimes[i] - (time % busTimes[i]);
        if(waitTime < lowestWait){
            lowestWait = waitTime;
            lowestId = busTimes[i];
        }
    }
    printf("Wait is %d for bus %d : %d\n", lowestWait, lowestId, lowestWait * lowestId);
    inputFile.close();
    return 1;
}
