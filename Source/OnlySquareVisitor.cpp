//
#include "OnlySquareVisitor.h"

OnlySquareVisitor::OnlySquareVisitor() {}

bool OnlySquareVisitor::Visit(Grid &grid) {

    if (visitOnce(grid)==true) {//On execute la strategie 2 fois, car une fois qu'une cellule est resolue, une deuxieme peut etre resolue
        visitOnce(grid);
        return true;
    }
    else {
        return false;
    }
}

bool OnlySquareVisitor::visitOnce(Grid &grid) {
    bool change=false;
    int regNumber=0;
    RegionHolder region1;
    RegionHolder region2;
    RegionHolder region3;
    RowHolder row1;
    RowHolder row2;
    RowHolder row3;
    ColumnHolder col1;
    ColumnHolder col2;
    ColumnHolder col3;
    Region regions[9];
    int i=0;

    for (list<Region>::iterator it=grid.regions.begin();it!=grid.regions.end();it++){
        regNumber++;
        RegionHolder reg(*it);
        if(!reg.isFull()) {
            int cellNumber=0;
            for (list<Cell*>::iterator it2=reg.cells.begin(); it2!=reg.cells.end();it2++) {
                cellNumber++;
                if ((*it2)->isEmpty()) {
                    ValueEliminator valEliminator;
                    reg.flagValues(valEliminator);//On flag d'abord toutes les valeurs de la region
                    //On selectionne les bonnes lignes à flaguer
                    if (regNumber<=3) {
                        //Top regions
                        region1=grid.NO();
                        region2=grid.N();
                        region3=grid.NE();
                    }
                    else if (regNumber>3 && regNumber<=6) {
                        //Middle regions
                        region1=grid.O();
                        region2=grid.C();
                        region3=grid.E();
                    }
                    else {
                        //Bottom regions
                        region1=grid.SO();
                        region2=grid.S();
                        region3=grid.SE();
                    }

                    if (cellNumber<=3) {
                        //Top Rows
                        row1=region1.TopRow();
                        row2=region2.TopRow();
                        row3=region3.TopRow();
                    }
                    else if (cellNumber>3 && cellNumber<=6) {
                        //Middle rows
                        row1=region1.MiddleRow();
                        row2=region2.MiddleRow();
                        row3=region3.MiddleRow();
                    }
                    else {
                        //Bottom rows
                        row1=region1.BottomRow();
                        row2=region2.BottomRow();
                        row3=region3.BottomRow();
                    }
                    row1.flagValues(valEliminator);//On flag la ligne entière de la cellule
                    row2.flagValues(valEliminator);
                    row3.flagValues(valEliminator);

                    //Ensuite on selectionne les bonnes colonnes
                    if (regNumber%3==1) {
                        //Top regions
                        region1=grid.NO();
                        region2=grid.O();
                        region3=grid.SO();
                    }
                    else if (regNumber%3==2) {
                        //Middle regions
                        region1=grid.N();
                        region2=grid.C();
                        region3=grid.S();
                    }
                    else {
                        //Bottom regions
                        region1=grid.NE();
                        region2=grid.E();
                        region3=grid.SE();
                    }

                    if (cellNumber%3==1) {
                        //Left columns
                        col1=region1.LeftColumn();
                        col2=region2.LeftColumn();
                        col3=region3.LeftColumn();
                    }
                    else if (cellNumber%3==2) {
                        //Middle columns
                        col1=region1.MiddleColumn();
                        col2=region2.MiddleColumn();
                        col3=region3.MiddleColumn();
                    }
                    else {
                        //Right columns
                        col1=region1.RightColumn();
                        col2=region2.RightColumn();
                        col3=region3.RightColumn();
                    }
                    col1.flagValues(valEliminator);//On flague la colonne entière de la cellule
                    col2.flagValues(valEliminator);
                    col3.flagValues(valEliminator);

                    //Ensuite on regarde dans valEliminator s'il ne reste plus qu'une seule valeur possible
                    if (valEliminator.availableValues()==1) {
                        char iVal=valEliminator.availableValue();
                        **it2=iVal;
                        change=true;
                    }
                }
            }
        }
        //On reconstruit chaque region
        regions[i]=Region(reg.getString());
        i++;
    }
    //Enfin on reconstruit la grille avec les nouvelles regions
    grid=Grid(regions[0], regions[1], regions[2], regions[3], regions[4], regions[5], regions[6], regions[7], regions[8]);

    return change;
}
