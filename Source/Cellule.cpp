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
	isguess=false
}
Cellule::Cellule(int n){
	value = n;
}
<<<<<<< HEAD
bool Cellule::isEmpty() {
    if (value==0) {
        return true;
    }
    else {
        return value==0;
    }
}
bool Cellule::isguess() {
}
Cellule::getvalue(int i, int j);
this->value = alue;
    print Cellule([i],[j])
    return *this;
}
=======
void Cellule::setValue(int n) {
	value = n;
}
>>>>>>> origin/MoussInterface
