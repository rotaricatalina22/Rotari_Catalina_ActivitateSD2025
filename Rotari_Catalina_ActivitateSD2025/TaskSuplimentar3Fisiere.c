//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//// Structura Masina
//struct StructuraMasina {
//    int id;
//    int nrUsi;
//    float pret;
//    char* model;
//    char* numeSofer;
//    unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//// Funcția de afisare a unei masini
//void afisareMasina(Masina masina) {
//    printf("Id: %d\nnrUsi: %d\npret: %.2f\nmodel: %s\nnumeSofer: %s\nserie: %c\n\n",
//        masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
//}
//
//// Funcția de afisare a unui vector de masini
//void afisareVectorMasini(Masina* masini, int nrMasini) {
//    for (int i = 0; i < nrMasini; i++) {
//        afisareMasina(masini[i]);
//    }
//}
//
//// Funcția de adăugare a unei noi mașini în vector
//void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
//    Masina* vector = malloc(sizeof(Masina) * ((*nrMasini) + 1));
//    for (int i = 0; i < (*nrMasini); i++) {
//        vector[i] = (*masini)[i];
//    }
//    vector[(*nrMasini)] = masinaNoua;
//    vector[(*nrMasini)].model = malloc(sizeof(char) * (strlen(masinaNoua.model) + 1));
//    strcpy_s(vector[(*nrMasini)].model, strlen(masinaNoua.model) + 1, masinaNoua.model);
//    vector[(*nrMasini)].numeSofer = malloc(sizeof(char) * (strlen(masinaNoua.numeSofer) + 1));
//    strcpy_s(vector[(*nrMasini)].numeSofer, strlen(masinaNoua.numeSofer) + 1, masinaNoua.numeSofer);
//
//    free(*masini);
//    (*masini) = vector;
//    (*nrMasini)++;
//}
//
//// Funcția de citire a unei masini din fisier
//Masina citireMasinaFisier(FILE* file) {
//    Masina masina;
//    char buffer[100];
//    fgets(buffer, 100, file);
//    char* token = strtok(buffer, ",\n");
//
//    masina.id = atoi(token);
//    masina.nrUsi = atoi(strtok(NULL, ",\n"));
//    masina.pret = atof(strtok(NULL, ",\n"));
//
//    char* model = strtok(NULL, ",\n");
//    masina.model = malloc(sizeof(char) * (strlen(model) + 1));
//    strcpy_s(masina.model, strlen(model) + 1, model);
//
//    char* numeSofer = strtok(NULL, ",\n");
//    masina.numeSofer = malloc(sizeof(char) * (strlen(numeSofer) + 1));
//    strcpy_s(masina.numeSofer, strlen(numeSofer) + 1, numeSofer);
//
//    masina.serie = strtok(NULL, ",\n")[0];
//
//    return masina;
//}
//
//// Funcția de citire a unui vector de masini dintr-un fisier
//Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
//    FILE* f = fopen(numeFisier, "r");
//    Masina* masini = NULL;
//
//    while (!feof(f)) {
//        Masina m = citireMasinaFisier(f);
//        adaugaMasinaInVector(&masini, nrMasiniCitite, m);
//        free(m.model);
//        free(m.numeSofer);
//    }
//    fclose(f);
//    return masini;
//}
//
//// Funcția de salvare a unei masini într-un fisier text
//void salvareMasinaFisier(FILE* file, Masina masina) {
//    fprintf(file, "%d,%d,%.2f,%s,%s,%c\n", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
//}
//
//// Funcția de salvare a unui vector de masini într-un fisier text
//void salvareVectorMasiniFisier(const char* numeFisier, Masina* masini, int nrMasini) {
//    FILE* file = fopen(numeFisier, "masini.txt");
//    if (file == NULL) {
//        printf("Nu s-a putut deschide fisierul pentru salvare.\n");
//        return;
//    }
//
//    for (int i = 0; i < nrMasini; i++) {
//        salvareMasinaFisier(file, masini[i]);
//    }
//
//    fclose(file);
//}
//
//// Funcția de dezalocare a vectorului de masini
//void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
//    for (int i = 0; i < *nrMasini; i++) {
//        free((*vector)[i].model);
//        free((*vector)[i].numeSofer);
//    }
//    free(*vector);
//    *vector = NULL;
//    *nrMasini = 0;
//}
//
//int main() {
//    // Citire din fisierul masini.txt
//    Masina* masini = NULL;
//    int nrMasini = 0;
//    masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
//
//    // Afisare masini
//    printf("Masini citite din fisier:\n");
//    afisareVectorMasini(masini, nrMasini);
//
//    // Salvare masini într-un alt fisier
//    printf("Salvarea masinilor in fisierul masini_salvate.txt...\n");
//    salvareVectorMasiniFisier("masini_salvate.txt", masini, nrMasini);
//
//    // Dezalocarea memoriei
//    dezalocareVectorMasini(&masini, &nrMasini);
//
//    return 0;
//}
