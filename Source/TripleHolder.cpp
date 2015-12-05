//On definit ici la classe tripleholder, ensemble de 3 cellules..
#include "TripleHolder.h"

TripleHolder::TripleHolder() {
    cell1=Cell();
    cell2=Cell();
    cell3=Cell();
}

TripleHolder::TripleHolder(Cell &c1, Cell &c2, Cell &c3) {
    cell1=c1;
    cell2=c2;
    cell3=c3;
}

//Getcell permet d'acceder a une des cellules d'un triplet
Cell &TripleHolder::getCell1() {
    return cell1;
}

Cell &TripleHolder::getCell2() {
    return cell2;
}

Cell &TripleHolder::getCell3() {
    return cell3;
}

string TripleHolder::value() {
    string s;
    s+=cell1.iValue;
    s+=cell2.iValue;
    s+=cell3.iValue;
    return s;
}

void TripleHolder::flagValues(ValueEliminator &valEliminator) {
    valEliminator.flag(cell1.iValue);
    valEliminator.flag(cell2.iValue);
    valEliminator.flag(cell3.iValue);
}
// On verifie ici si une valeure est comprise dans un triplet
bool TripleHolder::isValuePresent(unsigned char iValue) {
    if (cell1.iValue==iValue||cell2.iValue==iValue||cell3.iValue==iValue) {
        return true;
    }
    return false;
}

string TripleHolder::getString() {
    string s;
    s+=cell1.iValue;
    s+=cell2.iValue;
    s+=cell3.iValue;
    return s;
}
