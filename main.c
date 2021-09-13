#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define WIDTH 50
#define HEIGHT 25
#define WALLS 5

void printArray(int array[HEIGHT][WIDTH]) {
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            printf("%c", array[y][x] == 1 ? 'O' : array[y][x] == 2 ? '.' : ' ');
        }
        printf("\n");
    }
}

void printCostArray(double array[HEIGHT][WIDTH]) {
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            printf("%f ", array[y][x]);
        }
        printf("\n");
    }
}

void initializeArray(int array[HEIGHT][WIDTH]) {
    // Set random seed
    srand(time(0));

    // Initalize array
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            int value = rand() % WALLS;
            if (value != 1) value = 0;
            array[y][x] = value;
        }
    }

    // Add walls
    for (int i=0; i<WIDTH; i++) {
        array[0][i] = 1;
        array[HEIGHT-1][i] = 1;
    }
    for (int i=0; i<HEIGHT; i++) {
        array[i][0] = 1;
        array[i][WIDTH-1] = 1;
    }
}

void cleanIntArray(int array[HEIGHT][WIDTH]) {
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            array[y][x] = 0;
        }
    }
}

void cleanDoubleArray(double array[HEIGHT][WIDTH]) {
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            array[y][x] = 0;
        }
    }
}

void cleanParentArray(int array[HEIGHT][WIDTH][2]) {
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            array[y][x][0] = -1;
            array[y][x][1] = -1;
        }
    }
}

void calculateHeuristics(double h[HEIGHT][WIDTH], double g[HEIGHT][WIDTH], double f[HEIGHT][WIDTH], int end[2]) {
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            h[y][x] = sqrt(pow(end[1] - x, 2) + pow(end[0] - y, 2));
            f[y][x] = g[y][x] + h[y][x];
        }
    }
}

int* getNewCurrent(double f[HEIGHT][WIDTH], int array[HEIGHT][WIDTH], int open[HEIGHT][WIDTH]) {
    static int lowest[2] = {-1, -1};
    int lowestValue = 99999;
    for (int y=0; y<HEIGHT; y++) {
        for (int x=0; x<WIDTH; x++) {
            if (f[y][x] < lowestValue && open[y][x] == 1) {
                lowest[0] = y;
                lowest[1] = x;
                lowestValue = f[lowest[0]][lowest[1]];
            }
        }
    }
    return lowest;
}

void reconstruct(int* current, int parent[HEIGHT][WIDTH][2], int array[HEIGHT][WIDTH]) {
    while (parent[current[0]][current[1]][0] != -1) {
        array[parent[current[0]][current[1]][0]][parent[current[0]][current[1]][1]] = 2;
        current[0] = parent[current[0]][current[1]][0];
        current[1] = parent[current[0]][current[1]][1];
    }
    printf("\n");
    printArray(array);
    printf("\n");
}

int main(int argc, char** argv) {
    int array[HEIGHT][WIDTH];
    int parent[HEIGHT][WIDTH][2];

    double f[HEIGHT][WIDTH];
    double g[HEIGHT][WIDTH];
    double h[HEIGHT][WIDTH];

    int* current;
    int done = 0;
    int numOpen = 0;
    int open[HEIGHT][WIDTH];
    int closed[HEIGHT][WIDTH];

    int start[2] = {1, 1};
    int end[2] = {HEIGHT-2, WIDTH-2};

    array[start[0]][start[1]] = 2;
    array[end[0]][end[1]] = 2;

    initializeArray(array);
    cleanParentArray(parent);
    cleanDoubleArray(f);
    cleanDoubleArray(g);
    cleanDoubleArray(h);
    calculateHeuristics(h, g, f, end);
    cleanIntArray(open);
    cleanIntArray(closed);

    open[start[0]][start[1]] = 1;
    numOpen++;

    while (numOpen > 0 && done == 0) {
        current = getNewCurrent(f, array, open);

        if (current[0] == end[0] && current[1] == end[1]) {
            done = 1;
            reconstruct(current, parent, array);
            return 0;
        }

        open[current[0]][current[1]] = 0;
        numOpen--;
        closed[current[0]][current[1]] = 1;

        for (int y=current[0]-1; y<current[0]+2; y++) {
            for (int x=current[1]-1; x<current[1]+2; x++) {
                if (x < 0 || y < 0 || x > WIDTH-1 || y > HEIGHT-1 ||
                    abs(current[0] - y) == abs(current[1] - x) ||
                    closed[y][x] == 1 || array[y][x] == 1) {
                    continue;
                }

                double tempG = g[current[0]][current[1]] + 1;
                if (open[y][x] == 1) {
                    if (tempG < g[y][x]) {
                        g[y][x] = tempG;
                        f[y][x] = g[y][x] + h[y][x];
                        parent[y][x][0] = current[0];
                        parent[y][x][1] = current[1];
                    }
                }
                else {
                    g[y][x] = tempG;
                    open[y][x] = 1;
                    numOpen++;
                    f[y][x] = g[y][x] + h[y][x];
                    parent[y][x][0] = current[0];
                    parent[y][x][1] = current[1];
                }
            }
        }
    }
    if (numOpen == 0 && done == 0) {
        done = 1;
        printf("\n");
        printArray(array);
        printf("\nNo solution!\n\n");
    }

    return 0;
}