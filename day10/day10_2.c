#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_MAX_LENGTH 10
#define TOKEN_BUFFER_LENGTH 3
#define TOKEN_LENGTH 10
#define RENDER_WIDTH 40
#define RENDER_HEIGHT 10

int cycle = 0;
int X = 1;
int rowIndex = 0;
int rendered[RENDER_HEIGHT + 1][RENDER_WIDTH + 1];

void splitstr(char *strToSplit, char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH], char *divider) {
    char *token;
    token = strtok(strToSplit, divider);

    int i = 0;

    while( token != NULL ) {
        strcpy(tokenBuffer[i], token);
        token = strtok(NULL, divider);
        i++;
    }
    char *nullAnswer = "\0";
    strcpy(tokenBuffer[i], nullAnswer);
}

void renderImage() {
    for (int i = 0; i < RENDER_HEIGHT; i++) {
        for (int j = 0; j < RENDER_WIDTH; j++) {
            printf("%c", rendered[i][j]);
        }
        printf("\n");
    }
}

void render(char c) {
    rendered[rowIndex][cycle % 40] = c;
}

void handleCycle() {
    cycle += 1;

    if (cycle % RENDER_WIDTH == X
    || cycle % RENDER_WIDTH == X + 1
    || cycle % RENDER_WIDTH == X + 2
    ) {
        render('#');
    } else {
        render('.');
    }

    if (cycle % RENDER_WIDTH == 0) {
        rowIndex += 1;
    }
}

void handleLogic(char* buffer) {
    printf("%s\n", buffer);
    handleCycle();

    char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH];
    splitstr(buffer, tokenBuffer, " ");

    if (strcmp(tokenBuffer[0], "addx") == 0) {
        int xToAdd = (int) strtol(tokenBuffer[1], (char **)NULL, 10);
        handleCycle();
        X += xToAdd;
    }

    printf("\tcycle: %d\n", cycle);
    printf("\tX: %d\n", X);
}

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       printf("Error: could not open file %s\n", filename);
       return 1;
    };

    char buffer[BUFFER_MAX_LENGTH];

    while (fgets(buffer, BUFFER_MAX_LENGTH, file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        handleLogic(buffer);
    }

    renderImage();

    fclose(file);

    return 0;
}
