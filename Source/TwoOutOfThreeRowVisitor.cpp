
#include "TwoOutOfThreeRowVisitor.h"

TwoOutOfThreeRowVisitor::TwoOutOfThreeRowVisitor() {}

bool TwoOutOfThreeRowVisitor::Visit(Grid &grid) {
    bool change=false;
    int count=0;
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

    // Regions du haut

    for (int i=1; i<=9; i++) {//On essaye les chiffres un par un
        region1=grid.NO();
        region2=grid.N();
        region3=grid.NE();
        // TODO char iValue = to_string(i)[0];
        char iValue = i+'0';
        count=region1.isValuePresent(iValue)+region2.isValuePresent(iValue)+region3.isValuePresent(iValue);//On compte le nombre d'occurence du chiffre i dans les 3 regions.
        if (count==2) {//Si le chiffre apparait 2 fois, on execute la strategie
            RegionHolder regMissing;
            RegionHolder reg1;
            RegionHolder reg2;
            RowHolder row1;
            RowHolder row2;
            RowHolder rowMissing;
            int regNumber = 0;
            int rowNumber = 0;

            if (!region1.isValuePresent(iValue)) {//On cherche la region ou le chiffre est manquant
                regNumber=1;
                regMissing=region1;
                reg1=region2;
                reg2=region3;
            }
            else if (!region2.isValuePresent(iValue)) {
                regNumber=2;
                regMissing=region2;
                reg1=region1;
                reg2=region3;
            }
            else {
                regNumber=3;
                regMissing=region3;
                reg1=region1;
                reg2=region2;
            }

            // On cherche la ligne ou le chiffre est manquant
            if ((reg1.TopRow().isValuePresent(iValue)&&reg2.BottomRow().isValuePresent(iValue))||(reg2.TopRow().isValuePresent(iValue)&&reg1.BottomRow().isValuePresent(iValue))) {
                rowMissing=regMissing.MiddleRow();
                rowNumber=2;
            }
            else if ((reg1.TopRow().isValuePresent(iValue)&&reg2.MiddleRow().isValuePresent(iValue))||(reg1.MiddleRow().isValuePresent(iValue)&&reg2.TopRow().isValuePresent(iValue))) {
                rowMissing=regMissing.BottomRow();
                rowNumber=3;
            }
            else {
                rowMissing=regMissing.TopRow();
                rowNumber=1;
            }

            int count2=0;//On compte le nombre de cases vides dans la ligne en question
            if (rowMissing.G().isEmpty()) count2++;
            if (rowMissing.C().isEmpty()) count2++;
            if (rowMissing.D().isEmpty()) count2++;

            if (count2==1) {//Si une seule case est vide on la remplit facilement directement
                if (rowMissing.G().isEmpty()) {
                    rowMissing.cell1=Cell(iValue);
                }
                else if (rowMissing.C().isEmpty()) {
                    rowMissing.cell2=Cell(iValue);
                }
                else {
                    rowMissing.cell3=Cell(iValue);
                }
                change=true;
            }
            else if (count2==2||count2==3) {//Si 2 ou 3 cases sont vides, on regarde dans les colonnes correspondantes si la valeur est presente a l'aide d'un ValueEliminator pour chaque colonne
                ValueEliminator valEliminatorG;
                ValueEliminator valEliminatorC;
                ValueEliminator valEliminatorD;
                if (regNumber==1) {
                    grid.NO().LeftColumn().flagValues(valEliminatorG);
                    grid.O().LeftColumn().flagValues(valEliminatorG);
                    grid.SO().LeftColumn().flagValues(valEliminatorG);
                    grid.NO().MiddleColumn().flagValues(valEliminatorC);
                    grid.O().MiddleColumn().flagValues(valEliminatorC);
                    grid.SO().MiddleColumn().flagValues(valEliminatorC);
                    grid.NO().RightColumn().flagValues(valEliminatorD);
                    grid.O().RightColumn().flagValues(valEliminatorD);
                    grid.SO().RightColumn().flagValues(valEliminatorD);
                }
                else if (regNumber==2) {
                    grid.N().LeftColumn().flagValues(valEliminatorG);
                    grid.C().LeftColumn().flagValues(valEliminatorG);
                    grid.S().LeftColumn().flagValues(valEliminatorG);
                    grid.N().MiddleColumn().flagValues(valEliminatorC);
                    grid.C().MiddleColumn().flagValues(valEliminatorC);
                    grid.S().MiddleColumn().flagValues(valEliminatorC);
                    grid.N().RightColumn().flagValues(valEliminatorD);
                    grid.C().RightColumn().flagValues(valEliminatorD);
                    grid.S().RightColumn().flagValues(valEliminatorD);
                }
                else {
                    grid.NE().LeftColumn().flagValues(valEliminatorG);
                    grid.E().LeftColumn().flagValues(valEliminatorG);
                    grid.SE().LeftColumn().flagValues(valEliminatorG);
                    grid.NE().MiddleColumn().flagValues(valEliminatorC);
                    grid.E().MiddleColumn().flagValues(valEliminatorC);
                    grid.SE().MiddleColumn().flagValues(valEliminatorC);
                    grid.NE().RightColumn().flagValues(valEliminatorD);
                    grid.E().RightColumn().flagValues(valEliminatorD);
                    grid.SE().RightColumn().flagValues(valEliminatorD);
                }
                if (valEliminatorG.missingValues[i-1]==true) {//Ensuite, en fonction de si la valeur est presente dans chaque colonne, on sait quelle case on peut remplir
                    if (valEliminatorC.missingValues[i-1]==true||rowMissing.cell2.isEmpty()==false) {
                        rowMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorD.missingValues[i-1]==true||rowMissing.cell3.isEmpty()==false) {
                        rowMissing.cell2=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorC.missingValues[i-1]==true) {
                    if (valEliminatorG.missingValues[i-1]==true||rowMissing.cell1.isEmpty()==false) {
                        rowMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorD.missingValues[i-1]==true||rowMissing.cell3.isEmpty()==false) {
                        rowMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorD.missingValues[i-1]==true) {
                    if (valEliminatorG.missingValues[i-1]==true||rowMissing.cell1.isEmpty()==false) {
                        rowMissing.cell2=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorC.missingValues[i-1]==true||rowMissing.cell2.isEmpty()==false) {
                        rowMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
            }

            string sValues;//Ensuite on reconstruit la region modifiee
            if (rowNumber==1) {
                sValues=rowMissing.getString();
                sValues+=regMissing.MiddleRow().getString();
                sValues+=regMissing.BottomRow().getString();
            }
            else if (rowNumber==2) {
                sValues=regMissing.TopRow().getString();
                sValues+=rowMissing.getString();
                sValues+=regMissing.BottomRow().getString();
            }
            else {
                sValues=regMissing.TopRow().getString();
                sValues+=regMissing.MiddleRow().getString();
                sValues+=rowMissing.getString();
            }
            regionsNew[regNumber-1]=Region(sValues);
        }
        //Ensuite on reconstruit la grille a partir des nouvelles regions
        grid=Grid(regionsNew[0], regionsNew[1], regionsNew[2], regionsNew[3], regionsNew[4], regionsNew[5], regionsNew[6], regionsNew[7], regionsNew[8]);
    }

    //regions du milieu

    for (int i=1; i<=9; i++) {
        region1=grid.O();
        region2=grid.C();
        region3=grid.E();
        // TODO char iValue = to_string(i)[0];
        char iValue = i+'0';
        count=region1.isValuePresent(iValue)+region2.isValuePresent(iValue)+region3.isValuePresent(iValue);
        if (count==2) {
            RegionHolder regMissing;
            RegionHolder reg1;
            RegionHolder reg2;
            RowHolder row1;
            RowHolder row2;
            RowHolder rowMissing;
            int regNumber = 0;
            int rowNumber = 0;

            if (!region1.isValuePresent(iValue)) {
                regNumber=1;
                regMissing=region1;
                reg1=region2;
                reg2=region3;
            }
            else if (!region2.isValuePresent(iValue)) {
                regNumber=2;
                regMissing=region2;
                reg1=region1;
                reg2=region3;
            }
            else {
                regNumber=3;
                regMissing=region3;
                reg1=region1;
                reg2=region2;
            }

            if ((reg1.TopRow().isValuePresent(iValue)&&reg2.BottomRow().isValuePresent(iValue))||(reg2.TopRow().isValuePresent(iValue)&&reg1.BottomRow().isValuePresent(iValue))) {
                rowMissing=regMissing.MiddleRow();
                rowNumber=2;
            }
            else if ((reg1.TopRow().isValuePresent(iValue)&&reg2.MiddleRow().isValuePresent(iValue))||(reg1.MiddleRow().isValuePresent(iValue)&&reg2.TopRow().isValuePresent(iValue))) {
                rowMissing=regMissing.BottomRow();
                rowNumber=3;
            }
            else {
                rowMissing=regMissing.TopRow();
                rowNumber=1;
            }

            int count2=0;
            if (rowMissing.G().isEmpty()) count2++;
            if (rowMissing.C().isEmpty()) count2++;
            if (rowMissing.D().isEmpty()) count2++;

            if (count2==1) {
                if (rowMissing.G().isEmpty()) rowMissing.cell1=Cell(iValue);
                if (rowMissing.C().isEmpty()) rowMissing.cell2=Cell(iValue);
                if (rowMissing.D().isEmpty()) rowMissing.cell3=Cell(iValue);
                change=true;
            }
            else if (count2==2||count2==3) {
                ValueEliminator valEliminatorG;
                ValueEliminator valEliminatorC;
                ValueEliminator valEliminatorD;
                if (regNumber==1) {
                    grid.NO().LeftColumn().flagValues(valEliminatorG);
                    grid.O().LeftColumn().flagValues(valEliminatorG);
                    grid.SO().LeftColumn().flagValues(valEliminatorG);
                    grid.NO().MiddleColumn().flagValues(valEliminatorC);
                    grid.O().MiddleColumn().flagValues(valEliminatorC);
                    grid.SO().MiddleColumn().flagValues(valEliminatorC);
                    grid.NO().RightColumn().flagValues(valEliminatorD);
                    grid.O().RightColumn().flagValues(valEliminatorD);
                    grid.SO().RightColumn().flagValues(valEliminatorD);
                }
                else if (regNumber==2) {
                    grid.N().LeftColumn().flagValues(valEliminatorG);
                    grid.C().LeftColumn().flagValues(valEliminatorG);
                    grid.S().LeftColumn().flagValues(valEliminatorG);
                    grid.N().MiddleColumn().flagValues(valEliminatorC);
                    grid.C().MiddleColumn().flagValues(valEliminatorC);
                    grid.S().MiddleColumn().flagValues(valEliminatorC);
                    grid.N().RightColumn().flagValues(valEliminatorD);
                    grid.C().RightColumn().flagValues(valEliminatorD);
                    grid.S().RightColumn().flagValues(valEliminatorD);
                }
                else {
                    grid.NE().LeftColumn().flagValues(valEliminatorG);
                    grid.E().LeftColumn().flagValues(valEliminatorG);
                    grid.SE().LeftColumn().flagValues(valEliminatorG);
                    grid.NE().MiddleColumn().flagValues(valEliminatorC);
                    grid.E().MiddleColumn().flagValues(valEliminatorC);
                    grid.SE().MiddleColumn().flagValues(valEliminatorC);
                    grid.NE().RightColumn().flagValues(valEliminatorD);
                    grid.E().RightColumn().flagValues(valEliminatorD);
                    grid.SE().RightColumn().flagValues(valEliminatorD);
                }
                if (valEliminatorG.missingValues[i-1]==true) {
                    if (valEliminatorC.missingValues[i-1]==true||rowMissing.cell2.isEmpty()==false) {
                        rowMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorD.missingValues[i-1]==true||rowMissing.cell3.isEmpty()==false) {
                        rowMissing.cell2=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorC.missingValues[i-1]==true) {
                    if (valEliminatorG.missingValues[i-1]==true||rowMissing.cell1.isEmpty()==false) {
                        rowMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorD.missingValues[i-1]==true||rowMissing.cell3.isEmpty()==false) {
                        rowMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorD.missingValues[i-1]==true) {
                    if (valEliminatorG.missingValues[i-1]==true||rowMissing.cell1.isEmpty()==false) {
                        rowMissing.cell2=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorC.missingValues[i-1]==true||rowMissing.cell2.isEmpty()==false) {
                        rowMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
            }

            string sValues;
            if (rowNumber==1) {
                sValues=rowMissing.getString();
                sValues+=regMissing.MiddleRow().getString();
                sValues+=regMissing.BottomRow().getString();
            }
            else if (rowNumber==2) {
                sValues=regMissing.TopRow().getString();
                sValues+=rowMissing.getString();
                sValues+=regMissing.BottomRow().getString();
            }
            else {
                sValues=regMissing.TopRow().getString();
                sValues+=regMissing.MiddleRow().getString();
                sValues+=rowMissing.getString();
            }
            regionsNew[regNumber-1+3]=Region(sValues);
        }

        grid=Grid(regionsNew[0], regionsNew[1], regionsNew[2], regionsNew[3], regionsNew[4], regionsNew[5], regionsNew[6], regionsNew[7], regionsNew[8]);
    }

    //region du bas

    for (int i=1; i<=9; i++) {
        region1=grid.SO();
        region2=grid.S();
        region3=grid.SE();

        // TODO char iValue = to_string(i)[0];
        char iValue = i+'0';
        count=region1.isValuePresent(iValue)+region2.isValuePresent(iValue)+region3.isValuePresent(iValue);
        if (count==2) {
            RegionHolder regMissing;
            RegionHolder reg1;
            RegionHolder reg2;
            RowHolder row1;
            RowHolder row2;
            RowHolder rowMissing;
            int regNumber = 0;
            int rowNumber = 0;

            if (!region1.isValuePresent(iValue)) {
                regNumber=1;
                regMissing=region1;
                reg1=region2;
                reg2=region3;
            }
            else if (!region2.isValuePresent(iValue)) {
                regNumber=2;
                regMissing=region2;
                reg1=region1;
                reg2=region3;
            }
            else {
                regNumber=3;
                regMissing=region3;
                reg1=region1;
                reg2=region2;
            }

            if ((reg1.TopRow().isValuePresent(iValue)&&reg2.BottomRow().isValuePresent(iValue))||(reg2.TopRow().isValuePresent(iValue)&&reg1.BottomRow().isValuePresent(iValue))) {
                rowMissing=regMissing.MiddleRow();
                rowNumber=2;
            }
            else if ((reg1.TopRow().isValuePresent(iValue)&&reg2.MiddleRow().isValuePresent(iValue))||(reg1.MiddleRow().isValuePresent(iValue)&&reg2.TopRow().isValuePresent(iValue))) {
                rowMissing=regMissing.BottomRow();
                rowNumber=3;
            }
            else {
                rowMissing=regMissing.TopRow();
                rowNumber=1;
            }

            int count2=0;
            if (rowMissing.G().isEmpty()) count2++;
            if (rowMissing.C().isEmpty()) count2++;
            if (rowMissing.D().isEmpty()) count2++;

            if (count2==1) {
                if (rowMissing.G().isEmpty()) rowMissing.cell1=Cell(iValue);
                if (rowMissing.C().isEmpty()) rowMissing.cell2=Cell(iValue);
                if (rowMissing.D().isEmpty()) rowMissing.cell3=Cell(iValue);
                change=true;
            }
            else if (count2==2||count2==3) {
                ValueEliminator valEliminatorG;
                ValueEliminator valEliminatorC;
                ValueEliminator valEliminatorD;
                if (regNumber==1) {
                    grid.NO().LeftColumn().flagValues(valEliminatorG);
                    grid.O().LeftColumn().flagValues(valEliminatorG);
                    grid.SO().LeftColumn().flagValues(valEliminatorG);
                    grid.NO().MiddleColumn().flagValues(valEliminatorC);
                    grid.O().MiddleColumn().flagValues(valEliminatorC);
                    grid.SO().MiddleColumn().flagValues(valEliminatorC);
                    grid.NO().RightColumn().flagValues(valEliminatorD);
                    grid.O().RightColumn().flagValues(valEliminatorD);
                    grid.SO().RightColumn().flagValues(valEliminatorD);
                }
                else if (regNumber==2) {
                    grid.N().LeftColumn().flagValues(valEliminatorG);
                    grid.C().LeftColumn().flagValues(valEliminatorG);
                    grid.S().LeftColumn().flagValues(valEliminatorG);
                    grid.N().MiddleColumn().flagValues(valEliminatorC);
                    grid.C().MiddleColumn().flagValues(valEliminatorC);
                    grid.S().MiddleColumn().flagValues(valEliminatorC);
                    grid.N().RightColumn().flagValues(valEliminatorD);
                    grid.C().RightColumn().flagValues(valEliminatorD);
                    grid.S().RightColumn().flagValues(valEliminatorD);
                }
                else {
                    grid.NE().LeftColumn().flagValues(valEliminatorG);
                    grid.E().LeftColumn().flagValues(valEliminatorG);
                    grid.SE().LeftColumn().flagValues(valEliminatorG);
                    grid.NE().MiddleColumn().flagValues(valEliminatorC);
                    grid.E().MiddleColumn().flagValues(valEliminatorC);
                    grid.SE().MiddleColumn().flagValues(valEliminatorC);
                    grid.NE().RightColumn().flagValues(valEliminatorD);
                    grid.E().RightColumn().flagValues(valEliminatorD);
                    grid.SE().RightColumn().flagValues(valEliminatorD);
                }
                if (valEliminatorG.missingValues[i-1]==true) {
                    if (valEliminatorC.missingValues[i-1]==true||rowMissing.cell2.isEmpty()==false) {
                        rowMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorD.missingValues[i-1]==true||rowMissing.cell3.isEmpty()==false) {
                        rowMissing.cell2=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorC.missingValues[i-1]==true) {
                    if (valEliminatorG.missingValues[i-1]==true||rowMissing.cell1.isEmpty()==false) {
                        rowMissing.cell3=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorD.missingValues[i-1]==true||rowMissing.cell3.isEmpty()==false) {
                        rowMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
                else if (valEliminatorD.missingValues[i-1]==true) {
                    if (valEliminatorG.missingValues[i-1]==true||rowMissing.cell1.isEmpty()==false) {
                        rowMissing.cell2=Cell(iValue);
                        change=true;
                    }
                    else if (valEliminatorC.missingValues[i-1]==true||rowMissing.cell2.isEmpty()==false) {
                        rowMissing.cell1=Cell(iValue);
                        change=true;
                    }
                }
            }

            string sValues;
            if (rowNumber==1) {
                sValues=rowMissing.getString();
                sValues+=regMissing.MiddleRow().getString();
                sValues+=regMissing.BottomRow().getString();
            }
            else if (rowNumber==2) {
                sValues=regMissing.TopRow().getString();
                sValues+=rowMissing.getString();
                sValues+=regMissing.BottomRow().getString();
            }
            else {
                sValues=regMissing.TopRow().getString();
                sValues+=regMissing.MiddleRow().getString();
                sValues+=rowMissing.getString();
            }

            regionsNew[regNumber-1+6]=Region(sValues);
        }

        grid=Grid(regionsNew[0], regionsNew[1], regionsNew[2], regionsNew[3], regionsNew[4], regionsNew[5], regionsNew[6], regionsNew[7], regionsNew[8]);
    }


    return change;
}

