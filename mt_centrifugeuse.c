/*

Module : mt_centrifugeuse
Par    : PILOQUET Olivier (PILO13029704), ROGET Benjamin (ROGB09029601)
Date   : 21/06/2018

 */
/*=========================================================*/


/*=========================================================*/
//qui permet de désactiver certains warnings du compilateur 
#define _CRT_SECURE_NO_WARNINGS 
/*=========================================================*/
// Librairies usuelles à inclure 
/*=========================================================*/ 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>
//
#include "mt_centrifugeuse.h"
#include "mtwister.h"

/*=========================================================*/
/* LES CONSTANTES */
/*=========================================================*/
// si vous en avez, voici un bon endroit pour les introduire 



/*=========================================================*/




/*=========================================================*/
/*=========================================================*/
// avec le 1 du #if, ce main est actuellement actif
#if 0
int main(void) {

	//test_init_centrifugeuse();
	//test_print_centrifugeuse();
	//test_tock_centrifugeuse();
	//test_get_compteurs();
	//test_accroitre_prob();

	t_centrifugeuse centri = init_centrifugeuse();
	t_centrifugeuse *ptr = &centri;
	uint temps_rep = 2;
	int temps_en_attente = 2;
	int temps_en_arret = 2;
	//print_centrifugeuse(ptr);
	int succes;

	while (centri.tocks_total < 10000) {
		(*ptr).etat = tock_centrifugeuse(ptr);

		if ((*ptr).etat == EN_ARRET){
			if ((*ptr).compteur_tocks[1] % temps_en_arret == 9) {
				succes = set_en_attente(ptr);
				assert(succes);
			}
		}

		if ((*ptr).etat == EN_ATTENTE) {
			if ((*ptr).compteur_tocks[2] % temps_en_arret == 9) {
				succes = set_en_fonction(ptr);
				assert(succes);
			}
		}

		if ((*ptr).etat == 0 && (*ptr).temps_reparation == ~0) {
			set_temps_reparation(ptr, temps_rep);
		}

	}
	print_centrifugeuse(ptr);

	// on termine avec le standard... HIT ANY KEY	
	system("pause");
	// et ÇA, c'est un 0 avec une cravate...
	return EXIT_SUCCESS;
}
#endif
/*=========================================================*/

void	  print_centrifugeuse(const t_centrifugeuse * ptr) {
	printf("Centrifugeuse \n");
	printf("etat : %d\n", (*ptr).etat);
	printf("tocks en bris : %d\n", (*ptr).compteur_tocks[0]);
	printf("tocks en arret : %d\n", (*ptr).compteur_tocks[1]);
	printf("tocks en attente : %d\n", (*ptr).compteur_tocks[2]);
	printf("tocks en fonction : %d\n", (*ptr).compteur_tocks[3]);
	printf("nombre de bris : %d\n", (*ptr).nombre_bris);
	printf("probabilite de bris : %f\n", (*ptr).probabilite_bris);
	printf("tock en fonction depuis dernier bris : %d\n", (*ptr).tocks_apres_bris[0]);
	printf("tock en attente depuis dernier bris : %d\n", (*ptr).tocks_apres_bris[1]);
	printf("temps de reparation : %d\n", (*ptr).temps_reparation);
	printf("tocks total : %d\n", (*ptr).tocks_total);
}
void test_print_centrifugeuse(void) {
	t_centrifugeuse centri = {0,1,2,3,4,5,6,7,8,9};
	print_centrifugeuse(&centri);
}

t_centrifugeuse init_centrifugeuse(void) {
	t_centrifugeuse centrifugeuse = { 0 };
	centrifugeuse.etat = EN_ARRET;
	centrifugeuse.probabilite_bris = PROBABILITE_BRIS;
	return centrifugeuse;
}
void	   test_init_centrifugeuse(void) {
	t_centrifugeuse test_centri;
	t_centrifugeuse*ptr = &test_centri;

	test_centri = init_centrifugeuse();
	print_centrifugeuse(ptr);
}

int		  set_en_fonction(t_centrifugeuse * ptr) {
	// change l'etat de la machine en fonction si elle etait en attente
	if ((*ptr).etat == EN_ATTENTE) {
		(*ptr).etat = EN_FONCTION;
		return 1;
	}
	else {
		return 0;
	}
}
void test_set_en_fonction(void) {
	t_centrifugeuse test_centri = init_centrifugeuse();
	t_centrifugeuse*ptr = &test_centri;
	int succes;
	(*ptr).etat = EN_BRIS;

	succes = set_en_fonction(ptr);

	if (succes == 1) {
		printf("succes\n");
		printf("%d\n", (*ptr).etat);
	}
	else {
		printf("echec\n");
		printf("%d\n", (*ptr).etat);

	}
}

