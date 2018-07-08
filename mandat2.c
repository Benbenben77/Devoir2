//=========================================================
// 	petit main montrant le plus simple
//  code acceptable pour le mandat 2
//=========================================================

/*=========================================================*/

#define _CRT_SECURE_NO_WARNINGS 
/*=========================================================*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<assert.h>


#include "op_bits.h"

// VOUS AJUSTEREZ  AUX NOMS DE VOS MODULES
#include "mt_centrifugeuse.h"
#include "mt_ligne_centrifugeuse.h"

/*=========================================================*/
/* LES CONSTANTES */
/*=========================================================*/

// LE NOMBRE DE CENTRIFUGEUSES EN ACTION INITIALEMENT
#define NB_INITIAL 11

// LE NOMBRE DE BRIS DE CENTRIFUGEUSES QUI ARRETE LA SIMULATION
#define NB_BRIS_MAX 40
/*=========================================================*/
/*
	 j'utilise la fonction 
	 int get_nb_bris(const t_ligne_centrifugeuse* ptr) ;
	 que je vous ai décrite dans le mail de mardi soir (19 juin)
	 pour contrôler la boucle principale

	 SI LES NOMS DE VOS FONCTIONS D'AFFICHAGE DIFFÈRENT, 
	 VOUS DEVEZ SIMPLEMENT METTRE LES VOTRES
*/
/*=========================================================*/
#if 1
int main(void){

	t_ligne_centrifugeuse lig01;

	int cpt_bris = 0; // pas de bris encore, tout est neuf dans la ligne

	/* a la fin de la boucle principale
	   on  cherche une centrifugeuse brisée à remplacer
	   on se servira  de 4 variables
	   du train de bits des brisées dans la ligne
	   d'une position , d'une centrifugeuse  pour  copier
	   celle qu'on élimine
	   et d'un flag de découverte
	   */
	int position_bris = 0;
	unsigned int centri_en_bris;
	t_centrifugeuse  ordure;
	int trouve = 0;


	// VOILÀ ON COMMENCE L'ACTION

	// initialisation obligatoire de la ligne
	assert(init_ligne_centrifugeuse(&lig01, NB_INITIAL));
	// et son premier affichage
	print_ligne_centrifugeuse(&lig01);


	// tant que le nombre de bris dans la ligne < constante
	// on tock et on affiche si un bris s'est produit
	while (cpt_bris < NB_BRIS_MAX){
		int bris_actuel;

		tock_ligne(&lig01);

		// vérification du bris
		bris_actuel = get_nb_bris(&lig01);
		if (bris_actuel> cpt_bris){
			print_ligne_centrifugeuse(&lig01);
			cpt_bris = bris_actuel;
		}

	}
	// fin de la boucle principale et affichage de la ligne
	printf("\n fin de la boucle principale\n");
	print_ligne_centrifugeuse(&lig01);


	// il ne reste qu'à chercher une centrifugeuse 
	// en bris dans le train de bits de celles EN_BRIS
	// à la remplacer par une neuve
	// d'afficher la ligne et la certifugeuse éliminée

	centri_en_bris = get_en_etat(&lig01, EN_BRIS);

	while ((position_bris < NB_BITS) &(trouve == 0)){

		if (GET_BIT(centri_en_bris, position_bris)){
			trouve = 1;
			ordure = remplacer_centrifugeuse(&lig01, position_bris);
			print_centrifugeuse(&ordure);
		}
		++position_bris;
	}

	system("pause");
	return EXIT_SUCCESS;
}
/*=========================================================*/



#endif

