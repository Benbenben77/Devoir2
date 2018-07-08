/*

Module : mt_centrifugeuse
Par    : PILOQUET Olivier (PILO13029704), ROGET Benjamin (ROGB09029601)
Date   : 21/06/2018

*/


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

#include "mt_centrifugeuse.h"
#include "mt_ligne_centrifugeuse.h"
#include "mtwister.h"



#if 0
int main(void) {

	//test_init_ligne_centrifugeuse();
	//test_tock_ligne();
	//test_remplacer_centrifugeuse();
	test_get_en_etat();

	
	// on termine avec le standard... HIT ANY KEY	
	system("pause");
	// et ÇA, c'est un 0 avec une cravate...
	return EXIT_SUCCESS;
}
#endif
/*=========================================================*/


void print_ligne_centrifugeuse(t_ligne_centrifugeuse *ptr){

	printf("etat des centrifugeuse                     ");
	for (int iter = 31; iter >= 0; --iter) {
		printf("%d", (*ptr).ligne_centrifugeuse[iter]);
	}
	printf("\ncentrifugeuses en bris		%d	== %s\n", (*ptr).nb_centrifugeuse_bris, bits2string((*ptr).centrifugeuse_bris));
	printf("centrifugeuses en arret		%d	== %s\n", (*ptr).nb_centrifugeuse_arret, bits2string((*ptr).centrifugeuse_arret));
	printf("centrifugeuses en attente	%d	== %s\n", (*ptr).nb_centrifugeuse_attente, bits2string((*ptr).centrifugeuse_attente));
	printf("centrifugeuses en fonction	%d	== %s\n\n", (*ptr).nb_centrifugeuse_fonction, bits2string((*ptr).centrifugeuse_fonction));
}

uint configuration_valide(uint nombre, uint bit_un) {
	uint ordre_bit = 0;
	uint couple_bit = 0;
	uint bit_lu;
	uint nombre_bit_un = 0;
	uint valide = 1;

	// Lis un bit et regarde s'il est egal a 0 ou 1
	while (nombre_bit_un < bit_un) {
		bit_lu = 0;
		bit_lu = get_bit(nombre, ordre_bit);
		// Lis le nombre de bit a '1' consecutifs
		if (bit_lu >= 1) {
			couple_bit += 1;
			nombre_bit_un += 1;
		}
		// reinitialise le nb de bit a '1' si on lis un '0'
		else {
			couple_bit = 0;
		}
		// S'il y a plus que 2 bits egals a '1' cote a cote, retourne une config non valide
		if (couple_bit > 2) {
			valide = 0;
			return valide;
		}
		// parcourt tous les bits du nombre
		ordre_bit += 1;
	}

	// s'il n'y a pas d'erreur, retourne une config valide
	return valide;
}

