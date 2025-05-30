#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structura pentru un pacient
struct Pacient {
	int id;
	char* nume;
	int varsta;
	int gradUrgenta; //cu cât e mai mare, cu atât e mai urgent
};
typedef struct Pacient Pacient;

//structura pentru Heap
struct Heap {
	int lungime;
	int nrElemente;
	Pacient* vector;
};
typedef struct Heap Heap;

Pacient citirePacientDinFisier(FILE* f) {
	char buffer[100];
	char sep[] = ",\n";
	Pacient p;

	fgets(buffer, 100, f);
	char* token = strtok(buffer, sep);
	p.id = atoi(token);

	token = strtok(NULL, sep);
	p.nume = malloc(strlen(token) + 1);
	strcpy_s(p.nume, strlen(token) + 1, token);

	p.varsta = atoi(strtok(NULL, sep));
	p.gradUrgenta = atoi(strtok(NULL, sep));

	return p;
}

void afisarePacient(Pacient p) {
	printf("Id: %d\n", p.id);
	printf("Nume: %s\n", p.nume);
	printf("Varsta: %d\n", p.varsta);
	printf("Grad urgenta: %d\n\n", p.gradUrgenta);
}

Heap initializareHeap(int dim) {
	Heap h;
	h.lungime = dim;
	h.nrElemente = 0;
	h.vector = (Pacient*)malloc(sizeof(Pacient) * dim);
	return h;
}

void filtreazaHeap(Heap h, int poz) {
	int st = 2 * poz + 1;
	int dr = 2 * poz + 2;
	int max = poz;

	if (st < h.nrElemente && h.vector[st].gradUrgenta > h.vector[max].gradUrgenta)
		max = st;
	if (dr < h.nrElemente && h.vector[dr].gradUrgenta > h.vector[max].gradUrgenta)
		max = dr;

	if (max != poz) {
		Pacient aux = h.vector[max];
		h.vector[max] = h.vector[poz];
		h.vector[poz] = aux;
		if (max <= (h.nrElemente - 2) / 2)
			filtreazaHeap(h, max);
	}
}

Heap citireHeapPacienti(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	Heap h = initializareHeap(20);
	while (!feof(f)) {
		Pacient p = citirePacientDinFisier(f);
		if (p.id != 0)
			h.vector[h.nrElemente++] = p;
	}
	fclose(f);

	for (int i = (h.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(h, i);
	}
	return h;
}

void afisareHeap(Heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		afisarePacient(h.vector[i]);
	}
}

Pacient extragePacient(Heap* h) {
	if (h->nrElemente > 0) {
		Pacient p = h->vector[0];
		h->vector[0] = h->vector[h->nrElemente - 1];
		h->vector[h->nrElemente - 1] = p;
		h->nrElemente--;

		for (int i = (h->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*h, i);
		}
		return p;
	}
}

void dezalocareHeap(Heap* h) {
	for (int i = 0; i < h->lungime; i++) {
		if (h->vector[i].nume != NULL) {
			free(h->vector[i].nume);
		}
	}
	free(h->vector);
	h->vector = NULL;
	h->lungime = 0;
	h->nrElemente = 0;
}

int main() {
	Heap heap = citireHeapPacienti("pacienti.txt");

	printf("Afisare pacienti in heap:\n");
	afisareHeap(heap);

	printf("Extragem pacientii in ordinea gravitatii:\n");
	while (heap.nrElemente > 0) {
		Pacient p = extragePacient(&heap);
		afisarePacient(p);
	}

	dezalocareHeap(&heap);
	return 0;
}
