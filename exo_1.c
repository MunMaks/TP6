#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
    int count = 0;
    printf("Le nombre d’arguments qui lui a été fourni: %d\n", argc);

    while (*++argv){
        if (*(argv)[0] == '-' && strlen(*argv) > 1) { ++count; }
        else {
            FILE *fptr = fopen(*argv, "r");
            if (fptr != NULL) {
                printf("Fichier %s peut-être lu.\n", *argv);
                fclose(fptr);
            } else { printf("Fichier %s ne peut pas être lu.\n", *argv); }
        }
    }
    printf("Le nombre d’arguments commençant par le caractère '-' : %d\n", count);
    return 0;
}