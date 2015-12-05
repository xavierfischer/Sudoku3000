
#include "TwoOutOfThreeColumnVisitor.h"
#include <string>


TwoOutOfThreeColumnVisitor::TwoOutOfThreeColumnVisitor() {}

/**
    La fonction Visit permet de


*/

bool TwoOutOfThreeColumnVisitor::Visit(Grid &grid) {
    bool change=false;
    int count=0;

    // Décomposition de la grille en régions, stockées dans le tableau regionsNew
    // Chaque région est initialisée par sa String

    Region regionsNew[9];
    regionsNew[0]=Region(grid.NO().getString());
    regionsNew[1]=Region(grid.N().getString());
    regionsNew[2]=Region(grid.NE().getString());
    regionsNew[3]=Region(grid.O().getString());
    regionsNew[4]=Region(grid.C().getString());
    regionsNew[5]=Region(grid.E().getString());
    regionsNew[6]=Region(grid.SO().getString());
    regionsNew[7]=Region(grid.S().getString());
    regionsNew[8]=Region(grid.SE().getString());

    RegionHolder region1;
    RegionHolder region2;
    RegionHolder region3;

    //Colonne de gauche

    /*
        Dans les trois régions de gauche, pour chaque valeur, on recherche s'il existe des situations où un nombre est trouvé dans deux régions
        et absent dans la troisième.

        Si c'est le cas, on recoupe les informations qu'on a sur la ligne correspondante pour tenter de découvrir une cellule.
    */

    for (int i=1; i<=9; i++) {
        region1=grid.NO();
        region2=grid.O();
        region3=grid.SO();
        // TODO fonction to_string(int i) ?
        // char iValue = std::to_string(i)[0];
        char iValue = i+'0';
        count=region1.isValuePresent(iValue)+region2.isValuePresent(iValue)+region3.isValuePresent(iValue);

        if (count==2) {
            RegionHolder regMissing;
            RegionHolder reg1;
            RegionHolder reg2;
            ColumnHolder col1;
            ColumnHolder col2;
            ColumnHolder colMissing;
            int regNumber = 0;
            int regNumberTrue=0;
            int colNumber = 0;

            if (!region1.isValuePresent(iValue)) {
                regNumber=1;
                regNumberTrue=0;
                regMissing=region1;
                reg1=region2;
                reg2=region3;
            }
            else if (!region2.isValuePresent(iValue)) {
                regNumber=2;
                regNumberTrue=3;
                regMissing=region2;
                reg1=region1;
                reg2=region3;
            }
            else {
                regNumber=3;
                regNumberTrue=6;
                regMissing=region3;
                reg1=region1;
                reg2=region2;
            }

            if ((reg1.LeftColumn().isValuePresent(iValue)&&reg2.RightColumn().isValuePresent(iValue))||(reg1.RightColumn().isValuePresent(iValue)&&reg2.LeftColumn().isValuePresent(iValue))) {
                colMissing=regMissing.MiddleColumn();
                colNumber=2;
            }
            else if ((reg1.LeftColumn().isValuePresent(iValue)&&reg2.MiddleColumn().isValuePresent(iValue))||(reg1.MiddleColumn().isValuePresent(iValue)&&reg2.LeftColumn().isValuePresent(iValue))) {
                colMissing=regMissing.RightColumn();
                colNumber=3;
            }
            else {
                colMissing=regMissing.LeftColumn();
                colNumber=1;
            }

            int count2=0;
            if (colMissing.T().isEmpty()) count2++;
            if (colMissing.C().isEmpty()) count2++;
            if (colMissing.B().isEmpty()) count2++;

            if (count2==1) {
                if (colMissing.T().isEmpty())
                    colMissing.cell1=Cell(iValue);
                else if (colMissing.C().isEmpty())
                    colMissing.cell2=Cell(iValue);
                else
                    colMissing.cell3=Cell(iValue);
                change=true;
            }
            else if (count2==2||count2==3) {
                ValueEliminator valEliminatorT;
                ValueEliminator valEliminatorC;
                ValueEliminator valEliminatorB;
                if (regNumber==1) {
                    grid.NO().TopRow().flagValues(valEliminatorT);
                    grid.N().TopRow().flagValues(valEliminatorT);
                    grid.NE().TopRow().flagValues(valEliminatorT);
                    grid.NO().MiddleRow().flagValues(valEliminatorC);
                    grid.N().MiddleRow().flagValues(valEliminatorC);
                    grid.NE().MiddleRow().flagValues(valEliminatorC);
                    grid.NO().BottomRow().flagValues(valEliminatorB);
                    grid.N().BottomRow().flagValues(valEliminatorB);
                    grid.NE().BottomRow().flagValues(valEliminatorB);
                }
                else if (regNumber==2) {
                    grid.O().TopRow().flagValues(valEliminatorT);
                    grid.C().TopRow().flagValues(valEliminatorT);
                    grid.E().TopRow().flagValues(valEliminatorT);
                    grid.O().MiddleRow().flagValues(valEliminatorC);
                    grid.C().MiddleRow().flagValues(valEliminatorC);
                    grid.E().MiddleRow().flagValues(valEliminatorC);
                    grid.O().BottomRow().flagValues(valEliminatorB);
                    grid.C().BottomRow().flagValues(valEliminatorB);
                    grid.E().BottomRow().flagValues(valEliminatorB);
                }
                else {
                    grid.SO().TopRow().flagValues(valEliminatorT);
                    grid.S().TopRow().flagValues(valEliminatorT);
                    grid.SE().TopRow().flagValues(valEliminatorT);
                    grid.SO().MiddleRow().flagValues(valEliminatorC);
                    grid.S().MiddleRow().flagValues(valEliminatorC);
                    grid.SE().MiddleRow().flagValues(valEliminatorC);
                    grid.SO().BottomRow().flagValues(valEliminatorB);
                    grid.S().BottomRow().flagValues(valEliminatorB);
                    grid.SE().BottomRow().flagValues(valEliminatorB);
                }
                if (valEliminatorT.missingValues[i-1]==true) {
                    if (valEliminatorC.missingValues[i-1]==true||colMissing.cell2.isEmpty()==false) {
                        colMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorB.missingValues[i-1]==true||colMissing.cell3.isEmpty()==false) {
                        colMissing.cell2=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorC.missingValues[i-1]==true) {
                    if (valEliminatorT.missingValues[i-1]==true||colMissing.cell1.isEmpty()==false) {
                        colMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorB.missingValues[i-1]==true||colMissing.cell3.isEmpty()==false) {
                        colMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorB.missingValues[i-1]==true) {
                    if (valEliminatorT.missingValues[i-1]==true||colMissing.cell1.isEmpty()==false) {
                        colMissing.cell2=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorC.missingValues[i-1]==true||colMissing.cell2.isEmpty()==false) {
                        colMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
            }

            string sValues;
            if (colNumber==1) {
                sValues=colMissing.getString();
                sValues+=regMissing.MiddleColumn().getString();
                sValues+=regMissing.RightColumn().getString();
            }
            else if (colNumber==2) {
                sValues=regMissing.LeftColumn().getString();
                sValues+=colMissing.getString();
                sValues+=regMissing.RightColumn().getString();
            }
            else {
                sValues=regMissing.LeftColumn().getString();
                sValues+=regMissing.MiddleColumn().getString();
                sValues+=colMissing.getString();
            }

            regionsNew[regNumberTrue]=Region(sValues, true);
        }
        grid=Grid(regionsNew[0], regionsNew[1], regionsNew[2], regionsNew[3], regionsNew[4], regionsNew[5], regionsNew[6], regionsNew[7], regionsNew[8]);
    }

    //Colonnes du milieu

    for (int i=1; i<=9; i++) {
        region1=grid.N();
        region2=grid.C();
        region3=grid.S();
        // TODO char iValue = to_string(i)[0];
        char iValue = i+'0';
        count=region1.isValuePresent(iValue)+region2.isValuePresent(iValue)+region3.isValuePresent(iValue);
        if (count==2) {
            RegionHolder regMissing;
            RegionHolder reg1;
            RegionHolder reg2;
            ColumnHolder col1;
            ColumnHolder col2;
            ColumnHolder colMissing;
            int regNumber = 0;
            int regNumberTrue=0;
            int colNumber = 0;

            if (!region1.isValuePresent(iValue)) {
                regNumber=1;
                regNumberTrue=1;
                regMissing=region1;
                reg1=region2;
                reg2=region3;
            }
            else if (!region2.isValuePresent(iValue)) {
                regNumber=2;
                regNumberTrue=4;
                regMissing=region2;
                reg1=region1;
                reg2=region3;
            }
            else {
                regNumber=3;
                regNumberTrue=7;
                regMissing=region3;
                reg1=region1;
                reg2=region2;
            }

            if ((reg1.LeftColumn().isValuePresent(iValue)&&reg2.RightColumn().isValuePresent(iValue))||(reg1.RightColumn().isValuePresent(iValue)&&reg2.LeftColumn().isValuePresent(iValue))) {
                colMissing=regMissing.MiddleColumn();
                colNumber=2;
            }
            else if ((reg1.LeftColumn().isValuePresent(iValue)&&reg2.MiddleColumn().isValuePresent(iValue))||(reg1.MiddleColumn().isValuePresent(iValue)&&reg2.LeftColumn().isValuePresent(iValue))) {
                colMissing=regMissing.RightColumn();
                colNumber=3;
            }
            else {
                colMissing=regMissing.LeftColumn();
                colNumber=1;
            }

            int count2=0;
            if (colMissing.T().isEmpty()) count2++;
            if (colMissing.C().isEmpty()) count2++;
            if (colMissing.B().isEmpty()) count2++;

            if (count2==1) {
                if (colMissing.T().isEmpty()) colMissing.cell1=Cell(iValue);
                if (colMissing.C().isEmpty()) colMissing.cell2=Cell(iValue);
                if (colMissing.B().isEmpty()) colMissing.cell3=Cell(iValue);
                change=true;
            }
            else if (count2==2||count2==3) {
                ValueEliminator valEliminatorT;
                ValueEliminator valEliminatorC;
                ValueEliminator valEliminatorB;
                if (regNumber==1) {
                    grid.NO().TopRow().flagValues(valEliminatorT);
                    grid.N().TopRow().flagValues(valEliminatorT);
                    grid.NE().TopRow().flagValues(valEliminatorT);
                    grid.NO().MiddleRow().flagValues(valEliminatorC);
                    grid.N().MiddleRow().flagValues(valEliminatorC);
                    grid.NE().MiddleRow().flagValues(valEliminatorC);
                    grid.NO().BottomRow().flagValues(valEliminatorB);
                    grid.N().BottomRow().flagValues(valEliminatorB);
                    grid.NE().BottomRow().flagValues(valEliminatorB);
                }
                else if (regNumber==2) {
                    grid.O().TopRow().flagValues(valEliminatorT);
                    grid.C().TopRow().flagValues(valEliminatorT);
                    grid.E().TopRow().flagValues(valEliminatorT);
                    grid.O().MiddleRow().flagValues(valEliminatorC);
                    grid.C().MiddleRow().flagValues(valEliminatorC);
                    grid.E().MiddleRow().flagValues(valEliminatorC);
                    grid.O().BottomRow().flagValues(valEliminatorB);
                    grid.C().BottomRow().flagValues(valEliminatorB);
                    grid.E().BottomRow().flagValues(valEliminatorB);
                }
                else {
                    grid.SO().TopRow().flagValues(valEliminatorT);
                    grid.S().TopRow().flagValues(valEliminatorT);
                    grid.SE().TopRow().flagValues(valEliminatorT);
                    grid.SO().MiddleRow().flagValues(valEliminatorC);
                    grid.S().MiddleRow().flagValues(valEliminatorC);
                    grid.SE().MiddleRow().flagValues(valEliminatorC);
                    grid.SO().BottomRow().flagValues(valEliminatorB);
                    grid.S().BottomRow().flagValues(valEliminatorB);
                    grid.SE().BottomRow().flagValues(valEliminatorB);
                }
                if (valEliminatorT.missingValues[i-1]==true) {
                    if (valEliminatorC.missingValues[i-1]==true||colMissing.cell2.isEmpty()==false) {
                        colMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorB.missingValues[i-1]==true||colMissing.cell3.isEmpty()==false) {
                        colMissing.cell2=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorC.missingValues[i-1]==true) {
                    if (valEliminatorT.missingValues[i-1]==true||colMissing.cell1.isEmpty()==false) {
                        colMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorB.missingValues[i-1]==true||colMissing.cell3.isEmpty()==false) {
                        colMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorB.missingValues[i-1]==true) {
                    if (valEliminatorT.missingValues[i-1]==true||colMissing.cell1.isEmpty()==false) {
                        colMissing.cell2=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorC.missingValues[i-1]==true||colMissing.cell2.isEmpty()==false) {
                        colMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
            }

            string sValues;
            if (colNumber==1) {
                sValues=colMissing.getString();
                sValues+=regMissing.MiddleColumn().getString();
                sValues+=regMissing.RightColumn().getString();
            }
            else if (colNumber==2) {
                sValues=regMissing.LeftColumn().getString();
                sValues+=colMissing.getString();
                sValues+=regMissing.RightColumn().getString();
            }
            else {
                sValues=regMissing.LeftColumn().getString();
                sValues+=regMissing.MiddleColumn().getString();
                sValues+=colMissing.getString();
            }

            regionsNew[regNumberTrue]=Region(sValues, true);
        }
        grid=Grid(regionsNew[0], regionsNew[1], regionsNew[2], regionsNew[3], regionsNew[4], regionsNew[5], regionsNew[6], regionsNew[7], regionsNew[8]);
    }

    //Colonnes de droite

    for (int i=1; i<=9; i++) {
        region1=grid.NE();
        region2=grid.E();
        region3=grid.SE();

        // TODO char iValue = to_string(i)[0];
        char iValue = i+'0';

        count=region1.isValuePresent(iValue)+region2.isValuePresent(iValue)+region3.isValuePresent(iValue);
        if (count==2) {
            RegionHolder regMissing;
            RegionHolder reg1;
            RegionHolder reg2;
            ColumnHolder col1;
            ColumnHolder col2;
            ColumnHolder colMissing;
            int regNumber = 0;
            int regNumberTrue=0;
            int colNumber = 0;

            if (!region1.isValuePresent(iValue)) {
                regNumber=1;
                regNumberTrue=2;
                regMissing=region1;
                reg1=region2;
                reg2=region3;
            }
            else if (!region2.isValuePresent(iValue)) {
                regNumber=2;
                regNumberTrue=5;
                regMissing=region2;
                reg1=region1;
                reg2=region3;
            }
            else {
                regNumber=3;
                regNumberTrue=8;
                regMissing=region3;
                reg1=region1;
                reg2=region2;
            }

            if ((reg1.LeftColumn().isValuePresent(iValue)&&reg2.RightColumn().isValuePresent(iValue))||(reg1.RightColumn().isValuePresent(iValue)&&reg2.LeftColumn().isValuePresent(iValue))) {
                colMissing=regMissing.MiddleColumn();
                colNumber=2;
            }
            else if ((reg1.LeftColumn().isValuePresent(iValue)&&reg2.MiddleColumn().isValuePresent(iValue))||(reg1.MiddleColumn().isValuePresent(iValue)&&reg2.LeftColumn().isValuePresent(iValue))) {
                colMissing=regMissing.RightColumn();
                colNumber=3;
            }
            else {
                colMissing=regMissing.LeftColumn();
                colNumber=1;
            }

            int count2=0;
            if (colMissing.T().isEmpty()) count2++;
            if (colMissing.C().isEmpty()) count2++;
            if (colMissing.B().isEmpty()) count2++;

            if (count2==1) {
                if (colMissing.T().isEmpty()) colMissing.cell1=Cell(iValue);
                if (colMissing.C().isEmpty()) colMissing.cell2=Cell(iValue);
                if (colMissing.B().isEmpty()) colMissing.cell3=Cell(iValue);
                change=true;
            }
            else if (count2==2||count2==3) {
                ValueEliminator valEliminatorT;
                ValueEliminator valEliminatorC;
                ValueEliminator valEliminatorB;
                if (regNumber==1) {
                    grid.NO().TopRow().flagValues(valEliminatorT);
                    grid.N().TopRow().flagValues(valEliminatorT);
                    grid.NE().TopRow().flagValues(valEliminatorT);
                    grid.NO().MiddleRow().flagValues(valEliminatorC);
                    grid.N().MiddleRow().flagValues(valEliminatorC);
                    grid.NE().MiddleRow().flagValues(valEliminatorC);
                    grid.NO().BottomRow().flagValues(valEliminatorB);
                    grid.N().BottomRow().flagValues(valEliminatorB);
                    grid.NE().BottomRow().flagValues(valEliminatorB);
                }
                else if (regNumber==2) {
                    grid.O().TopRow().flagValues(valEliminatorT);
                    grid.C().TopRow().flagValues(valEliminatorT);
                    grid.E().TopRow().flagValues(valEliminatorT);
                    grid.O().MiddleRow().flagValues(valEliminatorC);
                    grid.C().MiddleRow().flagValues(valEliminatorC);
                    grid.E().MiddleRow().flagValues(valEliminatorC);
                    grid.O().BottomRow().flagValues(valEliminatorB);
                    grid.C().BottomRow().flagValues(valEliminatorB);
                    grid.E().BottomRow().flagValues(valEliminatorB);
                }
                else {
                    grid.SO().TopRow().flagValues(valEliminatorT);
                    grid.S().TopRow().flagValues(valEliminatorT);
                    grid.SE().TopRow().flagValues(valEliminatorT);
                    grid.SO().MiddleRow().flagValues(valEliminatorC);
                    grid.S().MiddleRow().flagValues(valEliminatorC);
                    grid.SE().MiddleRow().flagValues(valEliminatorC);
                    grid.SO().BottomRow().flagValues(valEliminatorB);
                    grid.S().BottomRow().flagValues(valEliminatorB);
                    grid.SE().BottomRow().flagValues(valEliminatorB);
                }
                if (valEliminatorT.missingValues[i-1]==true) {
                    if (valEliminatorC.missingValues[i-1]==true||colMissing.cell2.isEmpty()==false) {
                        colMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorB.missingValues[i-1]==true||colMissing.cell3.isEmpty()==false) {
                        colMissing.cell2=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorC.missingValues[i-1]==true) {
                    if (valEliminatorT.missingValues[i-1]==true||colMissing.cell1.isEmpty()==false) {
                        colMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorB.missingValues[i-1]==true||colMissing.cell3.isEmpty()==false) {
                        colMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorB.missingValues[i-1]==true) {
                    if (valEliminatorT.missingValues[i-1]==true||colMissing.cell1.isEmpty()==false) {
                        colMissing.cell2=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorC.missingValues[i-1]==true||colMissing.cell2.isEmpty()==false) {
                        colMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
            }

            string sValues;
            if (colNumber==1) {
                sValues=colMissing.getString();
                sValues+=regMissing.MiddleColumn().getString();
                sValues+=regMissing.RightColumn().getString();
            }
            else if (colNumber==2) {
                sValues=regMissing.LeftColumn().getString();
                sValues+=colMissing.getString();
                sValues+=regMissing.RightColumn().getString();
            }
            else {
                sValues=regMissing.LeftColumn().getString();
                sValues+=regMissing.MiddleColumn().getString();
                sValues+=colMissing.getString();
            }

            regionsNew[regNumberTrue]=Region(sValues, true);
        }
        grid=Grid(regionsNew[0], regionsNew[1], regionsNew[2], regionsNew[3], regionsNew[4], regionsNew[5], regionsNew[6], regionsNew[7], regionsNew[8]);
    }

    return change;
}
