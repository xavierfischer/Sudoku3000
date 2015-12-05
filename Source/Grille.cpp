#include "Grille.h"

Grille::Grille(){
    for(int i=1;i<10;i++){
        for(int j=1;j<10;j++){
            values[i][j] = 0;
        }
    }
}

void Grille::setValues(int data[9][9]){
        for(int i=1;i<10;i++){
        for(int j=1;j<10;j++){
            values[i][j] = data[i][j];
        }
    }
}

int *Grille::getLine(int i){
    return values[i];
}
