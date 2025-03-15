



#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

void afisareMasina(Masina masina) {
	//afiseaza toate atributele unei masini
	printf("Id: %d\nnrUsi: %d\npret: %0.2f\nmodel: %s\nnumeSofer: %s\nserie: %c", masina.id, masina.nrUsi, masina.pret, masina.model, masina.numeSofer, masina.serie);
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	Masina* vector = malloc(sizeof(Masina) * ((*nrMasini) + 1));

	for (int i = 0; i < (*nrMasini); i++) {
		vector[i] = (*masini)[i];
	}
	vector[(*nrMasini)] = masinaNoua;
	vector[(*nrMasini)].model = malloc(sizeof(char) * (strlen(masinaNoua.model) + 1));
	strcpy_s(vector[(*nrMasini)].model, (strlen(masinaNoua.model) + 1), masinaNoua.model);
	vector[(*nrMasini)].numeSofer = malloc(sizeof(char) * (strlen(masinaNoua.numeSofer) + 1));
	strcpy_s(vector[(*nrMasini)].numeSofer, (strlen(masinaNoua.numeSofer) + 1), masinaNoua.numeSofer);

	free(*masini);
	(*masini) = vector;
	(*nrMasini)++;

}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
	Masina masina;
	char buffer[100];
	fgets(buffer, 100, file);
	char separator[] = ",\n";

	char* token = strtok(buffer, separator);
	masina.id = atoi(token);

	char* token2 = strtok(NULL, separator);
	masina.nrUsi = atoi(token2);

	char* token3 = strtok(NULL, separator);
	masina.pret = atof(token3);

	char* token4 = strtok(NULL, separator);
	masina.model = malloc(sizeof(char) * (strlen(token4) + 1));
	strcpy_s(masina.model, strlen(token4) + 1, token4);

	char* token5 = strtok(NULL, separator);
	masina.numeSofer = malloc(sizeof(char) * (strlen(token5) + 1));
	strcpy_s(masina.numeSofer, strlen(token5) + 1, token5);

	char* token6 = strtok(NULL, separator);
	masina.serie = token6[0];

	return masina;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	FILE* f = fopen(numeFisier, "r");
	Masina* masini = NULL;
	while (!feof(f)) {
		//prin apelul repetat al functiei citireMasinaFisier()
		Masina m = citireMasinaFisier(f);
		//numarul de masini este determinat prin numarul de citiri din fisier
		adaugaMasinaInVector(&masini, nrMasiniCitite, m);
		free(m.model);
		free(m.numeSofer);
	}
	fclose(f);
	return masini;

	//ATENTIE - la final inchidem fisierul/stream-ul

}

//temaaaaaaaaaaaaaaaaaaaaaaaaaaaa

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0; i < *nrMasini; i++) {
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}
	free(*vector);
	*vector = NULL;
	*nrMasini = 0;

}

int main() {
	Masina* masini = NULL;
	int nrMasini = 0;
	masini = citireVectorMasiniFisier("masini.txt", &nrMasini);
	afisareVectorMasini(masini, nrMasini);
	return 0;
}

