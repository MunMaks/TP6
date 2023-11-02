#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compteCaracteres(FILE * fichier){
    int res = 0;
    char c;
    while ((c = fgetc(fichier)) != EOF) { ++res; }
    return res;
}

int main (int argc, char *argv[]){
    FILE* fptr;
    
    while(*++argv){
        fptr = fopen(*argv, "r");
        if (fptr) { printf("nombre d'elments est: %d\n", compteCaracteres(fptr)); }
        else {
            printf("Failed to open file, %s\n", *argv);
            continue;
        }
        fclose(fptr);
    }
    return 0;
}