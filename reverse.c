#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFile(char *fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", fileName);
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);
    char* fileContents = malloc(sizeof(fileSize+1));
    if ( fileContents == NULL){
        printf("File: %s is empty \n", fileName);
        exit(1);
    }
    fread(fileContents, sizeof(char), fileSize, file);
    fileContents[fileSize] = '\0';
    fclose(file);
    return fileContents;
}

char* getValueFromConsole(char *message) {
    char *value;
    size_t len = 0;
    printf("%s", message);
    if (getline(&value, &len, stdin) == -1) {
        fprintf(stderr, "error: cannot read value from console\n");
        exit(1);
    }
    value[strcspn(value, "\n")] = '\0';
    return value;
}

int main(int argc, char *argv[]) {
    char *inputFile;
    char *outputFile;

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    if (argc == 1) {
        inputFile = getValueFromConsole("Input file: ");
        outputFile = getValueFromConsole("Output file: ");
    } else if (argc == 2) {
        inputFile = argv[1];
        outputFile = getValueFromConsole("Output file: ");
    } else {
        inputFile = argv[1];
        outputFile = argv[2];
    }

    if (strcmp(inputFile, outputFile) == 0) {
        fprintf(stderr, "reverse: input and output file must differ\n");
        exit(1);
    }

    char *fileContents = readFile(inputFile);


}

