#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

// Seat status
enum Status {
    OCCUPIED,
    EMPTY
};

// Seat datastructure
struct Seat {
    Status status;
    int xPos;
    int yPos;
    std::vector<Seat*> neighbours;
};

// All the seat info
std::vector<Seat*> seats;
std::vector<std::vector<Seat*> > seatMap;

// Print the status of all the seats
void printSeats(){
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 10; col++){
            bool found = false;
            for(int s = 0; s < seats.size(); s++){
                if((seats[s]->xPos == col) && (seats[s]->yPos == row)){
                    printf("%s", (seats[s]->status == OCCUPIED)? "#" : "L");
                    found = true;
                    break;
                }
            }
            if(!found){
                printf(".");
            }
        }
        printf("\n");
    }
}

// Show the neighbours for a given seat
void printNeighbours(Seat* seat){
    for(int row = 0; row < 10; row++){
        for(int col = 0; col < 10; col++){
            bool found = false;
            if((seat->xPos == col) && (seat->yPos == row)){
                found = true;
                printf("o");
            }
            for(int s = 0; s < seat->neighbours.size(); s++){
                if((seat->neighbours[s]->xPos == col) && (seat->neighbours[s]->yPos == row)){
                    printf("#");
                    found = true;
                    break;
                }
            }
            if(!found){
                printf(".");
            }
        }
        printf("\n");
    }
}

// Count the number of occupied seats
int countSeats(){
    int total = 0;
    for(int i = 0; i < seats.size(); i++){
        if(seats[i]->status == OCCUPIED){
            total++;
        }
    }
    return total;
}

// Increase time by 1
bool step(){
    bool changed = false;
    std::vector<Status> newSeats;

    // Loop through seats
    for(int i = 0; i < seats.size(); i++){
        Status newSeat = seats[i]->status;

        // Check how many neighbours are occupied
        int numOccupied = 0;
        for(int j = 0; j < seats[i]->neighbours.size(); j++){
            if(seats[i]->neighbours[j]->status == OCCUPIED){
                numOccupied++;
            }
        }

        // If seat was empty and has no occupied seats next to it
        if((seats[i]->status == EMPTY) && (numOccupied == 0)){
            changed = true;
            newSeat = OCCUPIED;

        // If seat was occupied and has 5 or more occupied seats next to it
        } else if((seats[i]->status == OCCUPIED) && (numOccupied >= 5)){
            changed = true;
            newSeat = EMPTY;
        }
        newSeats.push_back(newSeat);
    }

    // Copy the new seat status into main array
    for(int i = 0; i < seats.size(); i++){
        seats[i]->status = newSeats[i];
    }

    return changed;
}

// Find the closest neighbour in this direction
void findInDir(Seat* seat, int xDir, int yDir){
    int x = seat->xPos + xDir;
    int y = seat->yPos + yDir;
    int width = 98;
    int height = 91;
    while((x >= 0) && (y >= 0) && (x < width) && (y < height)){
        if((seatMap[y][x] != NULL)){
            seat->neighbours.push_back(seatMap[y][x]);
            return;
        }
        x += xDir;
        y += yDir;
    }
}

// Find all the neighbours for this seat
void getNeighbours(Seat *seat){
    for(int x = -1; x <= 1; x++){
        for(int y =-1; y <= 1; y++){
            if((x != 0) || (y != 0)){
                findInDir(seat, x, y);
            }
        }
    }
}

int main(){

    // Read seats into array
    std::string inputText;
    std::ifstream inputFile("input.txt");

    // Read the input
    int row = 0;
    while (getline(inputFile, inputText)) {
        std::vector<Seat*> thisLine;
        for(int col = 0; col < inputText.size(); col++){
            if(inputText[col] == 'L'){
                Seat *newSeat = new Seat;
                newSeat->xPos = col;
                newSeat->yPos = row;
                newSeat->status = EMPTY;
                seats.push_back(newSeat);
                thisLine.push_back(newSeat);
            } else {
                thisLine.push_back(NULL);
            }
        }
        row++;
        seatMap.push_back(thisLine);
    }
    // Get the neighbours for each seat
    for(int i = 0; i < seats.size(); i++){
        getNeighbours(seats[i]);
    }

    // Increment time until stable
    bool changed = true;
    while(changed){
        changed = step();
    }

    printf("There are %d occupied seats\n", countSeats());
    inputFile.close();
    return 1;
}
