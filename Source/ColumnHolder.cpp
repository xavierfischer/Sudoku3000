#include "ColumnHolder.h"

/*
	ColumnHolder hérite de TripleHolder. 
	Une instance de ColumnHolder représente trois cellules alignées dans le sens vertical, repérées par les lettres T, C et B pour Top, Center et Bottom. 
*/

/*
	Constructeur par défaut : crée un holder vide
*/

ColumnHolder::ColumnHolder() {
}

/*
	Crée un holder

	Paramètres : 
		cTop : Cellule du haut
		cCenter : Cellule centrale
		cBottom : Cellule du bas
*/

ColumnHolder::ColumnHolder(Cell &cTop, Cell &cCenter, Cell &cBottom) : TripleHolder(cTop, cCenter, cBottom) {
}

/*
	Retourne la cellule du haut
*/

Cell &ColumnHolder::T(void){
    return TripleHolder::getCell1();
}

/*
	Retourne la cellule du centre
*/

Cell &ColumnHolder::C(void){
    return TripleHolder::getCell2();
}

/*
	Retourne la cellule du bas
*/

Cell &ColumnHolder::B(void){
    return TripleHolder::getCell3();
}
