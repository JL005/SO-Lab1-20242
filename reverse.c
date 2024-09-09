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


int main(int argc, char *argv[]) {

    char *fileContents = readFile("input.txt");
    

}

