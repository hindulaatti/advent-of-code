#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getHand(char character) {
    // rock
    if (character == 'A' || character == 'X')
    {
        return 1;
    }

    // paper
    if (character == 'B' || character == 'Y')
    {
        return 2;
    }

    // scissors
    if (character == 'C' || character == 'Z')
    {
        return 3;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       printf("Error: could not open file %s", filename);
       return 1;
    };

    const unsigned MAX_LENGTH = 5;
    char buffer[MAX_LENGTH];
    
    int points = 0;

    while (fgets(buffer, MAX_LENGTH, file)) {
        int theirHand = getHand(buffer[0]);
        int myHand = getHand(buffer[2]);

        if (myHand == 2) {
            // draw
            myHand = theirHand;
        } else if (myHand == 1) {
            // lose
            myHand = theirHand + 2;
        } else if (myHand == 3) {
            // win
            myHand = theirHand + 1;
        }

        myHand = ((myHand - 1) % 3) + 1;

        points += myHand;

        printf("hands: %d, %d\n", theirHand, myHand);

        if (theirHand == myHand) {
            points += 3;
            continue;
        }

        if ((theirHand + 1) % 3 == myHand % 3) {
            points += 6;
            continue;
        }
    }

    fclose(file);

    printf("%d", points);

    return 0;
}