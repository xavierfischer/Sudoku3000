#include "Cell.h"
#include <iostream>
#include <stdexcept>
#include "Header.h"

/*
    On definit ici la classe cellule et on verifie que chaque cellule est bien remplie
    Chaque cellule est definie comme un couple (iValue, NumberCell) où
        iValue represente la valeur textuelle de la cellule, celle qui est affichée dans l'interface
        numberCell représente la valeur numérique de la cellule
*/

// Constructeur par défaut
Cell::Cell(){
    iValue='-';
    numberCell=0;

}
/*
    Crée une cellule
    On vérifie qu'il y a bien un chiffre et qu'il s'agit d'un entier entre 1 et 9 pour chaque cellule, ou du character '-' pour une cellule indéfinie

    iValue : la valeur à placer dans cette cellule
*/

Cell::Cell (char iValue){
    try {
        if (iValue!='-') {
            if (!isdigit(iValue)) {
                this->iValue='-';
                this->numberCell=0;
                throw domain_error("Veuillez insérer un chiffre dans la cellule.");
            }
            int iNumber = iValue - '0';
            if (iNumber<=0||iNumber>=10) {
                this->iValue='-';
                this->numberCell=0;
                throw out_of_range("Veuillez insérer un chiffre en 1 et 9.");
            }
            this->iValue=iValue;
            this->numberCell=iNumber;
        } else {
        this->iValue=iValue;
        this->numberCell=0;
        }
    }
    catch (const exception &e) {
        cout << e.what() << endl;
    }
    catch(...) {
        cout << "Veuillez insérer un chiffre valable dans la cellule." << endl;
    }
}

//Verifie si la cellule est vide ou non
bool Cell::isEmpty() {
    if (iValue=='-') {
        return true;
    }
    else {
        return false;
    }
}

Cell &Cell::operator= (unsigned char iValue){
    this->iValue = iValue;
    int iNumber = iValue - '0';
    this->numberCell=iNumber;
    return *this;
}

Cell::operator unsigned char() const {
    return this->iValue;
}

bool Cell::operator==(unsigned char iValue) const {
    if (this->iValue==iValue) {
        return true;
    } else {
        return false;
    }
}