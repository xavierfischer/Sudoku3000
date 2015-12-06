#include "Cellule.h"

/*
    On definit ici la classe cellule et on verifie que chaque cellule est bien remplie
    Chaque cellule est definie comme un couple (iValue, NumberCell) où
        iValue represente la valeur textuelle de la cellule, celle qui est affichée dans l'interface
        numberCell représente la valeur numérique de la cellule
*/

// Constructeur par défaut
Cellule::Cellule() {
	value = 0;
}
Cellule::Cellule(int n){
	value = n;
}
bool Cellule::isEmpty() {
    if (value==0) {
        return true;
    }
    else {
        return value==0;
    }
}
