#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare(char buffer[5]) {
    int numOfUnique = 0;

    for (int i = 0; i < 4; i++) {
        char * pfirst;
        char * plast;

        pfirst = strchr(buffer, buffer[i]);
        plast = strrchr(buffer, buffer[i]);

        if (pfirst == plast) {
            numOfUnique++;
        }
    }

    if (numOfUnique == 4) {
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

    char buffer[5];
    buffer[4] = 0;
    char letter;

    int i = 0;

    while( (letter = getc(file)) != EOF) {
        buffer[3] = buffer[2];
        buffer[2] = buffer[1];
        buffer[1] = buffer[0];
        buffer[0] = letter;

        i++;

        if (i < 4) {
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
