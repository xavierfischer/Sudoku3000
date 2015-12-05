
#include "ValueEliminator.h"

ValueEliminator::ValueEliminator() {
    for (int i=0; i<9; i++) {
        missingValues[i]=false;
    }
}

void ValueEliminator::flag(unsigned char iValue) {
    try {
        if (iValue =='-') {
        }
        else {
            int iNumber = iValue - '0';
            missingValues[iNumber-1]=true;
        }
    } catch (...) {
        cout << "Impossible de flaguer la cellule" << endl;
    }
}

//Nombre de valeurs manquantes dans la region, donc encore disponible
int ValueEliminator::availableValues() {
    int count=0;
    for (int i=0; i<9; i++) {
        if (missingValues[i]==false) {
            count++;
        }
    }
    return count;
}

char ValueEliminator::availableValue() {
    char temp=0;
    try {
        if (availableValues()==0) {
            // TODO throw logic_error("Aucune valeur manquante");
        }
        for (int i=0; i<9; i++) {
            if (missingValues[i]==false) {
                int result = i+1;
                return result + '0';
            }
        }
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
    return temp;
}