int		  set_en_attente(t_centrifugeuse * ptr) {
	// change l'etat de la machine en attente si elle etait en arret ou en fonction
	if ((*ptr).etat == EN_ARRET || (*ptr).etat == EN_FONCTION) {
		(*ptr).etat = EN_ATTENTE;
		return 1;
	}
	else {
		return 0;
	}
}
void test_set_en_attente(void) {
	t_centrifugeuse test_centri = init_centrifugeuse();
	t_centrifugeuse*ptr = &test_centri;
	int succes;
	(*ptr).etat = EN_ATTENTE;

	succes = set_en_attente(ptr);

	if (succes == 1) {
		printf("succes\n");
		printf("%d\n", (*ptr).etat);
	}
	else {
		printf("echec\n");
		printf("%d\n", (*ptr).etat);

	}
}

int		  set_en_arret(t_centrifugeuse * ptr) {
	// change l'etat de la machine en arret si elle etait en attente ou en fonction
	if ((*ptr).etat == EN_ATTENTE || (*ptr).etat == EN_FONCTION) {
		(*ptr).etat = EN_ARRET;
		return 1;
	}
	else {
		return 0;
	}
}
void test_set_en_arret(void) {
	t_centrifugeuse test_centri = init_centrifugeuse();
	t_centrifugeuse*ptr = &test_centri;
	int succes;
	(*ptr).etat = EN_ATTENTE;

	succes = set_en_arret(ptr);

	if (succes == 1) {
		printf("succes\n");
		printf("%d\n", (*ptr).etat);
	}
	else {
		printf("echec\n");
		printf("%d\n", (*ptr).etat);

	}
}

int		  tock_centrifugeuse(t_centrifugeuse * ptr) {
	// Decremente le temps de reparation si la machine est en bris et que son temps de reparation est defini
	if ((*ptr).etat == EN_BRIS){
		// incremente le compteur de tock en bris
		(*ptr).compteur_tocks[0] += 1;
		if ((*ptr).temps_reparation != ~0){
			(*ptr).temps_reparation -= 1;
		// Change l'etat de la machine en arret si le temps de reparation est termine
			if ((*ptr).temps_reparation == 0) {
				(*ptr).etat = EN_ARRET;
				(*ptr).probabilite_bris = PROBABILITE_BRIS;
			}
		}
	}
	// test si la machine brise quand la machine est en fonction ou en attente
	else if ((*ptr).etat == EN_ATTENTE || (*ptr).etat == EN_FONCTION) {
		// incremente le nombre de tock en fonction si la machine est en fonction
		if ((*ptr).etat == EN_FONCTION) (*ptr).compteur_tocks[3] += 1;
		// incremente le nombre de tock en attente si la machine est en attente
		if ((*ptr).etat == EN_ATTENTE) (*ptr).compteur_tocks[2] += 1;


		// initialisation du generateur de nombre aleatoire
		mt_srandSys();
		double bris = mt_rand();
		// S'il elle brise, son temps de reparation est infini et on incremente son nombre de bris
		if ((*ptr).probabilite_bris >= bris) {
			(*ptr).etat = EN_BRIS;
			// le temps de reparation passe a l'infini
			(*ptr).temps_reparation = ~0;
			(*ptr).nombre_bris += 1;
			//reinitialise le nombre de tock apres bris, en onction et en attente 
			(*ptr).tocks_apres_bris[0] = 0;
			(*ptr).tocks_apres_bris[1] = 0;
		}
		// sinon sa probabilite de bris augmente
		else {
			// incremente le nombre de tock en fonction apres bris si la machine est en fonction
			if ((*ptr).etat == EN_FONCTION) (*ptr).tocks_apres_bris[0] += 1;
			// incremente le nombre de tock en attente apres bris si la machine est en attente
			if ((*ptr).etat == EN_ATTENTE) (*ptr).tocks_apres_bris[1] += 1;
			accroitre_prob(ptr);
		}
	}
	else if ((*ptr).etat == EN_ARRET) {
		// incremente le nombre de tock en arret
		(*ptr).compteur_tocks[1] += 1;
	}
	//incremente le nombre de tock total de la machine
	(*ptr).tocks_total += 1;
	return (*ptr).etat;
}
void test_tock_centrifugeuse(void) {
	t_centrifugeuse centri = init_centrifugeuse();
	int *ptr = &centri;
#if 1
	centri.etat = EN_BRIS;
	centri.temps_reparation = 1;

	print_centrifugeuse(ptr);
	printf("\n\n");
	int verif_tock = tock_centrifugeuse(ptr);
	print_centrifugeuse(ptr);
#endif

#if 0
	centri.etat = EN_ATTENTE;
	centri.probabilite_bris = 0.9;

	print_centrifugeuse(ptr);
	int verif_tock;
	verif_tock = tock_centrifugeuse(ptr);
	printf("\n\n");
	print_centrifugeuse(ptr);
#endif 

#if 0
	centri.etat = EN_FONCTION;

	print_centrifugeuse(ptr);
	int verif_tock;
	verif_tock = tock_centrifugeuse(ptr);
	printf("\n\n");
	print_centrifugeuse(ptr);

#endif 

#if 0
	centri.etat = EN_ARRET;

	print_centrifugeuse(ptr);
	int verif_tock = tock_centrifugeuse(ptr);
	printf("\n\n");
	print_centrifugeuse(ptr);
#endif

}

