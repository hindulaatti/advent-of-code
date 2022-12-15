#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100

int getPriority(char character) {
    if (character == 0) {
        return (int) 0;
    }

    if (isupper((int) character)) {
        return (int) character - 64 + 26;
    }

    return (int) character - 96;
}

int getDoubleCharacter(char buffers[3][MAX_LENGTH]) {
    printf("buffer0 %s\n", buffers[0]);
    printf("buffer1 %s\n", buffers[1]);
    printf("buffer2 %s\n", buffers[2]);

    for (int i = 0; i < (int) strlen(buffers[0]); i++) {
        char charToCompare[2] = {0, '\0'};
        charToCompare[0] = buffers[0][i];
        char compare = buffers[1][strcspn(buffers[1], charToCompare)];
        if (compare && buffers[2][strcspn(buffers[2], charToCompare)] != 0) {
            printf("matching char was %c\n", compare);
            return compare;
        }
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

    char buffer[MAX_LENGTH];
    char buffers[3][MAX_LENGTH];
    
    int accumulator = 0;
    int i = 0;

    while (fgets(buffer, MAX_LENGTH, file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;

        strcpy(buffers[i], buffer);

        if (i == 2) {
            int result = getPriority(getDoubleCharacter(buffers));
            accumulator += result;
        }
        i = (i + 1) % 3;
    }

    fclose(file);

    printf("%d", accumulator);

    return 0;
}
