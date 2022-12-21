#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define GRID_SIDE 99

int visibilityToRight(int grid[GRID_SIDE][GRID_SIDE], int y, int x) {
    int visibility = 0;

    for (int i = x + 1; i < GRID_SIDE; i++) {
        visibility++;

        if (grid[y][i] >= grid[y][x]) {
            return visibility;
        }
    }

    return visibility;
}

int visibilityToBottom(int grid[GRID_SIDE][GRID_SIDE], int y, int x) {
    int visibility = 0;

    for (int i = y + 1; i < GRID_SIDE; i++) {
        visibility++;

        if (grid[i][x] >= grid[y][x]) {
            return visibility;
        }
    }

    return visibility;
}

int visibilityToLeft(int grid[GRID_SIDE][GRID_SIDE], int y, int x) {
    int visibility = 0;

    for (int i = x - 1; i >= 0; i--) {
        visibility++;

        if (grid[y][i] >= grid[y][x]) {
            return visibility;
        }
    }

    return visibility;
}

int visibilityToTop(int grid[GRID_SIDE][GRID_SIDE], int y, int x) {
    int visibility = 0;

    for (int i = y - 1; i >= 0; i--) {
        visibility++;

        if (grid[i][x] >= grid[y][x]) {
            return visibility;
        }
    }

    return visibility;
}

void calcMaxVisibility(int grid[GRID_SIDE][GRID_SIDE]) {
    int maxVisibility = 0;
    int visibility = 0;
    for (int i = 1; i < GRID_SIDE - 1; i++) {
        for (int j = 1; j < GRID_SIDE - 1; j++) {
            visibility = 
                visibilityToLeft(grid, i, j)
                * visibilityToRight(grid, i, j)
                * visibilityToTop(grid, i, j)
                * visibilityToBottom(grid, i, j);
            
            if (visibility > maxVisibility) {
                maxVisibility = visibility;
            }
        }
    }

    printf("max visibility: %d\n", maxVisibility);
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

    while( (buffer = getc(file)) != EOF) {
        if (buffer == '\n') {
            i++;
            j = 0;
            continue;
        }

        grid[i][j] = buffer - '0';

        j++;
    }

    calcMaxVisibility(grid);

    fclose(file);

    return 0;
}
