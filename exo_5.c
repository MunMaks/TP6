#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024  // pow(2, 10)


int compteLignes(FILE * file);

int compteMots(FILE * file);

int compteCaracteres(FILE * fichier);

void countStats(FILE *file, int *charCount, int *wordCount, int *lineCount);

int my_wc(FILE * file);


int main (int argc, char *argv[]){
    FILE* file;
    int displayCharCount = 0;
    int displayWordCount = 0;
    int displayLineCount = 0;
    int displayVersion = 0;

    int charCount = 0;
    int wordCount = 0;
    int lineCount = 0;
    
    char *mode = *++argv;

    for (int i = 1; *(mode + i) != '\0'; ++i){
        if (*mode == '-' && strlen(mode) > 1){
            if (*(mode + i) == 'l') { displayLineCount = 1; }
            else if (*(mode + i) == 'm') { displayWordCount = 1; }
            else if (*(mode + i) == 'c') { displayCharCount = 1; }
            else if (*(mode + i) == 'v') { displayVersion = 1; }
        }
    }
    if (!displayCharCount && !displayWordCount && !displayLineCount){
        displayCharCount = 1; displayWordCount = 1; displayLineCount = 1;
    }

    while (*++argv){
        file = fopen(*argv, "r");
        if (file == NULL) { printf("Fichier %s ne peut pas être lu.\n", *argv); }
        else {
            // printf("Fichier %s peut-être lu.\n", *argv);
            countStats (file, &charCount, &wordCount, &lineCount);

            if (displayCharCount) { printf("nombre de caracteres est: %d\n", charCount); }
            if (displayWordCount) { printf("nombre de mots est: %d\n", wordCount); }
            if (displayLineCount) { printf("nombre de lignes est: %d\n\n", lineCount); }
            fclose(file);
        }
    }
    printf("%d, %d, %d, %d\n", displayLineCount, displayWordCount, displayCharCount, displayVersion);
    return 0;
}

int compteLignes(FILE * file){
    int count = 0;
    char line[MAX_SIZE]; // Buffer for reading lines
    int c;
    while (fgets(line, MAX_SIZE, file)) { count++; }
    /*while ((c = fgetc(file)) != EOF) if (c == '\n') { count++; }
    count++;*/
    
    return count;
}

int compteMots(FILE * file){
    int count = 0;
    char word[MAX_SIZE];
    
    while (fscanf(file, " %255s ", word) == 1){ ++count; }
    return count;
}

int compteCaracteres(FILE * fichier){
    int res = 0;
    char c;
    while ((c = fgetc(fichier)) != EOF) { ++res; }
    return res;
}

void countStats(FILE *file, int *charCount, int *wordCount, int *lineCount) {
    int ch;
    int inWord = 0;

    *charCount = 0; //compteCaracteres(file);
    *wordCount = 0; //compteMots(file);
    *lineCount = 0; //compteLignes(file);

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') { (*lineCount)++; }

        if (ch == ' ' || ch == '\t' || ch == '\n') { inWord = 0; }
        else if (!inWord) {
            inWord = 1;
            (*wordCount)++; }
        (*charCount)++;
    }
    (*lineCount)++;
}
