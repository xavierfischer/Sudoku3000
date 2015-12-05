//On definit ici une region comme un carre de 9 cellules soit 3 triplets.
#include "RegionHolder.h"

RegionHolder::RegionHolder() {
    cells=*new list<Cell*>;
}

RegionHolder::RegionHolder(Region &region) {
    list<Cell>::iterator it=region.numbers.begin();
    for (int i=0;i<9;i++){
        Cell* b = new Cell(*it);
        this->cells.push_back(b);
        it++;
    }
    iter=cells.begin();
}

Cell & RegionHolder::NO(void){
    return *(*iter);
}
Cell & RegionHolder::N(void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<1;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::NE (void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<2;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::O(void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<3;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::C(void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<4;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::E(void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<5;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::SO(void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<6;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::S (void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<7;i++){
        it2++;	}
    return **it2;
}
Cell & RegionHolder::SE (void){
    list<Cell*>::iterator it2=iter;
    for (int i=0;i<8;i++){
        it2++;	}
    return **it2;
}



RowHolder RegionHolder::TopRow() {
    return RowHolder(NO(),N(),NE());
}

RowHolder RegionHolder::MiddleRow() {
    return RowHolder(O(),C(),E());
}

RowHolder RegionHolder::BottomRow() {
    return RowHolder(SO(),S(),SE());
}

ColumnHolder RegionHolder::LeftColumn() {
    return ColumnHolder(NO(), O(), SO());
}

ColumnHolder RegionHolder::MiddleColumn() {
    return ColumnHolder(N(), C(), S());
}

ColumnHolder RegionHolder::RightColumn() {
    return ColumnHolder(NE(), E(), SE());
}

void RegionHolder::flagValues(ValueEliminator &valEliminator) {
    for (list<Cell*>::iterator it=cells.begin();it!=cells.end();it++){
        valEliminator.flag(char(**it));
    }
}
// Cette fonction verifie si une valeure est bien presente dans une region donnee.
bool RegionHolder::isValuePresent(unsigned char iValue) {
    for (list<Cell*>::iterator it=cells.begin();it!=cells.end();it++){
        if (**it == iValue) {
            return true;
        }
    }
    return false;
}
// Cette fonction verifie si une region est bien complete
bool RegionHolder::isFull() {
    for (list<Cell*>::iterator it=cells.begin();it!=cells.end();it++){
        if ((*it)->isEmpty())
            return false;
    }
    return true;
}

string RegionHolder::getString() {
    string s;
    for (list<Cell*>::iterator it=cells.begin(); it!=cells.end();it++) {
        Cell c=**it;
        s+=c.iValue;
    }
    return s;
}
