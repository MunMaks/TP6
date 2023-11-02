#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUF_SIZE 65536  // pow(2, 16)

int compteLignes(FILE * file){
    int count = 0;
    char line[BUF_SIZE]; // Buffer for reading lines
    int c;
    while (fgets(line, BUF_SIZE, file)) { count++; }
    /*while ((c = fgetc(file)) != EOF) if (c == '\n') { count++; }
    count++;*/
    
    return count;
}

int main (int argc, char *argv[]){
    FILE* file;
    
    while(*++argv){
        file = fopen(*argv, "r");
        if (file) { printf("nombre de ligne est: %d\n", compteLignes(file)); }
        else {
            perror("Failed to open file \n");
            continue;
        }
        fclose(file);
    }
    return 0;
}