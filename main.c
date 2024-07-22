#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Struct
typedef struct Store {
    int x, y;         //Coordinates
    char name[21];    //Name
} Store;

//Variables
Store stores[16];
int final_pairs[16];
double min_distance;
int n;

//Calculate distance between stores
double calculate_distance(int i, int j) {
    double x_diff = stores[i].x - stores[j].x;
    double y_diff = stores[i].y - stores[j].y;
    return sqrt(x_diff * x_diff + y_diff * y_diff);
}

//Function to find minimum distance with stores
void find_minimum_distance(int used[], int pairs[], int index, double current_distance) {

    //If all the pairs are made, check if the current distance is less than minimum distance
    if (index == 2 * n) {
        if (current_distance < min_distance) {
            min_distance = current_distance;
            memcpy(final_pairs, pairs, 2 * n * sizeof(int));
        }
        return;
    }

    //If current store is used, move to next store
    if (used[index]) {
        find_minimum_distance(used, pairs, index + 1, current_distance);
        return;
    }

    //Pairing current store with each subsequent store
    for (int i = index + 1; i < 2 * n; i++) {
        if (!used[i]) {
            used[index] = used[i] = 1;
            pairs[index] = i;
            pairs[i] = index;

            //Recursively find the minimum distance with new pair added
            find_minimum_distance(used, pairs, index + 1, current_distance + calculate_distance(index, i));
            used[index] = used[i] = 0;
        }
    }
}

int main(void) {
    int c;

    //# of Test Cases
    scanf("%d", &c);

    for (int case_num = 0; case_num < c; case_num++) {
        
        //# of Store Pairs
        scanf("%d", &n);

        //For loop to read store information
        for (int i = 0; i < 2 * n; i++) {
            scanf("%d %d %s", &stores[i].x, &stores[i].y, stores[i].name);
        }

        int used[16] = {0};
        int pairs[16];
        min_distance = INFINITY;

        //Find minimum distance
        find_minimum_distance(used, pairs, 0, 0.0);

        //Print minimum distance
        printf("%.3f\n", min_distance);

        //Print pairs
        for (int i = 0; i < 2 * n; i++) {
            if (i < final_pairs[i]) {
                int j = final_pairs[i];
                printf("(%s, %s, %.3f)\n", stores[i].name, stores[j].name, calculate_distance(i, j));
            }
        }
    }

    return 0;
}