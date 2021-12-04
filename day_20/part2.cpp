#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

#include "Matrix.h"

// ----------------------------------------------------------------------------
// Size is 3 for test example, 12 for real example
const int MAP_ROW_SIZE = 12;

// ----------------------------------------------------------------------------
// Get Tiles
std::vector<Matrix*> getTiles(std::string filename){
    // Open file
    std::vector<std::string> messages;
    std::string inputText;
    std::ifstream inputFile(filename);

    std::vector<Matrix*> tiles;

    Matrix *newTile;// = Matrix(10);;
    int index = 0;
    bool recording = false;

    // Read line by line
    while (getline(inputFile, inputText)) {

        // Search for tile header
        std::regex rgx(".*Tile\\s(\\w+):\\.*");
        std::smatch match;
        if (std::regex_search(inputText, match, rgx)){

            // Init new tile
            newTile = new Matrix(10);
            newTile->id = std::stoi(match[1].str());
            recording = true;
            index = -1;
        }

        // Read in a line of the map
        if(recording && (index < 10) && (index > -1)){
            for(int i = 0; i < 10; i++){
                if(inputText[i] == '#'){
                    newTile->cells[index][i] = 1;
                } else {
                    newTile->cells[index][i] = 0;
                }
            }
        }
        index++;

        // Save finished map
        if(recording && (index == 10)){
            tiles.push_back(newTile);
        }

    }
    inputFile.close();

    return tiles;
}

// ----------------------------------------------------------------------------
// Build Map by trimming and combining the tiles
Matrix* buildMap(Matrix *tileMap, std::vector<Matrix*> tiles){
    Matrix *map = new Matrix(tileMap->size * 8);

    for(int i = 0; i < tileMap->size; i++){
        for(int j = 0; j < tileMap->size; j++){

            for(int x = 0; x < 8; x++){
                for(int y = 0; y < 8; y++){
                    map->cells[(i*8)+x][(j*8)+y] = tiles[tileMap->cells[i][j]]->getMatrix()[x+1][y+1];
                }
            }
        }
    }

    return map;
}

// ----------------------------------------------------------------------------
// Count number of active cells in the Map
int countMap(Matrix *map){
    int count = 0;
    for(int i = 0; i < map->size; i++){
        for(int j = 0; j < map->size; j++){
            if (map->cells[i][j] == 1){
                count++;
            }
        }
    }
    return count;
}

// ----------------------------------------------------------------------------
// Find Monsters
int findMonsters(Matrix *map){
    int monster[3][20] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0, // 1
        1,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1, // 8
        0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0  // 6 //15
    };

    int monsters = 0;
    for(int i = 0; i < map->size - 3; i++){
        for(int j = 0; j < map->size - 20; j++){
            for(int x = 0; x < 3; x++){
                for(int y = 0; y < 20; y++){
                    if(monster[x][y] == 1 && map->getMatrix()[i+x][j+y] == 0){
                        goto next;
                    }
                }
            }
            monsters++;
next:
        continue;
        }
    }
    return monsters;
}

// ----------------------------------------------------------------------------
// Attempt to build the map from a given corner
Matrix* attemptFromCorner(std::vector<Matrix*> tiles, int cornerIndex){
    Matrix *tileMap = new Matrix(MAP_ROW_SIZE);
    Matrix* currentTile = tiles[cornerIndex];
    Matrix* aboveTile = tiles[cornerIndex];
    currentTile->used = true;
    tileMap->cells[0][0] = cornerIndex;

    // Loop over size of grid
    for(int i = 0; i < tileMap->size; i++){
        for(int j = 0; j < tileMap->size; j++){
            if(i == 0 && j == 0)
                continue;

            bool done = false;
            for(int t = 0; t < tiles.size(); t++){
                if(tiles[t]->used)
                    continue;
                if(tiles[t]->id == currentTile->id)
                    continue;

                for(int c = 0; c < 8; c++){
                    tiles[t]->rotation = c % 4;
                    tiles[t]->flipped = c > 3;
                    if(j == 0){

                        if(aboveTile->matchBottom(tiles[t])){
                            tiles[t]->used = true;
                            tileMap->cells[i][j] = t;
                            currentTile = tiles[t];
                            aboveTile = tiles[t];
                            done = true;
                            break;
                        }
                    } else {
                        if(currentTile->matchRight(tiles[t])){
                            tiles[t]->used = true;
                            tileMap->cells[i][j] = t;
                            currentTile = tiles[t];
                            done = true;
                            break;
                        }
                    }
                }
                if(done)
                    break;
            }
            if(!done){
                // Reset all tiles and return
                for(Matrix* t : tiles){
                    t->used = false;
                }
                return tileMap;
            }
        }
    }
    tileMap->used = true;
    return tileMap;
}

// ----------------------------------------------------------------------------
// Get the 4 corner tiles
std::vector<int> getCorners(std::vector<Matrix*> tiles){
    std::vector<int> corners;
    for(int i = 0; i < tiles.size(); i++){
        int connections = 0;


        // For each other tile
        for(int j = 0; j < tiles.size(); j++){
            if(i == j)
                continue;


            // For each pair of combos
            for(int cA = 0; cA < 4; cA++){
                for(int cB = 0; cB < 8; cB++){
                    tiles[i]->rotation = cA % 4;
                    tiles[i]->flipped = cA > 3;
                    tiles[j]->rotation = cB % 4;
                    tiles[j]->flipped = cB > 3;

                    // Check if they match up right to left
                    if(tiles[i]->matchRight(tiles[j])){
                        connections++;
                    }
                }
            }
        }
        if(connections == 2){
            corners.push_back(i);
        }
    }
    return corners;
}

// ----------------------------------------------------------------------------
int main(){
    std::vector<Matrix*> tiles = getTiles("input.txt");
    for(Matrix* matrix : tiles){
        matrix->generateCombos();
    }

    // Get the 4 corners
    std::vector<int> corners = getCorners(tiles);

    // Arrange tiles into a grid starting from one of the corners
    Matrix *tileMap;
    for(int i : corners){
        for(int c = 0; c < 8; c++){
            tiles[i]->rotation = c % 4;
            tiles[i]->flipped = c > 3;
            tileMap = attemptFromCorner(tiles, i);
            if(tileMap->used){
                goto doneMap;
            }
        }
    }
doneMap:

    // Trim and combine the tiles to create a whole map
    Matrix *map = buildMap(tileMap, tiles);
    map->generateCombos();

    // Check each map combination for monsters
    int monsters = 0;
    for(int i = 0; i < 8; i++){
        map->rotation = i % 4;
        map->flipped = i > 3;
        monsters = findMonsters(map);
        if(monsters > 0){
            break;
        }
    }

    // Count the result
    int mapSize = countMap(map);
    printf("Size: %d, monsters %d, answer: %d\n", mapSize, monsters, mapSize - (monsters*15));

}