int init_ligne_centrifugeuse(t_ligne_centrifugeuse* ptr, uint nb_init) {
	int iter;
	int taille_ligne = sizeof(uint) * 8;
	uint ligne_complete;
	uint nb_centrifugeuse_attente = NB_CENTRIFUGEUSE_EN_ATTENTE;
	uint nb_centri_total = nb_init + nb_centrifugeuse_attente;

	// teste si le nombre de centrifugeuse en fonction n'est pas trop grand
	if ((nb_centri_total) > ((2.0 / 3.0) * taille_ligne)) {
		return 0;
	}

	// remplis une ligne de centrifugeuse avec des centrifugeuse en ARRET et une probabilite de bris
	for (iter = 0; iter < taille_ligne; ++iter) {
		(*ptr).ligne_centrifugeuse[iter] = init_centrifugeuse();
	}
	// met toutes les centrifugeuse de la ligne en arret
	(*ptr).centrifugeuse_arret = ~0;
	(*ptr).nb_centrifugeuse_arret = taille_ligne;

	// remplis une ligne avec le nombre de centrifugeuse en fonction donne
	iter = 0;
	while (nb_init > 1) {
		(*ptr).centrifugeuse_fonction = set_bit((*ptr).centrifugeuse_fonction, iter);
		(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter);
		(*ptr).centrifugeuse_fonction = set_bit((*ptr).centrifugeuse_fonction, iter + 1);
		(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter + 1);
		
		//Incrementation/decrementation du nombre de centrifugeuse en fonction/arret
		(*ptr).nb_centrifugeuse_arret -= 2;
		(*ptr).nb_centrifugeuse_fonction += 2;

		(*ptr).ligne_centrifugeuse[iter].etat = EN_FONCTION;
		(*ptr).ligne_centrifugeuse[iter+1].etat = EN_FONCTION;

		iter += 3;
		nb_init -= 2;
	}

	// rajoute la derniere a la ligne si le nombre de centri est impaire.
	if (nb_init == 1) {
		(*ptr).centrifugeuse_fonction = set_bit((*ptr).centrifugeuse_fonction, iter);
		(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter);

		(*ptr).ligne_centrifugeuse[iter].etat = EN_FONCTION;

		//Incrementation/decrementation du nombre de centrifugeuse en fonction/arret
		(*ptr).nb_centrifugeuse_arret -= 1;
		(*ptr).nb_centrifugeuse_fonction += 1;

		if (nb_centrifugeuse_attente == 0) {
			return 1;
		}

		if (nb_centrifugeuse_attente >= 1) {
			(*ptr).centrifugeuse_attente = set_bit((*ptr).centrifugeuse_attente, iter+1);
			(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter+1);
			(*ptr).ligne_centrifugeuse[iter+1].etat = EN_ATTENTE;
			(*ptr).nb_centrifugeuse_arret -= 1;
			(*ptr).nb_centrifugeuse_attente += 1;
		}
		iter += 3;
		nb_centrifugeuse_attente -= 1;

	}

	
	while (nb_centrifugeuse_attente > 1) {
		(*ptr).centrifugeuse_attente = set_bit((*ptr).centrifugeuse_attente, iter);
		(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter);
		(*ptr).centrifugeuse_attente = set_bit((*ptr).centrifugeuse_attente, iter + 1);
		(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter + 1);

		//Incrementation/decrementation du nombre de centrifugeuse en fonction/arret
		(*ptr).nb_centrifugeuse_arret -= 2;
		(*ptr).nb_centrifugeuse_attente += 2;

		(*ptr).ligne_centrifugeuse[iter].etat = EN_ATTENTE;
		(*ptr).ligne_centrifugeuse[iter + 1].etat = EN_ATTENTE;

		iter += 3;
		nb_centrifugeuse_attente -= 2;
	}

	if (nb_centrifugeuse_attente == 1) {
		(*ptr).centrifugeuse_attente = set_bit((*ptr).centrifugeuse_attente, iter);
		(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter);

		(*ptr).ligne_centrifugeuse[iter].etat = EN_ATTENTE;

		//Incrementation/decrementation du nombre de centrifugeuse en fonction/arret
		(*ptr).nb_centrifugeuse_arret -= 1;
		(*ptr).nb_centrifugeuse_attente += 1;
	}
	
	ligne_complete = (*ptr).centrifugeuse_bris & (*ptr).centrifugeuse_arret & (*ptr).centrifugeuse_attente & (*ptr).centrifugeuse_fonction;
	if (ligne_complete == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
void test_init_ligne_centrifugeuse(void){
	t_ligne_centrifugeuse ligne_centri = { 0 };
t_ligne_centrifugeuse *ptr = &ligne_centri;
uint nb_centri_fonct = 11;
int succes;

succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
if (succes != 0) print_ligne_centrifugeuse(ptr);
else printf("nb de centri en fct trop grand\n");
}

int		  ajouter_un(t_ligne_centrifugeuse* ptr) {
	int centri1 = 0;
	int centri2 = 0;
	int i = 0;
	int nb_bris1 = 0;
	int nb_bris2 = 100000;
	int centri_a_set = 99;
	int succes;
	int arret = 0;
	int test_configuration = 0;
	//cherche les centrifugeuse en attente, boucle toute les centrifugeuse possible pour trouver celle avec le moins de nombre de bris
	while (i <= 31 && (*ptr).nb_centrifugeuse_attente != 0) {

		centri2 = 0;
		//detecte la premiere centrifugeuse en attente et renvoie son nombre de bris et son ordre
		while (centri1 == 0 && arret == 0) {
			centri1 = get_bit((*ptr).centrifugeuse_attente, i);
			++i;
			if (i != 31) {
				nb_bris1 = (*ptr).ligne_centrifugeuse[i - 1].nombre_bris;
				centri_a_set = i - 1;
			}
			else { arret = 1; }
		}
		//detecte la deuxieme centrifugeuse en attente et renvoi son nombre de bris et son ordre
		while (centri2 == 0 && i <= 31) {

			centri2 = get_bit((*ptr).centrifugeuse_attente, i);
			++i;
			if (i != 31 && centri2 == 1) {
				nb_bris2 = (*ptr).ligne_centrifugeuse[i - 1].nombre_bris;
			}
		}
		//compare les nombre de bris et prends la centrifugeuse avec le plus petit nombre de bris
		if (nb_bris1 > nb_bris2) {
			centri_a_set = i - 1;
			nb_bris1 = nb_bris2;
		}

	}
	//si une centrifugeuse en attente a été détecter renvoi la nouvelle configuration
	if (centri_a_set != 99) {

		succes = set_en_fonction((&(*ptr).ligne_centrifugeuse[centri_a_set]));
		assert(succes);

		(*ptr).centrifugeuse_attente = clear_bit((*ptr).centrifugeuse_attente, centri_a_set);
		(*ptr).centrifugeuse_fonction = set_bit((*ptr).centrifugeuse_fonction, centri_a_set);

		++(*ptr).nb_centrifugeuse_fonction;
		--(*ptr).nb_centrifugeuse_attente;


		return 1;
	}
	//si aucune centrifugeuse en attente a été détecté va chercher une centrifugeuse en arret
	else {
		centri1 = 0;
		arret = 0;
		i = 0;
		// trouve les centrifugeuse en arret qui respect les condition pour etre activé
		while (i <= 31 && arret == 0) {
			centri1 = 0;
			// détecte une centrifugeuse arreté 
			while (centri1 == 0)
			{
				centri1 = get_bit((*ptr).centrifugeuse_arret, i);
				i++;
				if (i != 31 && centri1 == 1) {
					centri_a_set = i - 1;

				}
				if (i == 31) { arret = 1; }
			}
			// verifie si en ajoutant une nouvelle centrifugeuse la configuration sera toujours valide
			test_configuration = configuration_valide(((*ptr).centrifugeuse_fonction | (1 << (i - 1))), ((*ptr).nb_centrifugeuse_fonction + 1));
			//donne la nouvelle configuration si le nombre total de centrifugeuse active ne depasse pas 2/3 des centrifugeuse 
			//et que la configuration est valide apres l'ajout d'une centrifugeuse
			if (test_configuration == 1 && ((((*ptr).nb_centrifugeuse_fonction + 1) / 32.0) <= (2.0 / 3.0))) {

				succes = set_en_attente((&(*ptr).ligne_centrifugeuse[i - 1]));
				assert(succes);
				succes = set_en_fonction((&(*ptr).ligne_centrifugeuse[i - 1]));
				assert(succes);

				(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, i - 1);
				(*ptr).centrifugeuse_fonction = set_bit((*ptr).centrifugeuse_fonction, i - 1);

				++(*ptr).nb_centrifugeuse_fonction;
				--(*ptr).nb_centrifugeuse_arret;

				return 1;
			}


		}
		return 0;

	}
}
void test_ajouter_un(void) {

	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	uint nb_centri_fonct = 11;
	int succes;
	// le resultat attentu est que le 18 eme bit de la ligne fonction passe a 1 et celui de la ligne attente a 0
	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
	// forcage du nombre de  bris a 4 pour valider la fonction
	(*ptr).ligne_centrifugeuse[18].nombre_bris = 4;

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("nb de centri en fct trop grand\n");

	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");

	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");

	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");
	succes = ajouter_un(ptr);
}

int		  reduire_un(t_ligne_centrifugeuse* ptr) {
	int centri1 = 0;
	int centri2 = 0;
	int i = 0;
	int nb_bris1 = 0;
	int nb_bris2 = 100000;
	int centri_a_set = 99;
	int succes;
	int arret = 0;
	int test_configuration = 0;
	//cherche les centrifugeuse en attente, boucle toute les centrifugeuse possible
	while (i <= 31 && (*ptr).nb_centrifugeuse_attente != 0) {

		centri2 = 0;
		//detecte la premiere centrifugeuse en fonction et renvoie son nombre de bris
		while (centri1 == 0 && arret == 0) {
			centri1 = get_bit((*ptr).centrifugeuse_fonction, i);
			++i;
			if (i != 31) {
				nb_bris1 = (*ptr).ligne_centrifugeuse[i - 1].nombre_bris;
				centri_a_set = i - 1;
			}
			else { arret = 1; }
		}
		//detecte la deuxieme centrifugeuse en fonction et renvoie son nombre de bris
		while (centri2 == 0 && i <= 31) {

			centri2 = get_bit((*ptr).centrifugeuse_fonction, i);
			++i;
			if (i != 31 && centri2 == 1) {
				nb_bris2 = (*ptr).ligne_centrifugeuse[i - 1].nombre_bris;
			}
		}
		//compare les nombre de bris et prends la centrifugeuse avec le plus grand nombre de bris
		if (nb_bris1 < nb_bris2) {
			centri_a_set = i - 1;
			nb_bris1 = nb_bris2;
		}

	}
	//si aucune centrifugeuse en attente a été détecté renvoie un echec sinon renvoi la nouvelle configuration
	if (centri_a_set != 99 && ((*ptr).nb_centrifugeuse_fonction >= 1)) {

		succes = set_en_attente((&(*ptr).ligne_centrifugeuse[centri_a_set]));
		assert(succes);

		(*ptr).centrifugeuse_fonction = clear_bit((*ptr).centrifugeuse_fonction, centri_a_set);
		(*ptr).centrifugeuse_attente = set_bit((*ptr).centrifugeuse_attente, centri_a_set);

		++(*ptr).nb_centrifugeuse_attente;
		--(*ptr).nb_centrifugeuse_fonction;


		return 1;
	}
	else {
		return 0;
	}
}
void test_reduire_un(void) {

	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	uint nb_centri_fonct = 11;
	int succes;
	//resultat attendu est le 2 eme bit de la ligne en fonction a 0 et celui de la ligne en attente a 1
	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
	(*ptr).ligne_centrifugeuse[1].nombre_bris = 4;


	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("nb de centri en fct trop grand\n");

	succes = reduire_un(ptr);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("erreur\n");

}

void	  tock_ligne(t_ligne_centrifugeuse* ptr) {
	int iter;
	int etat[32] = { 0 };

	// Applique un tock a toutes les centrifugeuses de la ligne
	for (iter = 0; iter < 32; ++iter) {
		etat[iter] = tock_centrifugeuse(&(*ptr).ligne_centrifugeuse[iter]);

		// Si l'etat de la centrifugeuse apres le tock est different de l'etat precedant, change cet etat dans la ligne
		if (etat[iter] == EN_BRIS && (((*ptr).centrifugeuse_bris & (1 << iter)) == 0)) {

			(*ptr).nb_centrifugeuse_bris += 1;
			(*ptr).centrifugeuse_bris = set_bit((*ptr).centrifugeuse_bris, iter);

			// test si la centrifugeuse etait en attente ou en fonction au moment ou elle a brise et change sa valeur dans la ligne
			uint masque = 1 << iter;
			if (((*ptr).centrifugeuse_fonction & masque) >> iter == 1) {
				(*ptr).nb_centrifugeuse_fonction -= 1;
				(*ptr).centrifugeuse_fonction = clear_bit((*ptr).centrifugeuse_fonction, iter);
			}
			else {
				(*ptr).nb_centrifugeuse_attente -= 1;
				(*ptr).centrifugeuse_attente = clear_bit((*ptr).centrifugeuse_attente, iter);
			}
		}
		// Si l'etat de la centrifugeuse apres le tock est different de l'etat precedant, change cet etat dans la ligne
		if (etat[iter] == EN_ARRET && (((*ptr).centrifugeuse_arret & (1 << iter)) == 0)) {
			(*ptr).nb_centrifugeuse_arret += 1;
			(*ptr).centrifugeuse_arret = set_bit((*ptr).centrifugeuse_arret, iter);

			(*ptr).nb_centrifugeuse_bris -= 1;
			(*ptr).centrifugeuse_bris = clear_bit((*ptr).centrifugeuse_bris, iter);
		}

		// Si l'etat de la centrifugeuse apres le tock est different de l'etat precedant, change cet etat dans la ligne
		if (etat[iter] == EN_ATTENTE && (((*ptr).centrifugeuse_attente & (1 << iter)) == 0)) {
			(*ptr).nb_centrifugeuse_attente += 1;
			(*ptr).centrifugeuse_attente = set_bit((*ptr).centrifugeuse_attente, iter);

			(*ptr).nb_centrifugeuse_arret -= 1;
			(*ptr).centrifugeuse_arret = clear_bit((*ptr).centrifugeuse_arret, iter);
		}

		// Si l'etat de la centrifugeuse apres le tock est different de l'etat precedant, change cet etat dans la ligne
		if (etat[iter] == EN_FONCTION && (((*ptr).centrifugeuse_fonction & (1 << iter)) == 0)) {
			(*ptr).nb_centrifugeuse_fonction += 1;
			(*ptr).centrifugeuse_fonction = set_bit((*ptr).centrifugeuse_fonction, iter);

			(*ptr).nb_centrifugeuse_attente -= 1;
			(*ptr).centrifugeuse_attente = clear_bit((*ptr).centrifugeuse_attente, iter);
		}
	}
}
void test_tock_ligne(void) {
	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	uint nb_centri_fonct = 11;
	int succes;

	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
	assert(succes);

	print_ligne_centrifugeuse(ptr);

	// augmentation de la proba de la premier centri pour qu'elle casse
	(*ptr).ligne_centrifugeuse[3].probabilite_bris = 0.99;
	tock_ligne(ptr);
	print_ligne_centrifugeuse(ptr);

	// definition du temps de reparation à 1 pour qu'elle se repare
	uint temps_rep = 1;
	(*ptr).ligne_centrifugeuse[0].temps_reparation = 1;
	assert(succes);
	tock_ligne(ptr);
	print_ligne_centrifugeuse(ptr);

	for (int i = 0; i < 5000; ++i) {
		tock_ligne(ptr);
	}

	print_ligne_centrifugeuse(ptr);

	printf("%d", (*ptr).ligne_centrifugeuse[16].probabilite_bris);
	print_centrifugeuse(&(*ptr).ligne_centrifugeuse[16]);

}

t_centrifugeuse remplacer_centrifugeuse(t_ligne_centrifugeuse* ptr, uint position) {
	t_centrifugeuse copi_centri;
	t_centrifugeuse centri_vide = { 0 };

	if (position > 0 && position < 32) {
		if ((*ptr).ligne_centrifugeuse[position].etat != EN_ATTENTE && (*ptr).ligne_centrifugeuse[position].etat != EN_FONCTION){
			copi_centri = (*ptr).ligne_centrifugeuse[position];
			(*ptr).ligne_centrifugeuse[position] = init_centrifugeuse();
			return copi_centri;
		}
	}
	else {
		return centri_vide;
	}
}
void	   test_remplacer_centrifugeuse(void) {
	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	t_centrifugeuse copi;
	uint nb_centri_fonct = 11;
	uint position = 2;
	int succes;


	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
	assert(succes);

	ligne_centri.ligne_centrifugeuse[position].nombre_bris = 10;

	copi = remplacer_centrifugeuse(ptr, position);
	printf("\ncopie : \n");
	print_centrifugeuse(&copi);
	printf("\nnouvelle centri : \n");
	print_centrifugeuse(&(*ptr).ligne_centrifugeuse[position]);
}

uint	  get_en_etat(const t_ligne_centrifugeuse* ptr, int etat) {
	switch (etat) {

	case EN_BRIS:
		return (*ptr).centrifugeuse_bris;
		break;

	case EN_ARRET:
		return (*ptr).centrifugeuse_arret;
		break;

	case EN_ATTENTE:
		return (*ptr).centrifugeuse_attente;
		break;

	case EN_FONCTION:
		return (*ptr).centrifugeuse_fonction;
		break;

	default: 0;
	}
}
void test_get_en_etat(void) {
	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	t_centrifugeuse copi;
	uint nb_centri_fonct = 11;
	int etat = EN_FONCTION;
	int succes;

	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
	assert(succes);
	get_en_etat(ptr, etat);
}

t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse* ptr, uint position) {
	t_centrifugeuse copie_centri;
	t_centrifugeuse *ptr1 = &copie_centri;

	// recupere toute les valeurs de la centrifugeuse sur la ligne de centrifugeuse en entrée et en position donné
	(*ptr1).etat = (*ptr).ligne_centrifugeuse[position].etat;
	(*ptr1).compteur_tocks[0] = (*ptr).ligne_centrifugeuse[position].compteur_tocks[0];
	(*ptr1).compteur_tocks[1] = (*ptr).ligne_centrifugeuse[position].compteur_tocks[1];
	(*ptr1).compteur_tocks[2] = (*ptr).ligne_centrifugeuse[position].compteur_tocks[2];
	(*ptr1).compteur_tocks[3] = (*ptr).ligne_centrifugeuse[position].compteur_tocks[3];

	(*ptr1).nombre_bris = (*ptr).ligne_centrifugeuse[position].nombre_bris;

	(*ptr1).probabilite_bris = (*ptr).ligne_centrifugeuse[position].probabilite_bris;

	(*ptr1).tocks_apres_bris[0] = (*ptr).ligne_centrifugeuse[position].tocks_apres_bris[0];
	(*ptr1).tocks_apres_bris[1] = (*ptr).ligne_centrifugeuse[position].tocks_apres_bris[1];

	(*ptr1).temps_reparation = (*ptr).ligne_centrifugeuse[position].temps_reparation;

	(*ptr1).tocks_total = (*ptr).ligne_centrifugeuse[position].tocks_total;


	return copie_centri;

}
void	   test_get_centrifugeuse(void) {
	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	uint nb_centri_fonct = 11;
	int succes;
	t_centrifugeuse  test_centri;

	// resultat attendu est une copie de la centrifugeuse en position 3
	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);

	if (succes != 0) print_ligne_centrifugeuse(ptr);
	else printf("nb de centri en fct trop grand\n");

	print_centrifugeuse(&(*ptr).ligne_centrifugeuse[2]);

	test_centri = get_centrifugeuse(ptr, 2);

	print_centrifugeuse(&test_centri);
}

static  void permuter_centrifugeuse(t_ligne_centrifugeuse* ptr, uint p1, uint p2) {
	t_centrifugeuse copi_centri;
	int ligne_etatp1, ligne_etatp2;
	
	if ((*ptr).ligne_centrifugeuse[p1].etat != (*ptr).ligne_centrifugeuse[p2].etat) {
		ligne_etatp1 = get_en_etat(ptr, (*ptr).ligne_centrifugeuse[p2].etat);
		ligne_etatp1 = set_bit(ligne_etatp1, p1);

		
	}

	copi_centri = (*ptr).ligne_centrifugeuse[p1];
	(*ptr).ligne_centrifugeuse[p1] = (*ptr).ligne_centrifugeuse[p2];
	(*ptr).ligne_centrifugeuse[p2] = copi_centri;


}
void	test_permuter_centrifugeuse(void) {
	t_ligne_centrifugeuse ligne_centri = { 0 };
	t_ligne_centrifugeuse *ptr = &ligne_centri;
	t_centrifugeuse copi;
	uint nb_centri_fonct = 11;
	int succes;

	succes = init_ligne_centrifugeuse(ptr, nb_centri_fonct);
	assert(succes);
}