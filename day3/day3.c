#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getPriority(char character) {
    if (character == 0) {
        return (int) 0;
    }

    if (isupper((int) character)) {
        return (int) character - 64 + 26;
    }

    return (int) character - 96;
}

int getDoubleCharacter(char buffer[]) {
    const int bufferLength = (int) strlen(buffer);
    const int compartmentLength = bufferLength/2;

    char firstCompartment[compartmentLength + 1];
    char secondCompartment[compartmentLength + 1];
    firstCompartment[compartmentLength] = '\0';
    secondCompartment[compartmentLength] = '\0';

    for (int i = 0; i < bufferLength; i++) {
        if (i < compartmentLength) {
            firstCompartment[i] = buffer[i];
            continue;
        }

        secondCompartment[i - compartmentLength] = buffer[i];
    }

    for (int i = 0; i < compartmentLength; i++) {
        char charToCompare[2] = {0, '\0'};
        charToCompare[0] = firstCompartment[i];
        char compare = secondCompartment[strcspn(secondCompartment, charToCompare)];
        if (compare) return compare;
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

    const unsigned MAX_LENGTH = 100;
    char buffer[MAX_LENGTH];
    
    int accumulator = 0;

    while (fgets(buffer, MAX_LENGTH, file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        int result = getPriority(getDoubleCharacter(buffer));
        accumulator += result;
    }

    fclose(file);

    printf("%d", accumulator);

    return 0;
}
