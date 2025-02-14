#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pgcd.h"
#define RESULT_FILE "result.txt"
#define REF_FILE_A "txt/ref_A.txt"
#define REF_FILE_B "txt/ref_B.txt"
#define RESULT_FILE_C "txt/res_C.txt"
#define NB_VALUES 65535

int pgcd_result(int a, int b, FILE *file){

    int result_diff = pgcd_diff(a, b);
    int result_euclide = pgcd_euclide(a, b);   
    int result_liste_diviseur = pgcd_liste_diviseur(a, b);              

    if(result_diff == result_euclide && result_euclide == result_liste_diviseur && result_diff != -1){
        fprintf(file, "Test_0 : le PGCD de %d et de %d est %d\n", a, b, result_diff);
        fprintf(file, "Test_1 : le PGCD de %d et de %d est %d\n", a, b, result_euclide);
        fprintf(file, "Test_2 : le PGCD de %d et de %d est %d\n", a, b, result_liste_diviseur);
        fprintf(file, "Résultat : TRUE\n\n");
        return 1;
    }
    else{
        fprintf(file, "Test_0 : le PGCD de %d et de %d est %d\n", a, b, result_diff);
        fprintf(file, "Test_1 : le PGCD de %d et de %d est %d\n", a, b, result_euclide);
        fprintf(file, "Test_2 : le PGCD de %d et de %d est %d\n", a, b, result_liste_diviseur);
        fprintf(file, "Résultat : FALSE\n\n");
        return 0;
    }
}

int rand_A(){
    return rand()%(65535+1);
}

int rand_B(){
    return rand()%(65535+1);
}

int pgcd_result_c(const char *file_a, const char *file_b, const char *file_c){
    
    int a, b, error = 0, success = 0;

    FILE *fa = fopen(file_a, "r");
    FILE *fb = fopen(file_b, "r");
    FILE *fc = fopen(file_c, "w");

    if (!fa || !fb || !fc) {
        printf("Erreur d'ouverture de fichier\n");
        return -1;
    }

    for (int i = 0; i < NB_VALUES; i++) {
        if (fscanf(fa, "%d", &a) != 1 || fscanf(fb, "%d", &b) != 1) {
            printf("Erreur de lecture ligne %d\n", i + 2);
            error++;
            continue;
        }

        int result_diff = pgcd_diff(a, b);
        int result_euclide = pgcd_euclide(a, b);   
        int result_liste_diviseur = pgcd_liste_diviseur(a, b);              

        if (result_diff == result_euclide && result_euclide == result_liste_diviseur && result_diff != -1) {
            fprintf(fc, "%d\n", result_diff);
            success++;
        } else {
            error++;
        }
    }

    fclose(fa);
    fclose(fb);
    fclose(fc);
    
    printf("Succès : %d, Erreurs : %d\n", success, error);
    return success;
}


int main(int argc, char const *argv[])
{   
    srand(time(NULL));

    const char *filename = RESULT_FILE;
    remove(filename);
    FILE *file = fopen(filename, "w");

    int count_error = 0;
    int count_success = 0;
    for(int i = 0; i < 65355; i++){
        int a = rand_A();
        int b = rand_B();
        int result = pgcd_result(a, b, file);
        if (result == 0)
        {
            count_error++;
        }
        else{
            count_success++;
        }    
    }

    fprintf(file, "Nombre d'erreurs : %d\n", count_error);
    fprintf(file, "Nombre de succès : %d\n", count_success);

    fclose(file);

    const char *filename_a = REF_FILE_A;
    const char *filename_b = REF_FILE_B;
    const char *filename_c = RESULT_FILE_C;
    pgcd_result_c(filename_a, filename_b, filename_c);
    int ret = system("diff -w txt/res_C.txt txt/ref_C.txt > txt/compare.txt");

    if (ret == 0) {
        printf("Les fichiers sont identiques.\n");
    } else if (ret == 256) { 
        printf("Les fichiers sont différents.\n");
    } else {
        printf("Une erreur s'est produite.\n");
    }    
    return 0;
}
