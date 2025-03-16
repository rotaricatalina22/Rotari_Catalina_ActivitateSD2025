#include<stdio.h>
#include<stdlib.h>

struct Telefon {
	int id;
	int ram;
	char* producator; //sir de caractere
	float pret;
	char serie;//un singur caracter
};

//initializare articol Telefon
struct Telefon initializare(int id, int ram, const char* producator, float pret, char serie) {
	struct Telefon t;
	t.id = id;
	t.ram = ram;
	t.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(t.producator, strlen(producator) + 1, producator);
	t.pret = pret;
	t.serie = serie;
	//initializare structura
	return t;
}

void afisare(struct Telefon t) {
	//afisarea tuturor atributelor
}

void modificare_Atribut(struct Telefon t) {
	//modificarea unui atribut
}

void dezalocare(struct Telefon* t) {
	//dezalocarea campurilor alocate dinamic
}

int main() {
	struct Telefon t;
	t = initializare(1, 256, "Samsung", 2000, 5, 'A');
	return 0;
}