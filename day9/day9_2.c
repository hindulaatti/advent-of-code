#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// D + space + digit + digit + \n + \0
#define BUFFER_MAX_LENGTH 6
#define KNOT_AMOUNT 10

typedef struct Node {
    int coordinates[2];
    struct Node* next;
} node;

// 0, 0 is unique
int distinctTailPositions = 0;
node* currentTail = NULL;
int knotPos[KNOT_AMOUNT][2];
int lastKnotPos[KNOT_AMOUNT][2];

void initializeKnotPos() {
    for (int i = 0; i < KNOT_AMOUNT; i++) {
        knotPos[i][0] = 0;
        knotPos[i][1] = 0;
        lastKnotPos[i][0] = 0;
        lastKnotPos[i][1] = 0;
    }
}

int getAmountToMove(char* buffer) {
    char number[3] = {buffer[2], buffer[3], '\0'}; 
    return (int) strtol(number, (char **)NULL, 10);
}

void handleMovement(char direction, int headPos[2]) {
    switch (direction) {
        case 'U':
            headPos[1]++;
            break;
        case 'D':
            headPos[1]--;
            break;
        case 'L':
            headPos[0]--;
            break;
        case 'R':
            headPos[0]++;
            break;
    }
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

void printRope() {
    printf("\t");
    for (int j = 0; j < KNOT_AMOUNT; j++) {
        printf("%d, %d | ", knotPos[j][0], knotPos[j][1]);
    }
    printf("\n");
}

int horizontalDistance(int head[2], int tail[2]) {
    return head[0] - tail[0];
}

int verticalDistance(int head[2], int tail[2]) {
    return head[1] - tail[1];
}

int sign(int integer) {
    return (0 < integer) - (integer < 0);
}

void handleLogic(char direction, int amount) {
    printf("%c %d\n", direction, amount);

    for (int i = 0; i < amount; i++) {
        handleMovement(direction, knotPos[0]);

        // this logic was borrowed from reddit after 5 hours of wondering why my logic didnt work.
        // the example in the assignment worked just fine.
        // i quess the point here is to 
        // move 1 step in to every direction where previous knot was if its too far away
        for (int j = 1; j < KNOT_AMOUNT; j++) {
            int horDiff = horizontalDistance(knotPos[j - 1], knotPos[j]);
            int vertDiff = verticalDistance(knotPos[j - 1], knotPos[j]);

            if (abs(horDiff) < 2 && abs(vertDiff) < 2) {
                break;
            }

            knotPos[j][0] += sign(horDiff);
            knotPos[j][1] += sign(vertDiff);
        }

        printRope();

        createNewTail(knotPos[KNOT_AMOUNT - 1]);

        printf("\tcurrentTail: %d, %d\n", currentTail->coordinates[0], currentTail->coordinates[1]);

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
    currentTail = (node*)malloc(sizeof(node));
    initializeKnotPos();

    int amountToMove = 0;
    createNewTail(knotPos[0]);
    distinctTailPositions += 1;

    while (fgets(buffer, BUFFER_MAX_LENGTH, file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        amountToMove = getAmountToMove(buffer);
        handleLogic(buffer[0], amountToMove);
    }

    printf("distinct tail positions: %d\n", distinctTailPositions);

    fclose(file);

    return 0;
}
