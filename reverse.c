#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

char* readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", fileName);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    char* fileContents = (char*)malloc(fileSize+1);
    if ( fileContents == NULL){
        fprintf(stderr, "reverse: %s is empty \n", fileName);
        exit(1);
    }
    fread(fileContents, sizeof(char), fileSize, file);
    fileContents[fileSize] = '\0';
    fclose(file);
    return fileContents;
}

int countLines(char *fileContent){
    int lineCount = 0;
    for (int i = 0; fileContent[i] != '\0'; i++) {
        if (fileContent[i] == '\n') {
            lineCount++;
        }
    }
    return lineCount;
}

char** splitLines(char *fileContent, int lineCount){
    char **lines = (char**)malloc(lineCount * sizeof(char*));
    if (lines == NULL){
        fprintf(stderr, "Error allocating memory for lines\n");
        exit(1);
    }
    char *line = strtok(fileContent, "\n");
    int i = 0;
    while (line != NULL) {
        lines[i] = line;
        line = strtok(NULL, "\n");
        i++;
    }
    return lines;
}


void writeFile(char *fileName, char **lines, int lineCount) {
    FILE *file = fopen(fileName, "w");
    if (file == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s' for writing\n", fileName);
        exit(1);
    }

    for (int i = lineCount - 1; i >= 0; i--) {
        fprintf(file, "%s\n", lines[i]);
        //printf("%s\n", lines[i]);
    }

    fclose(file);
}

void freeMemory(char **lines, int lineCount) {
    for (int i = 0; i < lineCount; i++) {
        free(lines[i]);
    }
    free(lines);
}


void compare_files(const char *file1, const char *file2) {
    struct stat stat1, stat2;

    if (lstat(file1, &stat1) != 0) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", file1);
        exit(1);
    }

    if (lstat(file2, &stat2) != 0) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", file2);
        exit(1);
    }

    if ((stat1.st_ino == stat2.st_ino && stat1.st_dev == stat2.st_dev) || strcmp(file1, file2) == 0 ) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }

}


int main(int argc, char *argv[]) {
    char *inputFile;
    char *outputFile;

    inputFile = argv[1];
    outputFile = argv[2];

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    compare_files(inputFile, outputFile);

    char *fileContents = readFile(inputFile);

    int lineCount = countLines(fileContents);

    char **lines = splitLines(fileContents, lineCount);

    writeFile(outputFile, lines, lineCount);

    free(lines);
    free(fileContents);
    return 0;
}