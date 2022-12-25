#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_MAX_LENGTH 10
#define TOKEN_BUFFER_LENGTH 3
#define TOKEN_LENGTH 10

int cycle = 0;
int X = 1;
int accumulator = 0;

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

void handleCycle() {
    cycle += 1;

    if ((cycle - 20) % 40 == 0) {
        printf("cycle count was %d\n", cycle);
        accumulator += X * cycle;
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

    printf("accumulator: %d\n", accumulator);

    fclose(file);

    return 0;
}
