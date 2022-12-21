#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define GRID_SIDE 99

void printGrid(int grid[GRID_SIDE][GRID_SIDE]) {
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            printf("%d", grid[i][j]);
        }
        printf("\n");
    }
}

void initializeIsVisibleGrid(int grid[GRID_SIDE][GRID_SIDE]) {
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            if (i == 0 || i == GRID_SIDE - 1 || j == 0 || j == GRID_SIDE - 1) {
                grid[i][j] = 1;
                continue;
            }

            grid[i][j] = 0;
        }
    }
}

int visibleFromRight(int grid[GRID_SIDE][GRID_SIDE], int isVisibleGrid[GRID_SIDE][GRID_SIDE], int y, int x) {
    for (int i = x + 1; i < GRID_SIDE; i++) {
        if (grid[y][i] >= grid[y][x]) {
            return 0;
        }
    }

    return 1;
}

int visibleFromBottom(int grid[GRID_SIDE][GRID_SIDE], int isVisibleGrid[GRID_SIDE][GRID_SIDE], int y, int x) {
    for (int i = y + 1; i < GRID_SIDE; i++) {
        if (grid[i][x] >= grid[y][x]) {
            return 0;
        }
    }

    return 1;
}

int visibleFromLeft(int grid[GRID_SIDE][GRID_SIDE], int isVisibleGrid[GRID_SIDE][GRID_SIDE], int y, int x) {
    for (int i = 0; i < x; i++) {
        if (grid[y][i] >= grid[y][x]) {
            return 0;
        }
    }

    return 1;
}

int visibleFromTop(int grid[GRID_SIDE][GRID_SIDE], int isVisibleGrid[GRID_SIDE][GRID_SIDE], int y, int x) {
    for (int i = 0; i < y; i++) {
        if (grid[i][x] >= grid[y][x]) {
            return 0;
        }
    }

    return 1;
}

int isSide(int i, int j) {
    return i == 0 || i == GRID_SIDE - 1 || j == 0 || j == GRID_SIDE - 1;
}

void calcVisibilities(int grid[GRID_SIDE][GRID_SIDE], int isVisibleGrid[GRID_SIDE][GRID_SIDE]) {
    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            isVisibleGrid[i][j] = 
                isSide(i, j)
                || visibleFromLeft(grid, isVisibleGrid, i, j)
                || visibleFromRight(grid, isVisibleGrid, i, j)
                || visibleFromTop(grid, isVisibleGrid, i, j)
                || visibleFromBottom(grid, isVisibleGrid, i, j);
        }
    }
}

void printHowManyTrees(int grid[GRID_SIDE][GRID_SIDE]) {
    int sum = 0;

    for (int i = 0; i < GRID_SIDE; i++) {
        for (int j = 0; j < GRID_SIDE; j++) {
            sum += grid[i][j];
        }
    }

    printf("trees visible: %d", sum);
}

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       printf("Error: could not open file %s\n", filename);
       return 1;
    };

    char buffer;
    int i = 0;
    int j = 0;
    int grid[GRID_SIDE][GRID_SIDE];
    int isVisibleGrid[GRID_SIDE][GRID_SIDE];

    //initializeIsVisibleGrid(isVisibleGrid);

    while( (buffer = getc(file)) != EOF) {
        if (buffer == '\n') {
            i++;
            j = 0;
            continue;
        }

        grid[i][j] = buffer - '0';

        j++;
    }

    calcVisibilities(grid, isVisibleGrid);

    printGrid(isVisibleGrid);

    printHowManyTrees(isVisibleGrid);

    fclose(file);

    return 0;
}
