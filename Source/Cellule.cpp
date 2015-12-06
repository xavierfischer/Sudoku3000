
#include "Cell.h"
#include <iostream>
#include <stdexcept>
#include "Header.h"

Cellule::Cellule(){
    Value='-';
}
// On Verifie qu'il y a bien un chiffre entre 1 et 9 pour chaque cellule
Cellule::Cellule (char Value){
    try {
        if (Value!='-') {
            if (!isdigit(Value)) {
                this->Value='-';
                this->numberCell=0;
                throw domain_error("Veuillez insérer un chiffre");
            }
            int nombre = Value - '0';
            if (nombre<=0||nombre>=10) {
                this->Value='-'
                throw out_of_range("Veuillez insérer un chiffre compris entre 1 et 9.");
            }
            this->Value=Value;
        }
        else {
        this->Value=Value;
        }
    }
    catch (const exception &e) {
        cout << e.what() << endl;
    }
    catch(...) {
        cout << "Veuillez insérer un chiffre valable." << endl;
    }
}
//Verifie si la cellule est vide
bool Cellule::isEmpty() {
    if (Value=='-') {
        return true;
    }
    else {
        return false;
    }
}



Cell::operator unsigned char() const {
    return this->Value;
}

bool Cell::operator==(unsigned char Value) const {
    if (this->Value==Value) {
        return true;
    } else {
        return false;
    }
}

