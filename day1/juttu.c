#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char *filename = "input.txt";
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
       printf("Error: could not open file %s", filename);
       return 1;
	};

	const unsigned MAX_LENGTH = 256;
	char buffer[MAX_LENGTH];
	
	int accumulator = 0;
	int max = 0;

	while (fgets(buffer, MAX_LENGTH, file)) {
		if (!strcmp(buffer, "\n")) {
			if (accumulator > max) {
				max = accumulator;
			}
			accumulator = 0;
			continue;
		}
        accumulator += (int) strtol(buffer, (char **)NULL, 10);
	}

	fclose(file);

	printf("%d", max);

	return 0;
}
