#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

int main(){
    // Input is short today, no need for file reading
    std::vector<int> input = {11,0,1,10,5,19};
    std::map<int,int> mostRecent;
    int nextNumber = 0;
    int targetNumber = 2020;

    // Add the starting numbers to the map
    for(int i = 0; i < targetNumber - 1; i++){

        // Starting numbers
        if(i < input.size()){
            mostRecent.insert(std::make_pair(input[i], i));
            nextNumber = 0;

        // Rest of sequence
        } else {

            // New number
            if(mostRecent.insert(std::make_pair(nextNumber, i)).second){
                nextNumber = 0;

            // Repeated number
            } else {
                int oldNextNumber = nextNumber;
                nextNumber = i - mostRecent[nextNumber];
                mostRecent[oldNextNumber] = i;
            }
        }
    }
    printf("The %dth number is %d\n", targetNumber, nextNumber);
    return 1;
}
