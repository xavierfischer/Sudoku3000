
/**
On definit ici la classe region, soit par ligne, soit par colonne. On introduit aussi 2 fonctions qui permettent de verifier si la region est
pleine (isFull) et si elle est consistente (isConsistent)
*/

#include "Region.h"
//On definit une region comme un ensemble de cellules.
Region::Region() {
    numbers=*new list<Cell>;
}
// une region est definie par les nombres qui la composent (string sNumbers) et par le booleen by column qui indique si on traite la region en ligne ou en colonne.
Region::Region (string sNumbers, bool byColumn) {
    try {
        if (sNumbers.size()!=9) {
            // TODO throw domain_error("Nombre incorrect de chiffres dans la region");
        }

        //On peut definir la region soit par ligne, soit par colonne. Par défaut la chaine de nombre est donnée par ligne :

        if (byColumn==false) {
            NO=Cell(sNumbers[0]);
            N=Cell(sNumbers[1]);
            NE=Cell(sNumbers[2]);
            O=Cell(sNumbers[3]);
            C=Cell(sNumbers[4]);
            E=Cell(sNumbers[5]);
            SO=Cell(sNumbers[6]);
            S=Cell(sNumbers[7]);
            SE=Cell(sNumbers[8]);
            sValues=sNumbers;
            for (int i=0; i<9; i++) {
                numbers.push_back(Cell(sNumbers[i]));
            }
        } else {
            NO=Cell(sNumbers[0]);
            O=Cell(sNumbers[1]);
            SO=Cell(sNumbers[2]);
            N=Cell(sNumbers[3]);
            C=Cell(sNumbers[4]);
            S=Cell(sNumbers[5]);
            NE=Cell(sNumbers[6]);
            E=Cell(sNumbers[7]);
            SE=Cell(sNumbers[8]);

            sValues=sNumbers[0];
            numbers.push_back(Cell(sNumbers[0]));
            sValues+=sNumbers[3];
            numbers.push_back(Cell(sNumbers[3]));
            sValues+=sNumbers[6];
            numbers.push_back(Cell(sNumbers[6]));
            sValues+=sNumbers[1];
            numbers.push_back(Cell(sNumbers[1]));
            sValues+=sNumbers[4];
            numbers.push_back(Cell(sNumbers[4]));
            sValues+=sNumbers[7];
            numbers.push_back(Cell(sNumbers[7]));
            sValues+=sNumbers[2];
            numbers.push_back(Cell(sNumbers[2]));
            sValues+=sNumbers[5];
            numbers.push_back(Cell(sNumbers[5]));
            sValues+=sNumbers[8];
            numbers.push_back(Cell(sNumbers[8]));
        }
    } catch (const exception &e) {
        cout << e.what() << endl;
    }
}

//indique si une region est remplie ou non
bool Region::isFull() {
    if (numbers.size()!=9) {
        return false;
    }
    for (Cell c : numbers) {
        if (c.isEmpty()) {
            return false;
        }
    }
    return true;
}
/**
    Cette fonction vérifie s'il n'y a pas de doublons dans une région
 */

bool Region::isConsistent() {

    //TODO Ecrire une version simplifiée sans itérateur

    list<char> listChars;
    for(list<Cell>::iterator it=numbers.begin();it!=numbers.end();it++){
        if (char(*it)!='-')
            listChars.push_back(char(*it));
    }
    listChars.sort();
    list<char> listChars2(listChars);
    listChars2.unique();
    if(listChars2.size()==listChars.size())
        return true;
    else
        return false;
}

Cell &Region::getCell(int value){
    return value == 1 ? NO :
            value == 2 ? N :
            value == 3 ? NE :
            value == 4 ? O :
            value == 5 ? C :
            value == 6 ? E :
            value == 7 ? SO :
            value == 8 ? S : SE;
}

int Region::numberNotEmpty(){
    return listOfValues().size();
}

list<int> Region::listOfValues(){
    list<int> listValues;
    for(int i=1;i<10;i++){
        Cell &c = getCell(i);
        if(!c.isEmpty()){
            listValues.push_back(c.numberCell);
        }
    }
    return listValues;
}
