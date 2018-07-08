/*==========================================================*/
/* 
	Une courte présentation francaise suit l'introduction en anglais des auteurs
	et donne le caractère général de chaque  fonction

   Les auteurs n'offrant que des distributions uniformes qui peuvent parfois 
   paraitre redondantes.
   J'ai ajouté des fonctions standardisées pour obtenir des évènements  
   dans une distribution :
		uniforme générale( avec  ou  sans  bornes ) entière ou réelle.
		normale avec Z(0,1) ou normale à moyenne et écart-type définis
	
	Je n'ai ajouté qu'une présentation minimale en francais aux fonctions originales
	offertes sans rien  y changer + quelques observations pour nos étudiants

	Le commentaire en présentation des déclarations originales de fonctions 
	ne suit pas le modèle donné dans le cours....
	il est vraiment 'limité' mais c'est souvent ainsi qu'on offre
	du code....  mal emballé.

	hs

*/
/*==========================================================*/

/*==========================================================*/
// DES AUTEURS
/* 
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)  
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.                          

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote 
        products derived from this software without specific prior written 
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

/*==========================================================*/

#ifndef _MT19937AR_H_
#define _MT19937AR_H_
/*==========================================================*/

//permet de désactiver certains warnings de stdio
#define _CRT_SECURE_NO_WARNINGS   
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>


/*==========================================================*/
/*==========================================================*/

/* VOICI UNE INTERFACE MODULAIRE STANDARD POUR MES ÉTUDIANTS */

/*==========================================================*/
/*  D'abord l'offre de deux fonctions d'initialisation du
     générateur. Un générateur non-initialisé s'initialise 
     en fait à 0 et émet la même séquence ce qui fait douter
	 du caractère aléatoire.... C'est au client de l'initialiser
	 MAIS JUSTE UNE FOIS dans tout le programme.
*/

/*==========================================================*/
/* La fonction mt_srand 
 la forme d'initialisation la plus classique d'un générateur  
 à partir d'un entier quelconque, la séquence pseudo aléatoire 
 à venir est totalement déterminée par la valeur reçue en paramètre

PARAMETRE(s): s, un entier quelconque

SORTIE: aucune

SPECS: aucune
*/
void mt_srand(unsigned long s);

/*==========================================================*/


/*==========================================================*/
/* la fonction mt_srandSys 
 une forme alternative d'initialisation du générateur à partir 
 de l'horloge interne de la machine,  l'horloge donne un entier
 qui sert de paramètre à la fonction précédente. 
 Cette valeur est retournée pour des motifs de possible reproduction
 des conditions initiales d'une simulation numérique.

PARAMETRE(s): Aucun

SORTIE: l'entier qui a véritablement initialisé le générateur

SPECS: aucune
*/
unsigned long mt_srandSys(void);
/*==========================================================*/

/* LES CINQ FONCTIONS D'ÉMISSION DANS LES DISTRIBUTIONS SPÉCIFIÉES */

