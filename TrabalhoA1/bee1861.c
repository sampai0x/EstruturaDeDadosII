//Cauã Pirateli Bertin - RA: 114600. BEEID: 804067
//Claudevan Moreira da Costa Junior - RA: 115478. BEEID: 804018
//Emerson Osvaldo Menegatti Junior - RA: 112301. BEEID: 872881
//Pedro Henrique Pereira Pinto - RA: 115879. BEEID: 821863 
//Pedro Lucas Sampaio - RA: 115919. BEEID: 813025

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tipoDado{
	char nome[20];
	int qtsMortes;
} Assassinos;

struct ArvHall{
	Assassinos dado;
	struct ArvHall *esquerdo;
	struct ArvHall *direito;
};

struct ArvMortos{
	char morto[20];
	struct ArvMortos *esquerdo;
	struct ArvMortos *direito;
};

typedef struct ArvHall Hall;
typedef struct ArvMortos Mortos;

Hall* insereAssassinos(Hall *, Assassinos);
Mortos* insereMortos(Mortos *, char *);
int busca(Mortos *mortos, char *chave);
int show(Hall *, Mortos *);

int main (){
	char matou[20], morreu[20];
	Hall *hall = NULL;
	Mortos *mortos = NULL;

	while (scanf(" %s %s", matou, morreu) != EOF){
		Assassinos assassino = { 0 };
		strcpy(assassino.nome, matou);
		hall = insereAssassinos(hall, assassino);
		
		mortos = insereMortos(mortos, morreu);
	}

	printf("HALL OF MURDERERS\n");
	show(hall, mortos);

}

Hall* insereAssassinos(Hall *hall, Assassinos assassino){
	if (!hall){
		hall = (Hall *) malloc(sizeof(Hall));
		hall->dado = assassino;
		hall->dado.qtsMortes++;
		hall->esquerdo = hall->direito = NULL;
	}
	else if (strcmp(hall->dado.nome, assassino.nome) > 0)
		hall->esquerdo = insereAssassinos(hall->esquerdo, assassino);
	else if (strcmp(hall->dado.nome, assassino.nome) < 0)
		hall->direito = insereAssassinos(hall->direito, assassino);
	else
		hall->dado.qtsMortes++;

	return hall;
}

Mortos* insereMortos(Mortos *mortos, char *morto){
	if (!mortos){
		mortos = (Mortos *) malloc(sizeof(Mortos));
		strcpy(mortos->morto, morto);
		mortos->esquerdo = mortos->direito = NULL;

	}
	else if (strcmp(mortos->morto, morto) > 0)
		mortos->esquerdo = insereMortos(mortos->esquerdo, morto);
	else
		mortos->direito = insereMortos(mortos->direito, morto);

	return mortos;
}

int show(Hall *hall, Mortos *mortos){
	if (hall != NULL){
		show(hall->esquerdo, mortos);
		if (!busca(mortos, hall->dado.nome))
			printf("%s %u\n", hall->dado.nome, hall->dado.qtsMortes);
		show(hall->direito, mortos);
	}

}

int busca(Mortos *mortos, char *chave){
	int direita, esquerda;
	if (!mortos)
		return 0;
	if (strcmp(mortos->morto, chave) == 0)
		return 1;
	if (strcmp(mortos->morto, chave) > 0)
		esquerda = busca(mortos->esquerdo, chave);
	else
		direita = busca(mortos->direito, chave);

}