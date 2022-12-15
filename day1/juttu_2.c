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
	int top2 = 0;
	int top3 = 0;

	while (fgets(buffer, MAX_LENGTH, file)) {
		if (!strcmp(buffer, "\n")) {
			if (accumulator > max) {
				top3 = top2;
				top2 = max;
				max = accumulator;
			} else if (accumulator > top2) {
				top3 = top2;
				top2 = accumulator;
			} else if (accumulator > top3) {
				top3 = accumulator;
			}
			accumulator = 0;
			continue;
		}
        accumulator += (int) strtol(buffer, (char **)NULL, 10);
	}

	fclose(file);

	printf("max: %d\n", max);
	printf("top2: %d\n", top2);
	printf("top3: %d\n", top3);

	printf("sum top3: %d\n", max + top2 + top3);

	return 0;
}
