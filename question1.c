//
// Created by Roee on 17/12/2025.
//
#include <stdio.h>
#include <stdlib.h>
#define M 1000

int lenPacmanPath(char mat[][M], int n, int m); // Replace this line with your function.
void update_index_via_order(int* row, int* col, int n, int m, char current_order, char last_order);


// Do not change these functions
void fillMatrix(char mat[][M], int n, int m) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf(" %c", &mat[i][j]);
        }
    }
}

// Do not change the main function
int main() {
    int n = 0, m = 0;
    int student_output = -2;
    // First enter the size of the matrix
    printf("enter matrix: \n");
    scanf(" %d %d", &n, &m);
    // allocating the matrix - will be explained later in the course
    char (*mat)[M] = malloc(n * M * sizeof(char));
    if (mat) {
        fillMatrix(mat, n, m);
        student_output = lenPacmanPath(mat, n, m);
    }
    printf("count: %d", student_output);
    // Freeing the matrix - will be explained later in the course
    free(mat);
    return 0;
}

/**
 * Updates the coordinates of pacman via the matrix input
 * * use row and columns pointers to update straight from the function
 */
void update_index_via_order(int* row, int* col, int n, int m, char current_order, char last_order) {
    if (current_order == '#') {
        switch (last_order) {
            case 'R': (*col)++; *col >= m ? *col = 0: 0; break; //move Right
            case 'L': (*col)--; *col < 0 ? *col = m - 1: 0; break; //move LEFT
            case 'U': (*row)--; *row < 0 ? *row = n - 1: 0; break; //move UP
            case 'D': (*row)++; *row >= n ? *row = 0: 0;break; //move DOWN
        }
    } else {
        switch (current_order) {
            case 'R': (*col)++; *col >= m ? *col = 0: 0; break; //move Right
            case 'L': (*col)--; *col < 0 ? *col = m - 1: 0; break; //move LEFT
            case 'U': (*row)--; *row < 0 ? *row = n - 1: 0; break; //move UP
            case 'D': (*row)++; *row >= n ? *row = 0: 0;break; //move DOWN
        }
    }
}

/**
 * Counts the length of pacman steps (cyclic)
 * * use row and columns pointers to update straight from the function
 *
 * @param mat - the matrix describing pacman steps
 * @param n - the number of rows of the matrix
 * @param m - the number of columns of the matrix
 */
int lenPacmanPath(char mat[][M], int n, int m) {
    int flag = 1, row = 0, col = 0; //sets variable to track movement
    char current_order = 0, last_order = 0; //variables for inputs via Matrix
    int counter = 0;
    int last_location[2] = {0,0}; //coordinates of pacman, starts at (0,0)

    while (flag) { //stops only if pacman hits (0,0) after first iteration
        current_order = mat[row][col];
        //use function to track and update pacman movements
        update_index_via_order(&row, &col, n, m, current_order, last_order);
        if (current_order != '#') { //keeps the loop as long as '#' is an input
            last_order = current_order;
        }
        last_location[0] = row;
        last_location[1] = col;
        counter++;
        //checks location is not (0,0)
        if (last_location[0] == 0 && last_location[1] == 0 && counter > 0) {
            flag = 0;
        }
    }
    return counter;
}