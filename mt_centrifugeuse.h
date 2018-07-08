/*

 Module : mt_centrifugeuse 
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

/*=========================================================*/
/* LES CONSTANTES */
/*=========================================================*/

#define PROBABILITE_BRIS 0.001
#define PROBA_BRIS_ATTENTE 0.01

// definition des etats possible d'une centrifugeuse
typedef enum {
	EN_BRIS,
	EN_ARRET,
	EN_ATTENTE,
	EN_FONCTION
}ETAT;

typedef unsigned int uint;

typedef struct {
	int etat;
	uint compteur_tocks[4];
	uint nombre_bris;
	double probabilite_bris;
	uint tocks_apres_bris[2];
	uint temps_reparation;
	uint tocks_total;
}t_centrifugeuse;


/******************** PRINT_CENTRIFUGEUSE ********************/

/* Affiche tous les paramètre d'une centrifugeuse */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : - */

void print_centrifugeuse(const t_centrifugeuse * ptr);
void test_print_centrifugeuse(void);

/******************** INIT_CENTRIFUGEUSE ********************/

/* Initialise une centrifugeuse en arret et avec sa probabilite de bris */
/* PARAMETRES : -  */
/* RETOUR : la centrifugeuse initialisee */

t_centrifugeuse init_centrifugeuse(void);
void	   test_init_centrifugeuse(void);

/******************** SET_EN_FONCTION ********************/

/* Change l'etat de la centrifugeuse en fonction  */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : 1 si reussi 0 si echec */

int		  set_en_fonction(t_centrifugeuse * ptr);
void test_set_en_fonction(void);

/******************** SET_EN_ATTENTE ********************/

/* Change l'etat de la centrifugeuse en attente  */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : 1 si reussi 0 si echec */

int		  set_en_attente(t_centrifugeuse * ptr);
void test_set_en_attente(void);

/******************** SET_EN_ARRET ********************/

/* Change l'etat de la centrifugeuse en arret  */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : 1 si reussi 0 si echec */

int		  set_en_arret(t_centrifugeuse * ptr);
void test_set_en_arret(void);

/******************** TOCK_CENTRIFUGEUSE ********************/

/* Genere un tock (unite de temps) pour la centrifugeuse  */
/* Si elle */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : etat de la centrifugeuse */

int		  tock_centrifugeuse(t_centrifugeuse * ptr);
void test_tock_centrifugeuse(void);

/******************** SET_TEMPS_REPARATION ********************/

/* Defini le temps de reparation d'une centrifugeuse brisee  */
/* PARAMETRES : ptr : adresse memoire de la centrifugeuse, 
				temps : temps de reparation de la centrifugeuse  */
/* RETOUR : 1 si reussi 0 si echec */

int		  set_temps_reparation(t_centrifugeuse * ptr, uint temps);
void test_set_temps_reparation(void);

/******************** GET_COMPTEURS ********************/

/* Met a jour tous les compteurs d'une centrifugeuse dans un tableau,
   nombre tock a chaque etat, le nombre de bris, le nombre de tock a partir du dernier bris
   et le temps de reparation */
/* PARAMETRES : ptr : adresse memoire de la centrifugeuse 
				tab : tableau contenant les compteurs d'une centrifugeuse*/
/* RETOUR : - */

void	  get_compteurs(const t_centrifugeuse * ptr, uint * tab);
void test_get_compteurs(void);

/******************** GET_PROB_BRIS ********************/

/* recupere la probabilite de bris d'une centrifugeuse  */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : probabilite de bris de la centrifugeuse */

double	  get_prob_bris(const t_centrifugeuse * ptr);
void test_get_prob_bris(void);

/******************** ACCROITRE_PROB ********************/

/* augmente la probabilite de bris d'une ventrifugeuse pour un tock si elle ne s'est pas brisee  */
/* PARAMETRES : adresse memoire de la centrifugeuse  */
/* RETOUR : - */

static void accroitre_prob(t_centrifugeuse * ptr);
void   test_accroitre_prob(void);

/********************************************************/