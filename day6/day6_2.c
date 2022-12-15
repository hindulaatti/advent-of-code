#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define UNIQUE_NEEDED 14

int compare(char buffer[UNIQUE_NEEDED + 1]) {
    int numOfUnique = 0;

    for (int i = 0; i < UNIQUE_NEEDED; i++) {
        char * pfirst;
        char * plast;

        pfirst = strchr(buffer, buffer[i]);
        plast = strrchr(buffer, buffer[i]);

        if (pfirst == plast) {
            numOfUnique++;
        }
    }

    printf("%d\n", numOfUnique);

    if (numOfUnique == UNIQUE_NEEDED) {
        return 1;
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

    char buffer[UNIQUE_NEEDED + 1];
    buffer[UNIQUE_NEEDED] = 0;
    char letter;

    int i = 0;

    while( (letter = getc(file)) != EOF) {
        for(int j = UNIQUE_NEEDED - 2; j >= 0; j--) {
            buffer[j + 1] = buffer[j];
        }

        buffer[0] = letter;

        i++;

        if (i < UNIQUE_NEEDED) {
            continue;
        }

        if (compare(buffer)) {
            break;
        }
    }

    printf("chars needed to read: %d\n", i);

    fclose(file);

    return 0;
}
