#ifndef _MATRIX_INCLUDE
#define _MATRIX_INCLUDE
#include <vector>

class Matrix {

    public:
        int size;
        int id;
        int** cells;
        bool flipped;
        int rotation;
        bool used;


        Matrix(int size);
        ~Matrix();

        void generateCombos();
        int** getMatrix();
        void print();
        bool matchRight(Matrix *other);
        bool matchBottom(Matrix *other);

    private:
        std::vector<int**> combos;

        int** newEmpty();
        int** newCopy();
        int** rotate(int rot, int** in);
        int** flip(int** in);
        void deleteMatrix(int** matrix);
};

#endif
