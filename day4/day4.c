#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void parseRange(char rangeString[], int* range) {
    int stringLength = (int) strlen(rangeString);

    int dividerLocation = strcspn(rangeString, "-");

    int splitLengths[2] = {dividerLocation + 1, stringLength - dividerLocation};

    char firstString[splitLengths[0]];
    firstString[splitLengths[0]] = '\0';
    char secondString[splitLengths[1]];
    secondString[splitLengths[1]] = '\0';

    for (int i = 0; i < splitLengths[0] - 1; i++) {
        firstString[i] = rangeString[i];
    }

    for (int i = 0; i < splitLengths[1] - 1; i++) {
        secondString[i] = rangeString[i + dividerLocation + 1];
    }

    range[0] = (int) strtol(firstString, (char **)NULL, 10);
    range[1] = (int) strtol(secondString, (char **)NULL, 10);

}

void splitToRanges(char buffer[], int* ranges) {
    int bufferLength = (int) strlen(buffer);

    int dividerLocation = strcspn(buffer, ",");

    int splitLengths[2] = {dividerLocation + 1, bufferLength - dividerLocation};

    char firstString[splitLengths[0]];
    firstString[splitLengths[0]] = '\0';
    char secondString[splitLengths[1]];
    secondString[splitLengths[1]] = '\0';

    for (int i = 0; i < splitLengths[0] - 1; i++) {
        firstString[i] = buffer[i];
    }

    for (int i = 0; i < splitLengths[1] - 1; i++) {
        secondString[i] = buffer[i + dividerLocation + 1];
    }

    parseRange(firstString, &ranges[0]);
    parseRange(secondString, &ranges[2]);
}

int rangeContainsOther(int rangeStart, int rangeEnd, int compareRangeStart, int compareRangeEnd) {
    for(int i = rangeStart; i <= rangeEnd; i++) {
        if (i < compareRangeStart || i > compareRangeEnd) {
            return 0;
        }
    }

    printf("Comparerange was wholy in range\n");
    
    return 1;
}

int doLogic(char buffer[]) {
    printf("%s\n", buffer);

    int ranges[4] = {0,0,0,0};
    
    splitToRanges(buffer, ranges);

    return rangeContainsOther(ranges[0], ranges[1], ranges[2], ranges[3])
        || rangeContainsOther(ranges[2], ranges[3], ranges[0], ranges[1]);

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
        accumulator += doLogic(buffer);
        printf("\n");
    }

    fclose(file);

    printf("%d", accumulator);

    return 0;
}
