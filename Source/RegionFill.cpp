#include "RegionFill.h"

RegionFill::RegionFill(Region &reg):region(reg) {}

/**
    Algorithme optimisé pour le remplissage d'une région quand huit valeurs sont présentes
*/

bool RegionFill::fill(){
    int myints[] = {1,2,3,4,5,6,7,8,9};
    list<int> possibleValues (myints, myints + sizeof(myints)/sizeof(int));
    int lastEmptyCell = 0;
    for(int i=1;i<10;i++){
        Cell &c = region.getCell(i);
        if(!c.isEmpty()){
            possibleValues.remove(c.numberCell);
        } else
            lastEmptyCell = i;
    }
    if(possibleValues.size()==1){
        region.getCell(lastEmptyCell).numberCell = possibleValues.front();
        region.getCell(lastEmptyCell).iValue = possibleValues.front() + '0';
        return true;
    }
    return false;
}