/*==========================================================*/
/* La fonction mt_rand   
L'émission d'un nombre réel dans la distribution uniforme 0,1 

PARAMETRE(s): Aucun

SORTIE : la valeur émise par le générateur

SPECS : aucune
*/
double mt_rand(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randf

L'émission d'un nombre réel dans une  uniforme [b1, b2] 

PARAMETRE(s): deux valeurs réelles quelconques qui serviront 
               de bornes à l'intervalle

SORTIE : la valeur émise par le générateur

SPECS : l'ordre des paramètres n'a aucune importance
*/
double mt_randf(double b1, double b2);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randi

L'émission d'un nombre entier positif dans une uniforme [1, borne]

PARAMETRE(s): une valeur entière quelconque

SORTIE : la valeur entière émise par le générateur

SPECS :  si le paramètre effectif < 0 , c'est la valeur absolue 
			du paramètre  qui sera considérée
         recevant 0 elle retourne automatiquement 0 et 
			c'est le seul 0 possible
*/
int mt_randi(int borne);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randn

L'émission d'un nombre réel dans la distribution normale Z, 
la plus classique  de moyenne 0 et d'écart type 1

PARAMETRE(s) : Aucun

SORTIE : la valeur réelle émise par le générateur

SPECS : celle-ci a une parité dans l'émission
ce qui peut déconcerter si on réinitialise le générateur
en cours d'exécution ( ce qui en réalité ne doit PAS être fait)
*/
double mt_randn(void);
/*==========================================================*/

/*==========================================================*/
/* La fonction mt_randnormal

L'émission d'un nombre réel dans une distribution normale quelconque, 
  de moyenne mu  et d'écart-type sigma donnés

PARAMETRE(s) : mu définit la moyenne voulue et sigma l'écart-type

SORTIE : la valeur réelle émise par le générateur

SPECS : le signe de sigma n'a pas d'importance.
*/
double mt_randnormal(double mu, double sigma);

/*==========================================================*/






/*==========================================================*/
/* SUIT L'INTERFACE ORIGINALE DES DEUX CRÉATEURS */
/*==========================================================*/
/* 
   l'utilisation du type long par les auteurs avait une importance
   historique lorsque les entiers de base(int) pouvaient encore avoir une 
   représentation à 16 bits, le long nous assurait de 32 bits (ce 
   que les auteurs considèrent normal, puisque c'est le format 
   qu'ils décrivent partout) et c'est 32 bits qu'on obtient maintenant 
   sur tout compilateur moderne avec un int.

   l'utilisation du modificateur unsigned  par les auteurs 
   fait partie des choixs offerts au client. Les auteurs auraient bien
   pu passer sous silence et tout dans l'interface serait en int.
   
	Encore par souci d'élargir l'interface, les auteurs offrent toutes 
	les 4 formes d'uniformes réelles entre 0 et 1 :
		(0,1) intervalle ouvert --sans 0 ni 1 --
		[0,1) intervalle ouvert à droite -- avec 0 mais sans 1 --
		(0,1] intervalle ouvert à gauche -- sans 0 mais avec 1 --
		[0,1] intervalle fermé  -- avec 0 et avec 1 --

  */
/*==========================================================*/
/*	Deux formes d'init possibles.
	Vous pouvez ne pas vous préoccuper du unsigned long 
	en paramètre formel et donner un int ou un tableau 
	de int (En assumant alors le warning possible)
*/
/*==========================================================*/

/* initializes mersenne twister 
   pseudo-random number generator with a seed */
/* initialisation à partir d'un entier quelconque */
/* la séquence pseudo aléatoire sera totalement déterminée*/

void mt_init_genrand(unsigned long s);
/*==========================================================*/


/*	initialize by an array with array-length
	init_key is the array for initializing keys
	key_length is its length
	slight change for C++, 2004/2/26
	idem in ANSI C
*/
/* variante de la précédente mais ici,
  donnez- lui un tableau  d'entiers et la taille du tableau */

void mt_init_by_array(const unsigned long init_key[], int key_length);
/*==========================================================*/

/* generates a random number on [0,0xffffffff]-interval*/
/* Pour obtenir un entier sur 32 bits pseudo-aléatoires */
unsigned long mt_genrand_int32(void);

/*==========================================================*/
/* generates a random number on [0,0x7fffffff]-interval*/
/* Pour obtenir un entier sur 31 bits pseudo-aléatoires */
/* Vous êtes simplement assuré qu'il ne sera pas négatif */
/* si on récupère dans un int à 32 bits*/
long mt_genrand_int31(void);

/*==========================================================*/

/*==========================================================*/

/* These real versions are due to Isaku Wada, 2002/01/09 added */

/* et les quatre uniformes dans l'intervalle 0,1 */
/* simplement différenciées par le suffixe 1,2,3,53*/
/* PAS très fort comme représentativité ...... */
/* mais l'âme japonaise souffre surement des mêmes maux que la notre!*/

/* generates a random number on [0,1]-real-interval*/
double mt_genrand_real1(void);

/* generates a random number on [0,1)-real-interval*/
double mt_genrand_real2(void);

/* generates a random number on (0,1)-real-interval*/
double mt_genrand_real3(void);

/* generates a random number on [0,1) with 53-bit resolution*/
double mt_genrand_res53(void);
/*==========================================================*/

/*==========================================================*/
#endif	
/*==========================================================*/

