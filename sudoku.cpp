#include <stdio.h>
#include <math.h>
#include <stdlib.h>

class Sudoku {

private:
    int** board;
    int size;
    int sq_size; // size of smaller square. sqrt of size

    bool valid(int row, int col, int num) {
        // check row
        for (int i = 0; i < size; i++) {
            if (board[row][i] == num) {
                return false;
            }
        }
        // check column
        for (int i = 0; i < size; i++) {
            if (board[i][col] == num) {
                return false;
            }
        }
        // check inner square
        int sq_row = (row / sq_size) * sq_size;
        int sq_col = (col / sq_size) * sq_size;
        for (int i = 0; i < sq_size; i++) {
            for (int j = 0; j < sq_size; j++) {
                if (board[i + sq_row][j + sq_col] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    // true if blank exists, false otherwise
    bool nextBlank(int* row, int* col) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (board[i][j] == 0) {
                    *row = i;
                    *col = j;
                    return true;
                }
            }
        }
        return false;
    }

public:
    Sudoku (int** board, int size) : board(board), size(size) {
        sq_size = (int) sqrt(size);
        if (sq_size - sqrt(size) != 0) {
            // cannot solve. size must be perfect square
        }
    }

    void printBoard() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                printf("%i ", board[i][j]);
            }
            printf("\n");
        }
    }

    bool solve() {
        int row, col, num;
        if(!nextBlank(&row, &col)) {
            return true;
        }
        for (num = 1; num <= size; num++) {
            if (valid(row, col, num)) {
                board[row][col] = num;
                if (solve()) {
                    return true;
                }
                board[row][col] = 0;
            }
        }
        return false;
    }

    void freeBoard() {
        for (int i = 0; i < size; i++) {
            free(board[i]);
        }
        free(board);
    }
};

int main(void) {
    int size = 9;
    int sudoku_board[9][9] = {
        {0,0,4,0,0,0,0,3,9},
        {5,1,0,0,0,3,0,0,6},
        {0,0,0,7,9,1,5,4,2},
        {0,7,8,6,0,9,4,5,0},
        {0,4,3,0,0,8,2,0,0},
        {0,5,2,0,7,0,0,0,8},
        {2,3,0,5,0,0,0,0,0},
        {0,9,0,0,0,7,0,2,1},
        {4,0,7,9,0,0,3,0,0}
    };

    int** board = (int**) malloc(sizeof(int*) * size);
    for (int i = 0; i < size; i++) {
        board[i] = (int*) malloc(sizeof(int*) * size);
        for (int j = 0; j < size; j++) {
            board[i][j] = sudoku_board[i][j];
        }
    }

    Sudoku* sudoku = new Sudoku(board, size);
    sudoku->solve();
    sudoku->printBoard();
    sudoku->freeBoard();
    return 0;
}