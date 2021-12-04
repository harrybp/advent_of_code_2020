#include "Matrix.h"

Matrix::Matrix(int newSize) {
    size = newSize;
    rotation = 0;
    flipped = false;
    used = false;
    cells = newEmpty();
}

Matrix::~Matrix(){
    deleteMatrix(cells);
    for(int** mat : combos){
        deleteMatrix(mat);
    }
}

// ----------------------------------------------------------------------------
// Free memory
void Matrix::deleteMatrix(int** matrix){
    for(int i = 0; i < size; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
}

// ----------------------------------------------------------------------------
// New Empty matrix
int** Matrix::newEmpty() {
    int** empty = new int*[size];
    for(int i = 0; i < size; i++){
        empty[i] = new int[size];
    }
    return empty;
}

// ----------------------------------------------------------------------------
// New copy of matrix
int** Matrix::newCopy(){
    int** newCells = newEmpty();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            newCells[i][j] = cells[i][j];
        }
    }
    return newCells;
}

// ----------------------------------------------------------------------------
// Flip a matrix
int** Matrix::flip(int** in) {
    int** newMatrix = newEmpty();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            newMatrix[i][j] = in[i][(size)-1-j];
        }
    }
    deleteMatrix(in);
    return newMatrix;
}

// ----------------------------------------------------------------------------
// Rotate a matrix
int** Matrix::rotate(int rot, int** in) {
    for(int a = 0; a < rot; a++){
        for (int i = 0; i < size / 2; i++) {
            for (int j = i; j < size - i - 1; j++) {

                // Swap elements of each cycle
                // in clockwise direction
                int temp = in[i][j];
                in[i][j] = in[size - 1 - j][i];
                in[size - 1 - j][i] = in[size - 1 - i][size - 1 - j];
                in[size - 1 - i][size - 1 - j] = in[j][size - 1 - i];
                in[j][size - 1 - i] = temp;
            }
        }
    }
    return in;
}

// ----------------------------------------------------------------------------
// Generate all flip/rotate matrix combos
void Matrix::generateCombos() {
    //combos.push_back(cells);
    for(int i = 0; i < 4; i++){
        int** newCells = newCopy();
        combos.push_back(rotate(i, newCells));
    }
    for(int i = 0; i < 4; i++){
        int** newCells = newCopy();
        combos.push_back(flip(rotate(i, newCells)));
    }

}

// ----------------------------------------------------------------------------
// Get matrix
int** Matrix::getMatrix() {
    int index = 0;
    index += rotation;
    if(flipped)
        index += 4;
    return combos[index];
}

// ----------------------------------------------------------------------------
// Print matrix
void Matrix::print() {
    if(id != 0){
        printf("ID: %d\n", id);
    }
    int** matrix = getMatrix();
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(matrix[i][j] == 1){
                printf("# ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}

// ----------------------------------------------------------------------------
// See if another matrix lines up with our right edge
bool Matrix::matchRight(Matrix* other){
    int** matrixA = getMatrix();
    int** matrixB = other->getMatrix();
    for(int i = 0; i < size; i++){
        if(matrixA[i][9] != matrixB[i][0]){
            return false;
        }
    }
    return true;
}

// ----------------------------------------------------------------------------
// See if another matrix lines up with our bottom edge
bool Matrix::matchBottom(Matrix* other){
    int** matrixA = getMatrix();
    int** matrixB = other->getMatrix();
    for(int i = 0; i < size; i++){
        if(matrixA[9][i] != matrixB[0][i]){
            return false;
        }
    }
    return true;
}
