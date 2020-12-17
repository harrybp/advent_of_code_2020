#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

// A point in 3D space
struct Cube {
    int x;
    int y;
    int z;
};

std::vector<std::vector<std::vector<int> > > world;
int worldSize;

// Print a representation of the 4D vector
void drawWorld(int from, int to){
    for(int z = from; z < to; z++){
        printf("\nZ = %d\n", z);
        for(int y = 0; y < world[z].size(); y++){
            for(int x = 0; x < world[z][y].size(); x++){
                if(world[z][y][x] == 1){
                    printf("#");
                } else {
                    printf(".");
                }
            }
            printf("\n");
        }
    }
}

// Initialise a 3 dimensional vector
std::vector<std::vector<std::vector<int> > > getClearVector(int size){
    std::vector<std::vector<std::vector<int> > > newWorld;
    for(int z = 0; z < size; z++){
        std::vector<std::vector<int> > zLevel;
        for(int y = 0; y < size; y++){
            std::vector<int> yLevel;
            for(int x = 0; x < size; x++){
                yLevel.push_back(0);
            }
            zLevel.push_back(yLevel);
        }
        newWorld.push_back(zLevel);
    }
    return newWorld;
}

// Apply the rules to increase time by one
void step(){
    // Create a new copy of the world
    std::vector<std::vector<std::vector<int> > > newWorld = getClearVector(worldSize);

    // Iterate over each dimension
    for(int z = 0; z < world.size(); z++){
        for(int y = 0; y < world[z].size(); y++){
            for(int x = 0; x < world[z][y].size(); x++){

                // Need to check all surrounding points
                int numSurroundings = 0;
                for(int xOff = -1; xOff <= 1; xOff++){
                    for(int yOff = -1; yOff <= 1; yOff++){
                        for(int zOff = -1; zOff <= 1; zOff++){
                            if(((zOff != 0) || (yOff != 0) || (xOff != 0)) &&
                                (z + zOff >= 0) && (z + zOff < worldSize) &&
                                (y + yOff >= 0) && (y + yOff < worldSize) &&
                                (x + xOff >= 0) && (x + xOff < worldSize)){

                                // Checking surrounding point
                                if(world[z + zOff][y + yOff][x + xOff] == 1){
                                    numSurroundings++;
                                }
                            }
                        }
                    }
                }

                // If cube is active, stay acive if 2 or 3 surroundings
                if(world[z][y][x] == 1){
                   if((numSurroundings == 2) || (numSurroundings == 3)){
                       newWorld[z][y][x] = 1;
                   } else {
                       newWorld[z][y][x] = 0;
                   }

                // If cube is inactive, activate if 3 surroundings
                } else {
                    if(numSurroundings == 3){
                        newWorld[z][y][x] = 1;
                    } else {
                        newWorld[z][y][x] = 0;
                    }
                }
            }
        }
    }
    world = newWorld;
}

// Count how many cubes in the world are active
int countActive(){
    int total = 0;
    for(int z = 0; z < world.size(); z++){
        std::vector<std::vector<int> > zLevel = world[z];
        for(int y = 0; y < zLevel.size(); y++){
            std::vector<int> yLevel = zLevel[y];
            for(int x = 0; x < yLevel.size(); x++){
                total += world[z][y][x];
            }
        }
    }
    return total;
}


int main(){
    int iterations = 6;

    // Read seats into array
    std::string inputText;
    std::ifstream inputFile("input.txt");
    int y = 0;
    while (getline(inputFile, inputText)) {

        // Setup world array
        if(y == 0){
            worldSize = (iterations * 2) + inputText.size();
            world = getClearVector(worldSize);
        }

        // Read in line
        for(int x = 0; x < inputText.size(); x++){
            if(inputText[x] == '#'){
                world[0 + iterations][y + iterations][x + iterations] = 1;
            }
        }
        y++;
    }

    for(int i = 0; i < iterations; i++){
        step();
    }
    printf("Total: %d\n", countActive());
    inputFile.close();
    return 1;
}
