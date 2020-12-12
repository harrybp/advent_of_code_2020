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
    Dir dir;
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
    ship.dir = EAST;
    ship.x = 0;
    ship.y = 0;

    // Execute the instructions
    for(int i = 0; i < instructions.size(); i++){
        switch(instructions[i].cmd){
            case 'N':
                ship.y -= instructions[i].amount;
                break;
            case 'E':
                ship.x += instructions[i].amount;
                break;
            case 'S':
                ship.y += instructions[i].amount;
                break;
            case 'W':
                ship.x -= instructions[i].amount;
                break;
            case 'L':
                ship.dir = static_cast<Dir>((ship.dir + 4 - (instructions[i].amount / 90)) % 4);
                break;
            case 'R':
                ship.dir = static_cast<Dir>((ship.dir + (instructions[i].amount / 90)) % 4);
                break;
            case 'F':
                Instruction newInstruction = {dirToCmd(ship.dir), instructions[i].amount};
                instructions.insert(instructions.begin() + i + 1, newInstruction);
                break;
        }
    }
    printf("Ship is at (%d, %d), distance is %d\n", ship.x, ship.y, abs(ship.x) + abs(ship.y));
    inputFile.close();
    return 1;
}
