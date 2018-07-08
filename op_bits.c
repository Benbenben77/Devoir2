/*****************************************************/
//  PAR   : h saulnier  f henri					     

/*****************************************************/

/*********************************************************/

/* implémentation des fonctions offertes dans op_bits.h*/
/* toutes sont simples et basées sur les bitwise operators du C */

#include "op_bits.h"

/*********************************************************/


/*****************************************************/
/*		DEFINITIONS DES FONCTIONS				*/
/*****************************************************/



/*****************************************************/
int get_bit(unsigned int nombre, unsigned int ordre) {
	// STRATEGIE
	// tester  ordre valide 
	// si oui, un bitwise and && avec un train de bit n'ayant 
	// qu'un 1 judicieusement placé au bon ordre
	// sinon retour de 0

	if (ordre < NB_BITS){
		return  (nombre & (1 << ordre)) != 0 ;
	}
	return 0;
}

/*****************************************************/
unsigned int set_bit(unsigned int nombre, unsigned int ordre) {
	// STRATEGIE
	// tester ordre valide
	// SI OUI un bitwise or avec un train de bit n'ayant qu'un 1
	// judicieusement placé au bon ordre
	// sinon retour de la valeur recue 

	if (ordre < NB_BITS){
		return  nombre | (1 << ordre);
	}
	return nombre ;

}

/*****************************************************/
unsigned int clear_bit(unsigned int nombre, unsigned int ordre){
	// STRATEGIE
	// tester ordre valide
	// SI OUI un bitwise and avec le complement d un train de bits 
	//  qui  a  un un seul  0 judicieusement placé au bon ordre
	// sinon retour de la valeur recue 


	if (ordre < NB_BITS){
		return nombre & ~(1 << ordre);
	}
	return nombre;
}

/*****************************************************/
unsigned int flip_bit(unsigned int nombre, unsigned int ordre){
	// STRATEGIE
	// tester ordre valide
	// SI OUI si le bit ordre est à 1, on le clear sinon on le set	
	// sinon retour de la valeur recue 

	if (ordre < NB_BITS){
		if (get_bit(nombre, ordre)) {
			return clear_bit(nombre, ordre);
		}
		return set_bit(nombre, ordre);
	}
	return nombre;
	
}

/*****************************************************/




/*****************************************************/
//ATTENTION
// ce code n est pas pour vous
// ne le lisez meme pas
// profitez-en actuellement
// je vous l'expliquerai plus tard

const char* bits2string(unsigned int nombre) {

	// 200 c'est plus que suffisant
	// buffer est une locale dont la position est permanente
	static unsigned char buffer[200] = { 0 };

	int i; // iterateur

	// s'assure de l'indicateur de fin de chaine 
	buffer[NB_BITS] = 0;

	// boucle d'assignation de chaque bit obtenu 
	// de get_bit dans la string ( mais en ordre inverse )
	for (i = 0; i< NB_BITS; i += 1) {
		buffer[NB_BITS - 1 - i] = GET_BIT(nombre, i) ? '1' : '0';
	}

	// retour de la string
	return buffer;
}
/*****************************************************/

