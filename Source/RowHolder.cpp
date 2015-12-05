// On definit ici une ligne comme un ensemble de 3 triplets tripleholder
#include "RowHolder.h"

RowHolder::RowHolder() {

}

RowHolder::RowHolder(Cell &cLeft, Cell &cCenter, Cell &cRight) : TripleHolder(cLeft, cCenter, cRight) {

}

Cell &RowHolder::G(void){
    return TripleHolder::getCell1();
}

Cell &RowHolder::C(void){
    return TripleHolder::getCell2();
}

Cell &RowHolder::D(void){
    return TripleHolder::getCell3();
}

string RowHolder::printRow() {
    string s;
    s=char(G());
    s+=" ";
    s+=char(C());
    s+=" ";
    s+=char(D());
    return s;
}
