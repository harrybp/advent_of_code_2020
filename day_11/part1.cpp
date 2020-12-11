#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

// Types of seats
enum Seat {
    EMPTY = 0,
    OCCUPIED = 1,
    FLOOR = 2
};

// Number of people each seat can accompdate
int v[3] = {0,1,0};

// The seats array
Seat seats[93][100];
int height = 91;
int width = 98;

// Print the seating arrangement for debug purposes
void printSeats(){
    for(int row = 0; row < height+2; row++){
        for(int col = 0; col < width+2; col++){
            char repr = (seats[row][col] == EMPTY)? 'L' :
                     (seats[row][col] == OCCUPIED)? '#' : '.';
           printf("%c", repr);
        }
       printf("\n");
    }
}

// Count the number of occupied seats
int countSeats(){
    int count = 0;
    for(int row = 1; row < height + 1; row++){
        for(int col = 1; col < width + 1; col++){
            count += v[seats[row][col]];
        }
    }
    return count;
}

// Increase time by 1, return whether anything changed
bool step(){
    bool change = false;
    Seat newSeats[height + 2][width + 2];
    for(int row = 1; row < height+1; row++){
        for(int col = 1; col < width+1; col++){

            // Count the number of people in the surrounding seats
            int sum = v[seats[row-1][col-1]] + v[seats[row-1][col]] + v[seats[row-1][col+1]] +
                      v[seats[row  ][col-1]]                        + v[seats[row  ][col+1]] +
                      v[seats[row+1][col-1]] + v[seats[row+1][col]] + v[seats[row+1][col+1]];
            Seat mySeat = seats[row][col];

            // If seat is empty and nobody else is next to us
            if((mySeat == EMPTY) && (sum == 0)){
                newSeats[row][col] = OCCUPIED;
                change = true;

            // If seat is occupied and 4 or more people are next to us
            }else if((mySeat == OCCUPIED) && (sum >= 4)){
                newSeats[row][col] = EMPTY;
                change = true;

            // Otherwise no change
            }else{
                newSeats[row][col] = mySeat;
            }
        }
    }

    // Copy new seating arrangement into main array
    for(int row = 1; row < height+1; row++){
        for(int col = 1; col < width+1; col++){
            seats[row][col] = newSeats[row][col];
        }
    }
    return change;

}


int main(){

    // Read seats into array
    std::string inputText;
    std::ifstream inputFile("input.txt");

    // Create a buffer of empty seats all around to avoid bounds checking later
    for(int col = 0; col < width + 2; col++){
        seats[0][col] = FLOOR;
    }
    int row = 1;
    while ((row < height + 1) && (getline(inputFile, inputText))) {
        seats[row][0] = FLOOR;
        for(int col = 1; col < width+1; col++){
            seats[row][col] = (inputText[col-1] == 'L')? EMPTY : FLOOR;
        }
        seats[row][width+1] = FLOOR;
        row++;
    }
    for(int col = 0; col < width + 2; col++){
        seats[row][col] = FLOOR;
    }

    // Iterate until it stablises
    bool itChanged = true;
    while(itChanged){
        itChanged = step();
    }
    printf("There are %d occupied seats\n", countSeats());

    inputFile.close();
    return 1;
}
