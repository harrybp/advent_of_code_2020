#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main(){
    // Input is short today, no need for file reading
    std::vector<int> input = {11,0,1,10,5,19};
    int nextNumber = 0;
    int targetNumber = 30000000;

    // Allocate a big heap array
    int *mostRecent = (int*)malloc(targetNumber * sizeof(int));
    memset(mostRecent, 0, targetNumber*sizeof(*mostRecent));

    // Add the starting numbers to the map
    for(int i = 0; i < targetNumber - 1; i++){

        // Starting numbers
        if(i < input.size()){
            mostRecent[input[i]] = i+1;
            nextNumber = 0;

        // Rest of sequence
        } else {

            if(mostRecent[nextNumber] == 0){
                mostRecent[nextNumber] = i+1;
                nextNumber = 0;

            } else {
                int oldNextNumber = nextNumber;
                nextNumber = i+1 - mostRecent[nextNumber];
                mostRecent[oldNextNumber] = i+1;
            }
        }
    }
    printf("The %dth number is %d\n", targetNumber, nextNumber);
    return 1;
}
