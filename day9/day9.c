#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// D + space + digit + digit + \n + \0
#define BUFFER_MAX_LENGTH 6

typedef struct Node {
    int coordinates[2];
    struct Node* next;
} node;

// 0, 0 is unique
int distinctTailPositions = 0;
node* currentTail = NULL;

int getAmountToMove(char* buffer) {
    char number[3] = {buffer[2], buffer[3], '\0'}; 
    return (int) strtol(number, (char **)NULL, 10);
}

void handleMovement(char direction, int headPos[2]) {
    switch (direction) {
        case 'U':
            headPos[0]++;
            break;
        case 'D':
            headPos[0]--;
            break;
        case 'L':
            headPos[1]--;
            break;
        case 'R':
            headPos[1]++;
            break;
    }
}

int tailIsCloseToHead(int headPos[2], int tailPos[2]) {
    if ((headPos[0] - 1 == tailPos[0]
        || headPos[0] + 1 == tailPos[0]
        || headPos[0] == tailPos[0])
        && (headPos[1] - 1 == tailPos[1]
        || headPos[1] + 1 == tailPos[1]
        || headPos[1] == tailPos[1])) {
        return 1;
    }
    return 0;
}

int tailHasBeenHere(int tailPos[2]) {
    node* tail = currentTail;
    int i = 0;

    while (tail->next != NULL) {
        tail = tail->next;

        if (tail->coordinates[0] == tailPos[0] 
        && tail->coordinates[1] == tailPos[1]) {
            return 1;
        }
        i++;
    }

    printf("\t\ttail count was %d\n", i);

    return 0;
}

void createNewTail(int newTailPos[2]) {
    struct Node* newTail = NULL;
    newTail = (struct Node*)malloc(sizeof(struct Node));
    newTail->coordinates[0] = newTailPos[0];
    newTail->coordinates[1] = newTailPos[1];
    newTail->next = currentTail;
    currentTail = newTail;
}

void handleLogic(char direction, int amount, int headPos[2]) {
    printf("%c %d\n", direction, amount);
    int lastHeadPos[2];

    for (int i = 0; i < amount; i++) {
        lastHeadPos[0] = headPos[0];
        lastHeadPos[1] = headPos[1];
        handleMovement(direction, headPos);
        printf("\t%d, %d\n", headPos[1], headPos[0]);

        if (tailIsCloseToHead(headPos, currentTail->coordinates)) {
            continue;
        }

        createNewTail(lastHeadPos);

        printf("\tcurrentTail: %d, %d\n", currentTail->coordinates[1], currentTail->coordinates[0]);

        if (tailHasBeenHere(currentTail->coordinates)) {
            continue;
        }

        printf("\t\tcurrentTail was unique\n");
        distinctTailPositions += 1;
        printf("\t\tunique tail positions: %d\n\n", distinctTailPositions);
    }
};

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       printf("Error: could not open file %s\n", filename);
       return 1;
    };

    char buffer[BUFFER_MAX_LENGTH];
    int headPos[2] = {0, 0};
    currentTail = (node*)malloc(sizeof(node));

    int amountToMove = 0;
    createNewTail(headPos);
    distinctTailPositions += 1;

    while (fgets(buffer, BUFFER_MAX_LENGTH, file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        amountToMove = getAmountToMove(buffer);
        handleLogic(buffer[0], amountToMove, headPos);
    }

    printf("distinct tail positions: %d\n", distinctTailPositions);

    fclose(file);

    return 0;
}
