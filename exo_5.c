#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 1024  // pow(2, 10)

int len_word(char *word);

int compteLignes(FILE * file);

int compteMots(FILE * file);

int compteCaracteres(FILE * file);

void compteTout(FILE *file, int *caracteres, int *mots, int *lignes);

void affiche_options(char *mode, int *affiche_char, int *affiche_mots, int *affiche_lignes, int *affiche_version);

void affiche_synopsis(int affiche_char, int affiche_mots, int affiche_lignes, int affiche_version, int caracteres, int mots, int lignes);

// int my_wc(FILE * file);

void usage(char *nom);

int main (int argc, char *argv[]){
    FILE* file;
    int affiche_char = 0;
    int affiche_mots = 0;
    int affiche_lignes = 0;
    int affiche_version = 0;

    int caracteres = 0;
    int mots = 0;
    int lignes = 0;
    char *mode = *(argv + 1);

    // Si on a mis quelque chose après caractère '-'
    affiche_options(mode, &affiche_char, &affiche_mots, &affiche_lignes, &affiche_version);  // gestion des options
        
    // On parcours tous les fichiers
    while (*++argv){
        if ((*argv)[0] == '-') continue;  // pour éviter l'ouverture des options comme fichier
        file = fopen(*argv, "r");

        if (!file) { printf("Fichier %s ne peut pas être lu.\n\n", *argv); continue;}
        else {
            // printf("Fichier %s peut-être lu.\n", *argv);
            
            compteTout (file, &caracteres, &mots, &lignes);  // Ici on compte tout: lignes, mots, caractères
            
            affiche_synopsis(affiche_char, affiche_mots, affiche_lignes, affiche_version, caracteres, mots, lignes); // On les affiche

            fclose(file);  // la férmeture du fichier
        }
    }
    return 0;
}


int len_word(char *word){  // la longueur du mot
    int i = 0;
    while (*(word + i)){ ++i; } return i;
}

int compteLignes(FILE * file){
    int count = 0;
    char line[MAX_SIZE]; // Buffer for reading lines

    while (fgets(line, MAX_SIZE, file)) { count++; }
    /*while ((c = fgetc(file)) != EOF) if (c == '\n') { count++; } count++;*/
    return count;
}

int compteMots(FILE * file){
    int count = 0;
    char word[MAX_SIZE];
    while (fscanf(file, " %255s ", word) == 1){ ++count; }
    return count;
}

int compteCaracteres(FILE * file){
    int res = 0;
    char c;
    while ((c = fgetc(file)) != EOF) { ++res; }
    return res;
}

void compteTout(FILE *file, int *caracteres, int *mots, int *lignes) {
    int ch;

    *caracteres = 0;  //compteCaracteres(file);
    *mots = 0;        //compteMots(file);
    *lignes = 0;      //compteLignes(file);

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') { (*lignes)++; }

        if (ch == ' ' || ch == '\t' || ch == '\n') { (*mots)++; }

        (*caracteres)++;
    }

    (*mots)++;
    (*lignes)++;
}

void affiche_options(char *mode, int *affiche_char, int *affiche_mots, int *affiche_lignes, int *affiche_version){
    if (*mode == '-' && strlen(mode) > 1){
        for (int i = 1; i < len_word(mode); ++i){
            if (*(mode + i) == 'l') { *affiche_lignes = 1; }
            else if (*(mode + i) == 'm') { *affiche_mots = 1; }
            else if (*(mode + i) == 'c') { *affiche_char = 1; }
            else if (*(mode + i) == 'v') { *affiche_version = 1; }
            else { usage(mode); }
        }
    } else
        *affiche_lignes = *affiche_mots = *affiche_version = 1; //*affiche_char = 1;
}

void affiche_synopsis(int affiche_char, int affiche_mots, int affiche_lignes, int affiche_version, int caracteres, int mots, int lignes){
    if (affiche_char) { printf("nombre de caracteres est: %d\n", caracteres); }
    if (affiche_mots) { printf("nombre de mots est: %d\n", mots); }
    if (affiche_lignes) { printf("nombre de lignes est: %d\n\n", lignes); }
    if (affiche_version) { printf("C’est ma version du programme word count.\n"); }
}

void usage(char *nom){
    printf("USAGE : my_wc [-mlvc] [fichier1] [fichier2] [...]\n");
    printf("\tErreur : une option invalide est fournie: %s\n", nom);
    printf("\tAprès '-' vous ne devez utiliser que ces 4 lettres: 'l', 'm', 'c', 'v'.\n");
}