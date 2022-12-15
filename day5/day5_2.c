#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STATE_ROWS 9
#define STATE_LENGTH 100

void printState(char state[STATE_ROWS][STATE_LENGTH]) {
    for (int i = 0; i < STATE_ROWS; i++) {
        printf("%d: ", i);
        for (int j = 0; j < STATE_LENGTH; j++) {
            if(state[i][j] != 0) printf("%c", state[i][j]);
        }
        printf("\n");
    }
}

void printTopOnly(char state[STATE_ROWS][STATE_LENGTH]) {
    for (int i = 0; i < STATE_ROWS; i++) {
        printf("%c", state[i][ (int) strlen(state[i]) - 1 ]);
    }
    printf("\n");
}

void initializeState(char state[STATE_ROWS][STATE_LENGTH]){
    for (int i = 0; i < STATE_ROWS; i++) {
        for (int j = 0; j < STATE_LENGTH; j++) {
            state[i][j] = 0;
        }
    }
}

void parseState(char buffer[], int row, char state[STATE_ROWS][STATE_LENGTH]){
    for (int j = 0; j < STATE_ROWS; j++) {
        if (buffer[j * 4 + 1] == 0) {
            return;
        }
        if (buffer[j * 4 + 1] == ' ') {
            continue;
        }
        state[j][strlen(state[j])] = buffer[j * 4 + 1];
    }
}

void invertState(char state[STATE_ROWS][STATE_LENGTH]) {
    char tempState[STATE_ROWS][STATE_LENGTH];
    initializeState(tempState);
    for (int i = 0; i < STATE_ROWS; i++) {
        for (int j = STATE_LENGTH - 1; j >= 0; j--) {
            tempState[i][strlen(tempState[i])] = state[i][j];
        }

        for (int j = 0; j < STATE_LENGTH; j++) {
            state[i][j] = tempState[i][j];
        }
    }
}

void executeCommand(char state[STATE_ROWS][STATE_LENGTH], int command[3]) {
    int to = command[2] - 1;
    int from = command[1] - 1;

    int toLastIndex = (int) strlen(state[to]) - 1;
    int fromLastIndex = (int) strlen(state[from]) - 1;
    int j = command[0];

    printf("command: %d %d %d\n", j, from, to);

    for(int i = 0; i < command[0]; i++) {
        state[ to ][ toLastIndex + j ] = 
            state[ from ][ fromLastIndex - i ];
        
        state[ from ][ fromLastIndex - i ] = 0;
        j--;
    }

    printState(state);
}

void executeCommands(char *token, char state[STATE_ROWS][STATE_LENGTH], const char* divider) {
    char lastToken[20] = "move";
    int command[3] = {0, 0, 0};

    while( token != NULL ) {
        token = strtok(NULL, divider);

        if (token != NULL) {
            int commandPart = (int) strtol(token, (char **)NULL, 10);
            if (!commandPart) {
                strcpy(lastToken, token);
                continue;
            }

            if (strcmp(lastToken, "move") == 0) {
                command[0] = commandPart;
            }

            if (strcmp(lastToken, "from") == 0) {
                command[1] = commandPart;
            }

            if (strcmp(lastToken, "to") == 0) {
                command[2] = commandPart;
            }
        }
    }

    executeCommand(state, command);
}

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       printf("Error: could not open file %s", filename);
       return 1;
    };

    const unsigned MAX_LENGTH = 256;
    char buffer[MAX_LENGTH];
    
    char state[STATE_ROWS][STATE_LENGTH];
    initializeState(state);

    int i = 0;

    while (fgets(buffer, MAX_LENGTH, file)) {
        if (buffer[1] == '1') {
            break;
        }
        buffer[strcspn(buffer, "\r\n")] = 0;
        parseState(buffer, i, state);
        i++;
    }

    invertState(state);

    printf("Starting state:\n");
    printState(state);
    printTopOnly(state);
    printf("\n");

    char *token;
    const char s[2] = " ";

    while (fgets(buffer, MAX_LENGTH, file)) {
        //printf("buffer: %s\n", buffer);
        token = strtok(buffer, s);
        
        if (strcmp(token, "move") != 0) {
            continue;
        }
        
        executeCommands(token, state, s);

    }


    printf("After sorting:\n");
    printState(state);
    printTopOnly(state);
    printf("\n");

    fclose(file);

    return 0;
}
