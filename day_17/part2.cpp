#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

// A point in 4D space
struct Cube {
    int x;
    int y;
    int z;
    int q;
};

std::vector<std::vector<std::vector<std::vector<int> > > > world;
int worldSize;

// Print a representation of the 4D vector
void drawWorld(int from, int to){
    for(int q = from; q < to; q++){
        for(int z = from; z < to; z++){
            printf("\n Q = %d, Z = %d %lu)\n",q , z, world[q][z].size());
            for(int y = 0; y < world[q][z].size(); y++){
                for(int x = 0; x < world[q][z][y].size(); x++){
                    if(world[q][z][y][x] == 1){
                        printf("#");
                    } else {
                        printf(".");
                    }
                }
                printf("\n");
            }
        }
    }
}

// Initialise a 4 dimensional vector
std::vector<std::vector<std::vector<std::vector<int> > > > getClearVector(int size){
    std::vector<std::vector<std::vector<std::vector<int> > > > newWorld;
    for(int q = 0; q < size; q++){
        std::vector<std::vector<std::vector<int> > > qLevel;
        for(int z = 0; z < size; z++){
            std::vector<std::vector<int> > zLevel;
            for(int y = 0; y < size; y++){
                std::vector<int> yLevel;
                for(int x = 0; x < size; x++){
                    yLevel.push_back(0);
                }
                zLevel.push_back(yLevel);
            }
            qLevel.push_back(zLevel);
        }
        newWorld.push_back(qLevel);
    }
    return newWorld;
}

// Apply the rules to increase time by one
void step(){
    std::vector<std::vector<std::vector<std::vector<int> > > > newWorld = getClearVector(worldSize);

    for(int q = 0; q < world.size(); q++){
        for(int z = 0; z < world[q].size(); z++){
            for(int y = 0; y < world[q][z].size(); y++){
                for(int x = 0; x < world[q][z][y].size(); x++){

                    // Need to check all surrounding points
                    int numSurroundings = 0;
                    for(int xOff = -1; xOff <= 1; xOff++){
                        for(int yOff = -1; yOff <= 1; yOff++){
                            for(int zOff = -1; zOff <= 1; zOff++){
                                for(int qOff = -1; qOff <= 1; qOff++){
                                    if(((qOff != 0) || (zOff != 0) || (yOff != 0) || (xOff != 0)) &&
                                        (q + qOff >= 0) && (q + qOff < worldSize) &&
                                        (z + zOff >= 0) && (z + zOff < worldSize) &&
                                        (y + yOff >= 0) && (y + yOff < worldSize) &&
                                        (x + xOff >= 0) && (x + xOff < worldSize)){

                                        // Checking surrounding point
                                        if(world[q + qOff][z + zOff][y + yOff][x + xOff] == 1){
                                            numSurroundings++;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // If cube is active, stay acive if 2 or 3 surroundings
                    if(world[q][z][y][x] == 1){
                       if((numSurroundings == 2) || (numSurroundings == 3)){
                           newWorld[q][z][y][x] = 1;
                       } else {
                           newWorld[q][z][y][x] = 0;
                       }

                    // If cube is inactive, activate if 3 surroundings
                    } else {
                        if(numSurroundings == 3){
                            newWorld[q][z][y][x] = 1;
                        } else {
                            newWorld[q][z][y][x] = 0;
                        }
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
    for(int q = 0; q < world.size(); q++){
        for(int z = 0; z < world[q].size(); z++){
            for(int y = 0; y < world[q][z].size(); y++){
                for(int x = 0; x < world[q][z][y].size(); x++){
                    total += world[q][z][y][x];
                }
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
                world[0 + iterations][0 + iterations][y + iterations][x + iterations] = 1;
            }
        }
        y++;
    }

    for(int i = 0; i < 6; i++){
        step();
    }
    printf("Total: %d\n", countActive());
    inputFile.close();
    return 1;
}
