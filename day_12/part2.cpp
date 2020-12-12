#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

enum Dir {
    NORTH = 0,
    EAST  = 1,
    SOUTH = 2,
    WEST  = 3
};

struct Ship {
    int x;
    int y;
};

struct Waypoint {
    int x;
    int y;
};

struct Instruction {
    char cmd;
    int amount;
};

// Convert ships direction into a command
char dirToCmd(Dir dir){
    return (dir == NORTH)? 'N' :
            (dir == EAST)? 'E' :
           (dir == SOUTH)? 'S' : 'W';
}

// Rotate waypoint around the ship (origin)
Waypoint rotateWaypoint(Waypoint waypoint, int amount){
    for(int i = 0; i < amount; i++){
        int oldX = waypoint.x;
        waypoint.x = -waypoint.y;
        waypoint.y = oldX;

    }
    return waypoint;
}

// Move ship towards the waypoint
Ship moveForwards(Waypoint waypoint, Ship ship, int amount){
    for(int i = 0; i < amount; i++){
        ship.x += waypoint.x;
        ship.y += waypoint.y;
    }
    return ship;
}


int main(){

    // Read file into vector of instructions
    std::string inputText;
    std::ifstream inputFile("input.txt");
    std::vector<Instruction> instructions;
    while (getline(inputFile, inputText)) {
        Instruction newInstruction;
        newInstruction.cmd = inputText[0];
        newInstruction.amount = stoi(inputText.substr(1, inputText.size()));
        instructions.push_back(newInstruction);
    }

    // Initialise the ship
    Ship ship;
    ship.x = 0;
    ship.y = 0;

    Waypoint waypoint;
    waypoint.x = 10;
    waypoint.y = -1;

    // Execute the instructions
    for(int i = 0; i < instructions.size(); i++){
        switch(instructions[i].cmd){
            case 'N':
                waypoint.y -= instructions[i].amount;
                break;
            case 'E':
                waypoint.x += instructions[i].amount;
                break;
            case 'S':
                waypoint.y += instructions[i].amount;
                break;
            case 'W':
                waypoint.x -= instructions[i].amount;
                break;
            case 'L':
                waypoint = rotateWaypoint(waypoint, 4 - (instructions[i].amount / 90));
                break;
            case 'R':
                waypoint = rotateWaypoint(waypoint, instructions[i].amount / 90);
                break;
            case 'F':
                ship = moveForwards(waypoint, ship, instructions[i].amount);
                break;
        }
    }
    printf("Ship is at (%d, %d), distance is %d\n", ship.x, ship.y, abs(ship.x) + abs(ship.y));
    inputFile.close();
    return 1;
}
