/*****************************************************/
//  PAR   : h saulnier  f henri					     

/*****************************************************/

/* 
	Ce module offre  d'agir(3) ou de renseigner(2) � partir des bits 
	d'un entier positif
*/ 

/*  
	 les int type de base sur nos petites machines ont normalement
	 une repr�sentation � 4 bytes(32 bits) au d�but du vingt et uni�me si�cle 
	 entiers signed ou unsigned
*/

/* 
	L'ordre des bits dans un entier commence � 0 selon la tradition 
	on part du bit le moins significatif, celui d'ordre 0
	jusqu'au celui du nombre total de bits -1
    Avec 32 bits, l'ordre peut varier de 0 � 31  inclusivement
*/


/*
	les parametres  dans les fonctions offertes plus bas
	sont tous des entiers  positifs de type unsigned int
*/


/*
Le module offre  d'obtenir :


la valeur d'un bit sp�cifique (0 , 1) avec la fonction  get_bit(nombre, ordre)

la valeur en forcant un bit sp�cifique � 1 dans un entier
avec la fonction  set_bit(nombre, ordre)

la valeur en forcant un bit sp�cifique � 0 dans
un entier avec la fonction  clear_bit(nombre, ordre)

la valeur  en forcant l'inversion d'un bit sp�cifique
dans un entier avec  la fonction  flip_bit(nombre, ordre)

acc�s � une repr�sentation des bits d'un entier dans une chaine
de caract�res avec  la fonction  bits2string(nombre)

*/

/*****************************************************/
/* UNE INTRODUCTION AUX MACOS FONCTIONS */
/*
	 Quatre  fonctions ( get set clear et flip ) ont aussi une version MACRO
	 donn�e.
	 Cette alternative � la factorisation classique est importante en g�nie.
	 La programmation de modules de contr�le est souvent sujette � 
	 de s�v�res exigences de performance en vitesse d'ex�cution 
	 l'usage des macros  qui �vite les overheads fonctionnels
	 peut parfois acc�l�rer s�rieusement un programme.


	 ATTENTION
	 il y a des r�gles  et un ordre naturel de d�veloppement 
	 puisque la fonction restera toujours beaucoup plus s�re 
	 son comportement �tant bien plus facile � suivre en DEBUG
	 la macro porte le nom de la fonction tout en majuscules

	 ordre de d�veloppement 
	 1 - d�velopper la fonction
	 2 - faire subir � la fonction une batterie de tests de comportement, 
		 on les appelle sommairement tets unitaires 
	 3 - la fonction a maintenant une assurance de qualit�
	 4 - d�velopper la MACRO
	 5 - faire subir tous les tests du point 3 simultan�ment � la fonction et 
	     � la MACRO, les r�sultats obtenus doivent �tre partout identiques 
	 6 - la macro peut �tre utilis�e

	 Malgr� les 6 points pr�c�dents, vous devez  r�aliser que JAMAIS en C une 
	 macro n'aura la m�me assurance de qualit�  que sa fonction correspondante.

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

/* l'intervalle d'ordre acceptable donn� en param�tre 
	ira de 0 �  NB_BITS-1 
*/

/*****************************************************/

/*****************************************************/
/*****************************************************/


/******************* GET_BIT **********************/
/* 
	donne la valeur du  bit d'ordre sp�cifi�.		
	PARAMETRES : nombre , un entier non sign�						
	              ordre , sp�cifie le bit voulu dans nombre. 
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
	donne la valeur du nombre avec le bit d'ordre sp�cifi� mis � 1 
    PARAMETRES : nombre , un entier quelconque					
                 ordre , sp�cifie le bit mis � 1 dans nombre. 
	RETOUR : la valeur obtenue du param�tre avec ce bit � 1		

	SPECIFICATIONS :								
	Si ordre n'est pas dans l'intervalle correct
	la	fonction retourne la valeur re�ue	
*/

unsigned int set_bit(unsigned  int nombre, unsigned int ordre);

// sa version MACRO
#define SET_BIT(nombre, ordre)  ( ((ordre) < NB_BITS) ?  (nombre) |  ( 1 << (ordre) )  : (nombre) )


/**********************************************************/

/****************** CLEAR_BIT **************************/
/* 
	donne la valeur du nombre  avec le bit d'ordre sp�cifi� mis � 0 
	PARAMETRES : nombre , un entier quelconque						
	             ordre , sp�cifie le bit mis � 0 dans nombre
	RETOUR : la valeur obtenue du param�tre avec ce bit � 0	

	SPECIFICATIONS :								
	Si ordre n'est pas dans l'intervalle correct 
	la fonction retourne la valeur re�ue
*/

unsigned int clear_bit(unsigned int  nombre, unsigned int ordre);

// sa version MACRO
#define CLEAR_BIT(nombre, ordre)  ((((unsigned int) (ordre)) < NB_BITS) ? (((unsigned int)(nombre) & ~  (1 << (unsigned int) (ordre)))) : (unsigned int)(nombre))


/**********************************************************/

/******************** FLIP_BIT *************************/
/* 
	donne la valeur du nombre re�u  avec le bit invers� 
	d'ordre sp�cifi�
	Entr�e : nombre : un entier positif					
	          ordre : sp�cifie le bit  � inverser dans nombre. 
	RETOUR : la valeur obtenue du param�tre avec ce bit invers�					
	SPECIFICATIONS :							
	Si ordre n'est pas dans l'intervalle correct 
	la fonction retourne la valeur re�ue
*/
unsigned int flip_bit(unsigned int  nombre, unsigned int ordre);

// Remarquez le double usage de l'operateur conditionnel
#define FLIP_BIT(nombre, ordre)   ((((unsigned int)(ordre)) < NB_BITS)  ? GET_BIT(nombre, ordre) ? CLEAR_BIT(nombre, ordre) : SET_BIT(nombre, ordre) : (unsigned int)(nombre))
/**********************************************************/

/***************** BITS2STRING ****************************/
/* 
	donne une repr�sentation string ( chaine de caract�re constante) aux
	bits du nombre re�u.        
	PARAMETRE : nombre , un entier non sign�		
	RETOUR : une chaine constante								
	SPECIFICATIONS :								
	Les bits sont donn�s dans la string du moins significatif au plus 
	significatif, peu importe le signe du param�tre effectif
*/

const char* bits2string(unsigned int nombre);
/**********************************************************/

//c'est fini

#endif
/**********************************************************/

