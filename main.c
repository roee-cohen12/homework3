#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define M 1000
#define FOUR_ROWS 4

int lenPacmanPath(char mat[][M], int n, int m);
void update_index_via_order(int* row, int* col, int n, int m, char order);
bool check_locations(int arr[2]);
int update_last_movements(int locations[][M], int x, int y);
void fill_locations_matrix(int mat[][M]);


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
    scanf(" %d %d", &n, &m);
    // allocating the matrix - will be explained later in the course
    char (*mat)[M] = malloc(n * M * sizeof(char));
    if (mat) {
        fillMatrix(mat, n, m);
        student_output = lenPacmanPath(mat, n, m);
    }
    printf("%d", student_output);
    // Freeing the matrix - will be explained later in the course
    free(mat);
    return 0;
}

void fill_locations_matrix(int mat[][M]) {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            mat[i][j] = -1;
        }
    }
}

/** tool function for lenPacmanPath
 * Updates the coordinates of pacman via the matrix input
 * use row and columns pointers to update straight from the function
 * cannot pass the boundaries hence, pacman movement is cyclic
 */
void update_index_via_order(int* row, int* col, int n, int m, char order) {
        switch (order) {
            case 'R': (*col)++; *col >= m ? *col = 0: 0; return; //move Right
            case 'L': (*col)--; *col < 0 ? *col = m - 1: 0; return; //move LEFT
            case 'U': (*row)--; *row < 0 ? *row = n - 1: 0; return; //move UP
            case 'D': (*row)++; *row >= n ? *row = 0: 0; return; //move DOWN
            default: return;
        }
}
/** tool function for lenPacmanPath
 * Document pacmans last locations only if input wasn't '#'
 * also checks if a given input is in the last 4 coordinates
 * if input was registered before pacman is in a loop --> return 0
 * otherwise update the coordinates
 */
int update_last_movements(int locations[][M], int x, int y) {
    if (locations[x][y] == 1) {
        return 0;
    }
    locations[x][y] = 1;
    return 1;
}

/** tool function for lenPacmanPath
 * checks if pacman is at (0 , 0) thus completed the path
 * uses the last four locations array
 */
bool check_locations(int arr[2]) {
    return arr[0] == 0 && arr[1] == 0;
}

/**
 * Counts the length of pacman steps (cyclic)
 * use tool functions for simplification
 * @param mat - the matrix describing pacman steps
 * @param n - the number of rows of the matrix
 * @param m - the number of columns of the matrix
 */
int lenPacmanPath(char mat[][M], int n, int m) {
    //sets variable to track movement
    int row = 0, col = 0, counter = 0;
    char order = 0, check_order = 0; //variables for inputs via Matrix
    int document_locations[M][M]; fill_locations_matrix(document_locations);
    int last_location[2] = {0};

    while (true) { //stops only if pacman hits (0,0) after first iteration
        //printf("im here\n");
        check_order = mat[row][col];
        if (check_order != '#') { //'#' means move according to last order
            order = check_order;
        }
        //use function to track and update pacman movements
        update_index_via_order(&row, &col, n, m, order);
        if (!update_last_movements(document_locations, row, col)) {
            return -1;
        }
        last_location[0] = row; last_location[1] = col;
        counter++; //update steps
        //checks location is not (0,0)
        if (check_locations(last_location) && counter > 0) {
            return counter;
        }
    }
}