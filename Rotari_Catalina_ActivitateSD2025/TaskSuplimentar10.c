//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//} Masina;
//
//typedef struct Nod {
//	Masina info;
//	struct Nod* st;
//	struct Nod* dr;
//} Nod;
//
//Masina citireMasinaDinFisier(FILE* f) {
//	char buffer[100];
//	char sep[] = ",\n";
//	fgets(buffer, 100, f);
//	Masina m;
//	char* token = strtok(buffer, sep);
//	m.id = atoi(token);
//	m.nrUsi = atoi(strtok(NULL, sep));
//	m.pret = atof(strtok(NULL, sep));
//
//	token = strtok(NULL, sep);
//	m.model = (char*)malloc(strlen(token) + 1);
//	strcpy(m.model, token);
//
//	token = strtok(NULL, sep);
//	m.numeSofer = (char*)malloc(strlen(token) + 1);
//	strcpy(m.numeSofer, token);
//
//	m.serie = *strtok(NULL, sep);
//	return m;
//}
//
//void afisareMasina(Masina m) {
//	printf("ID: %d, Nr usi: %d, Pret: %.2f, Model: %s, Sofer: %s, Serie: %c\n",
//		m.id, m.nrUsi, m.pret, m.model, m.numeSofer, m.serie);
//}
//
//void adaugaMasina(Nod** rad, Masina m) {
//	if (*rad == NULL) {
//		*rad = (Nod*)malloc(sizeof(Nod));
//		(*rad)->info = m;
//		(*rad)->st = (*rad)->dr = NULL;
//	}
//	else if (m.id < (*rad)->info.id)
//		adaugaMasina(&((*rad)->st), m);
//	else if (m.id > (*rad)->info.id)
//		adaugaMasina(&((*rad)->dr), m);
//}
//
//Nod* citireArbore(const char* fisier) {
//	FILE* f = fopen(fisier, "r");
//	Nod* rad = NULL;
//	while (!feof(f)) {
//		Masina m = citireMasinaDinFisier(f);
//		adaugaMasina(&rad, m);
//	}
//	fclose(f);
//	return rad;
//}
//
//void afisareInordine(Nod* rad) {
//	if (rad) {
//		afisareInordine(rad->st);
//		afisareMasina(rad->info);
//		afisareInordine(rad->dr);
//	}
//}
//
//void dezalocareArbore(Nod** rad) {
//	if (*rad) {
//		dezalocareArbore(&(*rad)->st);
//		dezalocareArbore(&(*rad)->dr);
//		free((*rad)->info.model);
//		free((*rad)->info.numeSofer);
//		free(*rad);
//		*rad = NULL;
//	}
//}
//
//
//int calculeazaInaltime(Nod* rad) {
//	if (rad == NULL)
//		return 0;
//	int hSt = calculeazaInaltime(rad->st);
//	int hDr = calculeazaInaltime(rad->dr);
//	return 1 + (hSt > hDr ? hSt : hDr);
//}
//
//int determinaNumarNoduri(Nod* rad) {
//	if (rad == NULL) return 0;
//	return 1 + determinaNumarNoduri(rad->st) + determinaNumarNoduri(rad->dr);
//}
//
//Nod* subarboreMaiInalt(Nod* rad) {
//	if (rad == NULL) return NULL;
//	int hSt = calculeazaInaltime(rad->st);
//	int hDr = calculeazaInaltime(rad->dr);
//	return (hSt > hDr) ? rad->st : rad->dr;
//}
//
//int nrNoduriSubordine(Nod* rad) {
//	if (rad == NULL) return 0;
//	return determinaNumarNoduri(rad->st) + determinaNumarNoduri(rad->dr);
//}
//
//Nod* subarboreCuMaiMulteNoduri(Nod* rad) {
//	if (rad == NULL) return NULL;
//	int nrSt = determinaNumarNoduri(rad->st);
//	int nrDr = determinaNumarNoduri(rad->dr);
//	return (nrSt > nrDr) ? rad->st : rad->dr;
//}
//
//Nod* gasesteMinim(Nod* rad) {
//	while (rad && rad->st)
//		rad = rad->st;
//	return rad;
//}
//
//Nod* stergeNod(Nod* rad, int id) {
//	if (rad == NULL) return NULL;
//	if (id < rad->info.id)
//		rad->st = stergeNod(rad->st, id);
//	else if (id > rad->info.id)
//		rad->dr = stergeNod(rad->dr, id);
//	else {
//		// caz 1: frunza
//		if (rad->st == NULL && rad->dr == NULL) {
//			free(rad->info.model);
//			free(rad->info.numeSofer);
//			free(rad);
//			return NULL;
//		}
//		// caz 2: un singur copil
//		if (rad->st == NULL) {
//			Nod* tmp = rad->dr;
//			free(rad->info.model);
//			free(rad->info.numeSofer);
//			free(rad);
//			return tmp;
//		}
//		if (rad->dr == NULL) {
//			Nod* tmp = rad->st;
//			free(rad->info.model);
//			free(rad->info.numeSofer);
//			free(rad);
//			return tmp;
//		}
//		// caz 3: doi copii
//		Nod* succ = gasesteMinim(rad->dr);
//		free(rad->info.model);
//		free(rad->info.numeSofer);
//		rad->info = succ->info;
//		rad->dr = stergeNod(rad->dr, succ->info.id);
//	}
//	return rad;
//}
//
//
//int main() {
//	Nod* arbore = citireArbore("masini.txt");
//
//	printf("Afisare inordine:\n");
//	afisareInordine(arbore);
//
//	printf("\nInaltime arbore: %d\n", calculeazaInaltime(arbore));
//
//	printf("Subarborele cu inaltime mai mare are radacina cu ID-ul: %d\n",
//		subarboreMaiInalt(arbore)->info.id);
//
//	printf("Numar noduri in subordine: %d\n", nrNoduriSubordine(arbore));
//
//	printf("Subarborele cu mai multe noduri are radacina cu ID-ul: %d\n",
//		subarboreCuMaiMulteNoduri(arbore)->info.id);
//
//	printf("\nStergem nodul cu ID-ul 5:\n");
//	arbore = stergeNod(arbore, 5);
//	afisareInordine(arbore);
//
//	dezalocareArbore(&arbore);
//	return 0;
//}
