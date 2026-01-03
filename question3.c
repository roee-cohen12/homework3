#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define EPSILON 0.0001

int min_between_index(int arr[], int n);
int floor_pow_1_5(int i);
int max_between_index(int arr[], int start, int stop);
bool can_the_robot_pass(int p[], int n, int weight, int d);
int max_robot_weight(int p[], int n, int d);

/**
 * tool function for max_robot_weight
 * returns the value of an integer to 1.5 power floored using binary search
 * start by getting the average of the number with zero and check if the
 * squared value is bigger then the original number continue until they almost
 * the same (using epsilon range of error)
 * O(log(n))
*/
int floor_pow_1_5(int i) {
    double left = 0, right = i, mid = 0;

    while (right - left > EPSILON) {

        mid = (left + right) / 2.0;

        if (mid * mid > i) {
           right = mid;

        } else {
            left = mid;
        }
    }
    return (int)(i * mid);
}

/**
 * tool function for max_robot_weight
 * returns the max value in array between fixed range
 * O(n)
*/
int max_between_index(int arr[], int start, int stop) {
    int max = arr[start];
    for (int i = start; i < start + stop; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

/**
 * tool function for max_robot_weight
 * returns the min value in array
 * O(n)
*/
int min_between_index(int arr[], int n) {
    int min = arr[0];
    for (int i = 0; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

/**
 * tool function for max_robot_weight
 * returns if the robot can pass the bridge with specific weight
 * check if between given range d the number of continues segments with weight
 * less then the given one is bigger if so return false
 * O(n)
*/
bool can_the_robot_pass(int p[], int n, int weight, int d) {
    int count_less_then_weight = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] < weight) {
           count_less_then_weight++; //the robot can not step on this segment
        }
        if (count_less_then_weight >= d) {
            return false; //the robot can not pass the bridge with this weight
        }
        if (i % d == 0) { //resets every d steps
            count_less_then_weight = 0;
        }
    }
    return true;
}

int max_robot_weight(int p[], int n, int d) {
    /* first update the array of values to the lumorian value using the
     * formula: S_i = [i ^ 1.5](floored) + P_i
     * S_i --> the lumorian value, i --> the index, P_i --> arr[i]
     */
    for (int i = 0; i < n; i++) {
        p[i] += floor_pow_1_5(i); //use floor_pow for calculating sqrt
    }
    //the robot must step on the first and last step --> return the min between
    if (d == n) { return p[0] < p[n - 1] ? p[0] : p[n - 1]; }
    //the robot must step on each step --> return the min between the array
    if (d == 1) { return min_between_index(p, n); }

    /*the max value of the robot will always be less or equal to the min weight
     between the first and the last step
     use binary search to search for the maximum weight the robot can carry
    */
    int high = p[0] > p[n - 1] ? p[n - 1] : p[0];
    int low = 0, mid;
    while (low <= high) {
        mid = (high + low) / 2;
        if (can_the_robot_pass(p, n, mid, d)) {
            low = mid + 1; //increase the weight as we search for the max weight
        } else {
            high = mid - 1; //the robot can not pass with this weight
        }
    }
    return high; //this will be the maximum value at the end of the search
}

int main(void) {
    int n, d;
    if (scanf("%d", &n) != 1) {
        return 1;
    }
    int *p = (int*)malloc(sizeof(int) * n);
    if (!p) {
        return 1;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%d", p + i) != 1) {
            free(p);
            return 1;
        }
    }
    if (scanf("%d", &d) != 1) {
        free(p);
        return 1;
    }
    printf("%d", max_robot_weight(p, n, d));
    free(p);
    return 0;
}