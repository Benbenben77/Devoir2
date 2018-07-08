/*****************************************************/
//  PAR   : h saulnier  f henri					     

/*****************************************************/

/* 
	Ce module offre  d'agir(3) ou de renseigner(2) à partir des bits 
	d'un entier positif
*/ 

/*  
	 les int type de base sur nos petites machines ont normalement
	 une représentation à 4 bytes(32 bits) au début du vingt et unième siècle 
	 entiers signed ou unsigned
*/

/* 
	L'ordre des bits dans un entier commence à 0 selon la tradition 
	on part du bit le moins significatif, celui d'ordre 0
	jusqu'au celui du nombre total de bits -1
    Avec 32 bits, l'ordre peut varier de 0 à 31  inclusivement
*/


/*
	les parametres  dans les fonctions offertes plus bas
	sont tous des entiers  positifs de type unsigned int
*/


/*
Le module offre  d'obtenir :


la valeur d'un bit spécifique (0 , 1) avec la fonction  get_bit(nombre, ordre)

la valeur en forcant un bit spécifique à 1 dans un entier
avec la fonction  set_bit(nombre, ordre)

la valeur en forcant un bit spécifique à 0 dans
un entier avec la fonction  clear_bit(nombre, ordre)

la valeur  en forcant l'inversion d'un bit spécifique
dans un entier avec  la fonction  flip_bit(nombre, ordre)

accès à une représentation des bits d'un entier dans une chaine
de caractères avec  la fonction  bits2string(nombre)

*/

/*****************************************************/
/* UNE INTRODUCTION AUX MACOS FONCTIONS */
/*
	 Quatre  fonctions ( get set clear et flip ) ont aussi une version MACRO
	 donnée.
	 Cette alternative à la factorisation classique est importante en génie.
	 La programmation de modules de contrôle est souvent sujette à 
	 de sévères exigences de performance en vitesse d'exécution 
	 l'usage des macros  qui évite les overheads fonctionnels
	 peut parfois accélérer sérieusement un programme.


	 ATTENTION
	 il y a des règles  et un ordre naturel de développement 
	 puisque la fonction restera toujours beaucoup plus sûre 
	 son comportement étant bien plus facile à suivre en DEBUG
	 la macro porte le nom de la fonction tout en majuscules

	 ordre de développement 
	 1 - développer la fonction
	 2 - faire subir à la fonction une batterie de tests de comportement, 
		 on les appelle sommairement tets unitaires 
	 3 - la fonction a maintenant une assurance de qualité
	 4 - développer la MACRO
	 5 - faire subir tous les tests du point 3 simultanément à la fonction et 
	     à la MACRO, les résultats obtenus doivent être partout identiques 
	 6 - la macro peut être utilisée

	 Malgré les 6 points précédents, vous devez  réaliser que JAMAIS en C une 
	 macro n'aura la même assurance de qualité  que sa fonction correspondante.

*/
/**********************************************************/
/**********************************************************/


/*****************************************************/
#ifndef  __MODULE_OP_BITS0255__
#define  __MODULE_OP_BITS0255__

/**********************************************************/
 
#define _CRT_SECURE_NO_WARNINGS  

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

/**********************************************************/


/*****************************************************/
/*		CONSTANTE					*/
/*****************************************************/

/*  Le symbole pour le nombre de bits dans un entier 
	sur la plateforme de compilation.
*/
#define NB_BITS	 (sizeof(unsigned int) * 8)

/* l'intervalle d'ordre acceptable donné en paramètre 
	ira de 0 à  NB_BITS-1 
*/

/*****************************************************/

/*****************************************************/
/*****************************************************/


/******************* GET_BIT **********************/
/* 
	donne la valeur du  bit d'ordre spécifié.		
	PARAMETRES : nombre , un entier non signé						
	              ordre , spécifie le bit voulu dans nombre. 
	RETOUR : 0 ou 1 	

	SPECIFICATIONS :							
	Si ordre n'est pas dans l'intervalle correct 
	la fonction retourne 0	
*/

int get_bit(unsigned int  nombre, unsigned int ordre);

// sa version MACRO
#define GET_BIT(nombre, ordre)  ((((unsigned int) (ordre)) < NB_BITS) ? (((unsigned int)(nombre) & (1 << (unsigned int) (ordre))) != 0) : 0)
/**********************************************************/



/*********************** SET_BIT **************************/
/* 
	donne la valeur du nombre avec le bit d'ordre spécifié mis à 1 
    PARAMETRES : nombre , un entier quelconque					
                 ordre , spécifie le bit mis à 1 dans nombre. 
	RETOUR : la valeur obtenue du paramètre avec ce bit à 1		

	SPECIFICATIONS :								
	Si ordre n'est pas dans l'intervalle correct
	la	fonction retourne la valeur reçue	
*/

unsigned int set_bit(unsigned  int nombre, unsigned int ordre);

// sa version MACRO
#define SET_BIT(nombre, ordre)  ( ((ordre) < NB_BITS) ?  (nombre) |  ( 1 << (ordre) )  : (nombre) )


/**********************************************************/

/****************** CLEAR_BIT **************************/
/* 
	donne la valeur du nombre  avec le bit d'ordre spécifié mis à 0 
	PARAMETRES : nombre , un entier quelconque						
	             ordre , spécifie le bit mis à 0 dans nombre
	RETOUR : la valeur obtenue du paramètre avec ce bit à 0	

	SPECIFICATIONS :								
	Si ordre n'est pas dans l'intervalle correct 
	la fonction retourne la valeur reçue
*/

unsigned int clear_bit(unsigned int  nombre, unsigned int ordre);

// sa version MACRO
#define CLEAR_BIT(nombre, ordre)  ((((unsigned int) (ordre)) < NB_BITS) ? (((unsigned int)(nombre) & ~  (1 << (unsigned int) (ordre)))) : (unsigned int)(nombre))


/**********************************************************/

/******************** FLIP_BIT *************************/
/* 
	donne la valeur du nombre reçu  avec le bit inversé 
	d'ordre spécifié
	Entrée : nombre : un entier positif					
	          ordre : spécifie le bit  à inverser dans nombre. 
	RETOUR : la valeur obtenue du paramètre avec ce bit inversé					
	SPECIFICATIONS :							
	Si ordre n'est pas dans l'intervalle correct 
	la fonction retourne la valeur reçue
*/
unsigned int flip_bit(unsigned int  nombre, unsigned int ordre);

// Remarquez le double usage de l'operateur conditionnel
#define FLIP_BIT(nombre, ordre)   ((((unsigned int)(ordre)) < NB_BITS)  ? GET_BIT(nombre, ordre) ? CLEAR_BIT(nombre, ordre) : SET_BIT(nombre, ordre) : (unsigned int)(nombre))
/**********************************************************/

/***************** BITS2STRING ****************************/
/* 
	donne une représentation string ( chaine de caractère constante) aux
	bits du nombre reçu.        
	PARAMETRE : nombre , un entier non signé		
	RETOUR : une chaine constante								
	SPECIFICATIONS :								
	Les bits sont donnés dans la string du moins significatif au plus 
	significatif, peu importe le signe du paramètre effectif
*/

const char* bits2string(unsigned int nombre);
/**********************************************************/

//c'est fini

#endif
/**********************************************************/

