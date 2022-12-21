#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_LENGTH 100
#define TOKEN_BUFFER_LENGTH 100
#define TOKEN_LENGTH 100
#define PATH_LENGTH 100
#define PATH_STRING_LENGTH 256
#define DIR_NAME_LENGTH 50
#define FILE_NAME_LENGTH 50
#define DIR_ARRAY_LENGTH 1000
#define MAX_DIRS 10000

typedef struct {
    char key[PATH_STRING_LENGTH]; // path
    int size;
} item;

void calcAndPrintPromptAnswer(item* items) {
    int sum = 0;

    for (size_t i=0; i<DIR_ARRAY_LENGTH; i++) {
        if (strcmp(items[i].key, "\0") == 0 && items[i].size == 0) {
            break;
        }
        if (items[i].size < 100000) {
            sum += items[i].size;
        }
        //printf("key: %s, size: %d\n", items[i].key, items[i].size);
    }

    printf("\n\nsum size of all directories with size less than 100000: %d\n", sum);
};

void printItems(item* items) {
    for (size_t i=0; i<DIR_ARRAY_LENGTH; i++) {
        if (strcmp(items[i].key, "\0") == 0 && items[i].size == 0) {
            return;
        }
        printf("key: %s, size: %d\n", items[i].key, items[i].size);
    }
}

item* linear_search(item* items, size_t size, char* key) {
    for (size_t i=0; i<size; i++) {
        // compare NULL case also
        if (key == NULL && items[i].key[0] == '\0') {
            return &items[i];
        }

        if (key != NULL && strcmp(items[i].key, key) == 0) {
            return &items[i];
        }
    }
    return NULL;
}

item* findDirByPath(item* items, char* key) {
    return linear_search(items, MAX_DIRS, key);
}

item* findUndefinedDir(item* items) {
    return linear_search(items, MAX_DIRS, NULL);
}

void splitstr(char *strToSplit, char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH], char *divider) {
    char *token;
    token = strtok(strToSplit, divider);

    int i = 0;

    while( token != NULL ) {
        strcpy(tokenBuffer[i], token);
        token = strtok(NULL, divider);
        i++;
    }
    char *nullAnswer = "\0";
    strcpy(tokenBuffer[i], nullAnswer);
}

void printTokenArray(char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH], char *divider) {
    int i = 0;

    while (tokenBuffer[i][0] != '\0') {
        printf("%s%s", tokenBuffer[i], divider);
        i++;
    }
    
    printf("\n");
}

int pathFirstEmptyIndex(char path[PATH_LENGTH][DIR_NAME_LENGTH]) {
    for(int i = 0; i < PATH_LENGTH; i++) {
        if (path[i][0] == '\0') {
            return i;
        }
    }

    return NULL;
}

char* getPathString(char* destination, char path[PATH_LENGTH][DIR_NAME_LENGTH]) {
    char pathString[PATH_STRING_LENGTH] = "\0";
    for(int i = 0; i < PATH_LENGTH; i++) {
        if (path[i][0] == '\0') {
            return strcpy(destination, pathString);
        }
        // Dont append dir name if root
        if (strcmp(path[i], "/") != 0) {
            strcat(pathString, path[i]);
        }
        
        strcat(pathString, "/");
    }
    return destination;
}

void printPath(char path[PATH_LENGTH][DIR_NAME_LENGTH]) {
    char pathString[PATH_STRING_LENGTH];
    getPathString(pathString, path);
    printf("\t%s\n", pathString);
}

void initializePath(char path[PATH_LENGTH][DIR_NAME_LENGTH]) {
    for(int i = 0; i < PATH_LENGTH; i++) {
        strcpy(path[i], "\0");
    }
}

void appendToPath(char dir[], char path[PATH_LENGTH][DIR_NAME_LENGTH]) {
    strcpy(path[pathFirstEmptyIndex(path)], dir);
}

void popPath(char path[PATH_LENGTH][DIR_NAME_LENGTH]) {
    strcpy(path[pathFirstEmptyIndex(path) - 1], "\0");
}

void addDirSizeToParent(char path[PATH_LENGTH][DIR_NAME_LENGTH], item* items, char* childPath) {
    char currentPath[PATH_STRING_LENGTH] = "\0";
    getPathString(currentPath, path);
    item* childDir = findDirByPath(items, childPath);
    item* currentDir = findDirByPath(items, currentPath);

    currentDir->size += childDir->size;
    printf("\twent out of directory, child size: %d parent size: %d\n", childDir->size, currentDir->size);
}

void handleCd(char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH], char path[PATH_LENGTH][DIR_NAME_LENGTH], item* items) {
    if ((int) strcmp(tokenBuffer[2], "/") == 0) {
        initializePath(path);
        appendToPath(tokenBuffer[2], path);
        item *newDir = findUndefinedDir(items);
        getPathString(newDir->key, path);
        return;
    }

    if ((int) strcmp(tokenBuffer[2], "..") == 0) {
        char childPath[PATH_STRING_LENGTH] = "\0";
        getPathString(childPath, path);
        popPath(path);
        addDirSizeToParent(path, items, childPath);
        return;
    }

    appendToPath(tokenBuffer[2], path);
    item* newDir = findUndefinedDir(items);
    getPathString(newDir[0].key, path);
}

void handleCommand(char buffer[BUFFER_LENGTH], char path[PATH_LENGTH][DIR_NAME_LENGTH], item* items) {
    char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH];
    splitstr(buffer, tokenBuffer, " ");
    //printTokenArray(tokenBuffer, " ");
    
    if ((int) strcmp(tokenBuffer[1], "cd") == 0) {
        handleCd(tokenBuffer, path, items);
        printPath(path);
        return;
    }

    // command was ls, let outer loop handle file sizes
}

void handleFile(char buffer[BUFFER_LENGTH], item* item) {
    char tokenBuffer[TOKEN_BUFFER_LENGTH][TOKEN_LENGTH];
    splitstr(buffer, tokenBuffer, " ");
    
    if ((int) strcmp(tokenBuffer[0], "dir") != 0) {
        item->size = item->size + (int) strtol(tokenBuffer[0], (char **)NULL, 10);
        printf("\tdir size after file %s: %d\n", tokenBuffer[1], item->size);
    }
}

int main(int argc, char *argv[]) {
    char *filename = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
       printf("Error: could not open file %s\n", filename);
       return 1;
    };

    char buffer[BUFFER_LENGTH];
    char path[PATH_LENGTH][DIR_NAME_LENGTH];
    initializePath(path);

    item items[MAX_DIRS];

    while (fgets(buffer, BUFFER_LENGTH, file)) {
        buffer[strcspn(buffer, "\r\n")] = 0;
        printf("%s\n", buffer);
        if (buffer[0] == '$') {
            handleCommand(buffer, path, items);
            continue;
        }

        char pathString[PATH_STRING_LENGTH];
        getPathString(pathString, path);
        handleFile(buffer, findDirByPath(items, pathString));
    }

    strcpy(buffer, "$ cd ..");
    handleCommand(buffer, path, items);

    printItems(items);
    calcAndPrintPromptAnswer(items);

    fclose(file);

    return 0;
}
