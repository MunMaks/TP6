#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024  // pow(2, 10)

int compteMots(FILE * file){
    int count = 0;
    char word[MAX_SIZE];
    
    while (fscanf(file, " %255s ", word) == 1){ ++count; }
    return count;
}

int main (int argc, char *argv[]){
    FILE* file;
    while(*++argv){
        file = fopen(*argv, "r");
        if (file) { printf("nombre de mots est: %d\n", compteMots(file)); }
        else {
            perror("Failed to open file \n");
            continue;
        }
        fclose(file);
    }
    return 0;
}