int		  set_temps_reparation(t_centrifugeuse * ptr, uint temps) {
	// Defini le temps de reparation si la machine est en bris
	if ((*ptr).etat == EN_BRIS && (*ptr).temps_reparation == ~0) {
		(*ptr).temps_reparation = temps;
		return 1;
	}
	else {
		return 0;
	}
}
void test_set_temps_reparation(void) {
	t_centrifugeuse test_centri = init_centrifugeuse();
	t_centrifugeuse*ptr = &test_centri;
	int succes;
	uint temps;

	temps = 10;
	(*ptr).etat = EN_BRIS;
	(*ptr).temps_reparation = 15;

	succes = set_temps_reparation(&test_centri, temps);

	if (succes == 1) {
		printf("succes\n");
		printf("%d\n", (*ptr).temps_reparation);
	}
	else {
		printf("echec\n");
		printf("%d\n", (*ptr).temps_reparation);

	}
}


void	  get_compteurs(const t_centrifugeuse * ptr, uint * tab) {
	// case 0 a 3 remplis le tableau avec les compteurs de tocks de chaque etat
	for (int i = 0; i < 4; i++) {
		tab[i] = (*ptr).compteur_tocks[i];
	}
	// case 4 : ajoute le nombre de bris d'une centrifugeuse au tableau
	tab[4] = (*ptr).nombre_bris;
	// remplis le tableau avec les compteurs de tocks après un bris
	// case 5 : en attente ; case 6 : en fonction
	tab[5] = (*ptr).tocks_apres_bris[0];
	tab[6] = (*ptr).tocks_apres_bris[1];
	// case 7 : ajoute le temps de reparation de la centrifugeuse au tableau
	tab[7] = (*ptr).temps_reparation;
}
void test_get_compteurs(void) {
	t_centrifugeuse centri = init_centrifugeuse();
	t_centrifugeuse *ptr = &centri;
	uint tab[8] = { 0 };
	centri.compteur_tocks[0] = 2;
	centri.compteur_tocks[1] = 4;
	centri.compteur_tocks[2] = 8;
	centri.compteur_tocks[3] = 12;
	centri.nombre_bris = 4;
	centri.tocks_apres_bris[0] = 1;
	centri.tocks_apres_bris[1] = 3;
	centri.temps_reparation = 5;
	get_compteurs(ptr, tab);
	for (int i = 0; i < 8; ++i) {
		printf("case %d :     valeur : %d\n", i, tab[i]);
	}
}

double	  get_prob_bris(const t_centrifugeuse * ptr) {
	return (*ptr).probabilite_bris;
}
void test_get_prob_bris(void) {
	t_centrifugeuse test_centri = init_centrifugeuse();
	t_centrifugeuse*ptr = &test_centri;
	double test_proba_bris = get_prob_bris(&test_centri);
	printf("%f\n", test_proba_bris);

}

static void accroitre_prob(t_centrifugeuse * ptr) {
	uint nb_tocks_en_fonction = (*ptr).tocks_apres_bris[0];
	uint nb_tocks_en_attente = (*ptr).tocks_apres_bris[1];
	uint nb_bris = (*ptr).nombre_bris;
	double nouvel_proba_bris;
	
	nouvel_proba_bris = ((1 + nb_tocks_en_fonction + (nb_tocks_en_attente*0.1)) / (1000 + nb_tocks_en_fonction + (nb_tocks_en_attente*0.1))) + (nb_bris / (300 + nb_bris));
	// Affecte la nouvelle probabilite de bris en fonction de l'etat de la centrifugeuse
	if ((*ptr).etat == EN_FONCTION) {
		(*ptr).probabilite_bris =  nouvel_proba_bris;
	}
	else {
		(*ptr).probabilite_bris = PROBA_BRIS_ATTENTE *  nouvel_proba_bris;
	}
}
void   test_accroitre_prob(void) {
	t_centrifugeuse centri = init_centrifugeuse();
	t_centrifugeuse *ptr = &centri;
	centri.etat = EN_FONCTION;
	centri.nombre_bris = 1;
	centri.tocks_apres_bris[0] = 5;
	printf("centrifugeuse en fonction `\n");
	printf("probabilite de bris : %f\n", centri.probabilite_bris);
	accroitre_prob(ptr);
	printf("nouvelle probabilite de bris : %f\n", centri.probabilite_bris);

	centri.probabilite_bris = PROBABILITE_BRIS;
	centri.etat = EN_ATTENTE;
	printf("centrifugeuse en attente `\n");
	printf("probabilite de bris : %f\n", centri.probabilite_bris);
	accroitre_prob(ptr);
	printf("nouvelle probabilite de bris : %f\n", centri.probabilite_bris);
}