#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>

struct Tile {
    int id;
    int map[10][10];
    bool flipped;
    int rotation; // 1 = 90 clock, 3 = 270 clock
};

// ----------------------------------------------------------------------------
// Print Tile
void printTile(Tile tile){
    printf("-- %d --\n", tile.id);
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            if(tile.map[i][j] == 1){
                printf("# ");
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// ----------------------------------------------------------------------------
// Flip Tile
Tile flip(Tile tile){
    Tile newTile;
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            newTile.map[i][j] = tile.map[i][9-j];
        }
    }
    newTile.flipped = !tile.flipped;
    newTile.rotation = tile.rotation;
    newTile.id = tile.id;
    return newTile;
}

// ----------------------------------------------------------------------------
// Rotate an array 90degrees clockwise
void rotate90Clockwise(int a[10][10]){
    // Traverse each cycle
    for (int i = 0; i < 10 / 2; i++) {
        for (int j = i; j < 10 - i - 1; j++) {

            // Swap elements of each cycle
            // in clockwise direction
            int temp = a[i][j];
            a[i][j] = a[10 - 1 - j][i];
            a[10 - 1 - j][i] = a[10 - 1 - i][10 - 1 - j];
            a[10 - 1 - i][10 - 1 - j] = a[j][10 - 1 - i];
            a[j][10 - 1 - i] = temp;
        }
    }
}

// ----------------------------------------------------------------------------
// Rotate Tile
Tile rotate(Tile tile, int amount){
    Tile newTile;
    std::copy(&tile.map[0][0], &tile.map[0][0]+10*10,&newTile.map[0][0]);
    for(int a = 0; a < amount; a++){
        rotate90Clockwise(newTile.map);
    }
    newTile.rotation = (tile.rotation + amount) % 4;
    newTile.flipped = tile.flipped;
    newTile.id = tile.id;
    return newTile;
}

// ----------------------------------------------------------------------------
// Match tile, either on right or bottom
bool matchTileRight(Tile tileA, Tile tileB){
    for(int i = 0; i < 10; i++){
        if(tileA.map[i][9] != tileB.map[i][0]){
            return false;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------
bool matchTileBottom(Tile tileA, Tile tileB){
    for(int i = 0; i < 10; i++){
        if(tileA.map[9][i] != tileB.map[0][i]){
            return false;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------
// Generate all combos of a tile
std::vector<Tile> getCombos(Tile tile, bool basic){

    std::vector<Tile> combos;
    combos.push_back(tile);
    combos.push_back(rotate(tile,1));
    combos.push_back(rotate(tile,2));
    combos.push_back(rotate(tile,3));
    if(!basic){
        combos.push_back(flip(tile));
        combos.push_back(flip(rotate(tile, 1)));
        combos.push_back(flip(rotate(tile, 2)));
        combos.push_back(flip(rotate(tile, 3)));
    }
    return combos;
}

// ----------------------------------------------------------------------------
// Get Tiles
std::vector<Tile> getTiles(std::string filename){
    // Open file
    std::vector<std::string> messages;
    std::string inputText;
    std::ifstream inputFile(filename);
    std::vector<Tile> tiles;

    Tile newTile;
    int index = 0;
    bool recording = false;

    // Read line by line
    while (getline(inputFile, inputText)) {

        // Search for tile header
        std::regex rgx(".*Tile\\s(\\w+):\\.*");
        std::smatch match;
        if (std::regex_search(inputText, match, rgx)){

            // Init new tile
            newTile.id = std::stoi(match[1].str());
            recording = true;
            index = -1;
        }

        // Read in a line of the map
        if(recording && (index < 10) && (index > -1)){
            for(int i = 0; i < 10; i++){
                if(inputText[i] == '#'){
                    newTile.map[index][i] = 1;
                } else {
                    newTile.map[index][i] = 0;
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

int main(){
    std::vector<Tile> tiles = getTiles("input.txt");

    long long cornerTotal = 1;

    // For each tile
    for(int i = 0; i < tiles.size(); i++){
        int connections = 0;

        // Get the 4 possible rotations
        std::vector<Tile> combosA = getCombos(tiles[i], true);

        // For each other tile
        for(int j = 0; j < tiles.size(); j++){
            if(i == j)
                continue;

            // Get all possible flip/rotate combinations
            std::vector<Tile> combosB = getCombos(tiles[j], false);

            // For each pair of combos
            for(int cA = 0; cA < combosA.size(); cA++){
                for(int cB = 0; cB < combosB.size(); cB++){

                    // Check if they match up right to left
                    if(matchTileRight(combosA[cA], combosB[cB])){
                        connections++;
                    }
                }
            }
        }

        // Any tile with only two connections is a corner
        if(connections == 2){
            cornerTotal *= tiles[i].id;
        }

    }

    printf("%lld\n", cornerTotal);
    return 1;
}
