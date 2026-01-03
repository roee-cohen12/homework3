#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_SEGMENTS 100 /* m is guaranteed to be between 1 and 100 */

int min(int a, int b) { //return the min between two numbers
    if (a < b) {
        return a;
    }
    return b;
}

/** tool function for calc_trapped_watter
 * returns the sum of the trapped water between the walls
 * follow this logic: starts at wall(0), if the wall to my right is bigger
 * then no water can be trapped between, thus continue, same as the same height
 * if the wall to my right is shorter, continue searching until finding a wall
 * at least the same height
 */
int calc_wall_difference(int arr[], int n) {
    int sum_trapped_water = 0, run_index = 0;//index for searching right wall
    for (int i = 0; i < n; i ++) {
        run_index = i + 1;
        //follow the logic in the description
        if (arr[run_index] > arr[i]) { continue; }
        if (arr[i] > arr[run_index]) { // the wall to my right is shorter
            while (run_index < n && arr[i] > arr[run_index]) {
                run_index++; //search for the boundary wall to my right
            }
            //check if im at the right corner
            if (run_index == n) { run_index--; }

            //calculate the min height between the right and left end side
            int min_between_height = min(arr[i], arr[run_index]);

            //sum the trapped water
            for (int j = i + 1; j < run_index; j++) {
                sum_trapped_water += min_between_height - arr[j];
            }
            if (run_index + 1 == n) { break; } //necessary for ending the loop
            i = run_index - 1; //jump to next segment to check for trpped water
        }
    }
    return sum_trapped_water;
}

/**
 * function resposible for user input, use other fucntion to calculate the
 * trapped water between the walls
 */
int calc_trapped_water() {
    int num_of_segments, wall_index, wall_height;
    int wall_hist[MAX_SEGMENTS] = {0}; //histogram for documenting wall heights

    //first gets the number_of_segments
    scanf("%d", &num_of_segments);
    if (num_of_segments >= MAX_SEGMENTS || num_of_segments < 0) {
        return 0;
    }

    //gets the wall build description
    while (scanf("%d %d", &wall_index, &wall_height) == 2) {
        if (wall_index > num_of_segments || wall_index < 0) {
            continue;
        }
        if (wall_height < 0) {
            continue;
        }
        wall_hist[wall_index] += wall_height;
    }
    return calc_wall_difference(wall_hist, num_of_segments);
}

int main() {
    printf("%d\n", calc_trapped_water());

    return 0;
}