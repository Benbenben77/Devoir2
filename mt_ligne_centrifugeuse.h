/*

Module : mt_ligne_centrifugeuse
Par    : PILOQUET Olivier (PILO13029704), ROGET Benjamin (ROGB09029601)
Date   : 21/06/2018

Ce module permet d'effectuer des operation sur une centrifugeuse
changement d'etat de centrifugeuse, gestion du temps (tocks) des centrifugeuse)
gestion des probabilites de bris en fonction de l'etat et gestion des compteurs de tocks

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

//#include "op_bits.h"

//#include "devoir1.h"
/*=========================================================*/
/* LES CONSTANTES */
/*=========================================================*/

#define NB_CENTRIFUGEUSE_EN_ATTENTE 0;


typedef struct {
	t_centrifugeuse ligne_centrifugeuse[sizeof(uint)*8];
	uint nb_centrifugeuse_fonction;
	uint nb_centrifugeuse_bris;
	uint nb_centrifugeuse_attente;
	uint nb_centrifugeuse_arret;
	uint centrifugeuse_fonction;
	uint centrifugeuse_bris;
	uint centrifugeuse_attente;
	uint centrifugeuse_arret;
}t_ligne_centrifugeuse;


/******************** PRINT_CENTRIFUGEUSE ********************/

/* Affiche une ligne de centrifugeuse */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : - */

void	  print_ligne_centrifugeuse(t_ligne_centrifugeuse *ptr);
void test_print_ligne_ventrifugeuse(void);

int		  init_ligne_centrifugeuse(t_ligne_centrifugeuse* ptr, uint nb_init);
void test_init_ligne_centrifugeuse(void);

int		  ajouter_un(t_ligne_centrifugeuse* ptr);
void test_ajouter_un(void);

int		  reduire_un(t_ligne_centrifugeuse* ptr);
void test_reduire_un(void);

void	  tock_ligne(t_ligne_centrifugeuse* ptr);
void test_tock_ligne(void);

t_centrifugeuse remplacer_centrifugeuse(t_ligne_centrifugeuse* ptr, uint position);
void	   test_remplacer_centrifugeuse(void);

uint	  get_en_etat(const t_ligne_centrifugeuse* ptr, int etat);
void test_get_en_etat(void);

t_centrifugeuse get_centrifugeuse(const t_ligne_centrifugeuse* ptr, uint position);
void	   test_get_centrifugeuse(void);

static  void permuter_centrifugeuse(t_ligne_centrifugeuse* ptr, uint p1, uint p2);
void	test_permuter_centrifugeuse(void);

uint configuration_valide(uint nombre, uint bit_un);
