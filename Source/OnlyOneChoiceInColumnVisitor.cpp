
#include "OnlyOneChoiceInColumnVisitor.h"

OnlyOneChoiceInColumnVisitor::OnlyOneChoiceInColumnVisitor() {}

bool OnlyOneChoiceInColumnVisitor::Visit(Grid &grid) {
    bool change=false;

    RegionHolder region1;
    RegionHolder region2;
    RegionHolder region3;

    //Changement des 3 premieres colonnes

    region1=grid.NO();
    region2=grid.O();
    region3=grid.SO();

    ColumnHolder column1=region1.LeftColumn();
    ColumnHolder column2=region2.LeftColumn();
    ColumnHolder column3=region3.LeftColumn();
    LastCellFinder cellFinder1(column1, column2, column3);
    change=cellFinder1.fill()||change;

    ColumnHolder column4=region1.MiddleColumn();
    ColumnHolder column5=region2.MiddleColumn();
    ColumnHolder column6=region3.MiddleColumn();
    LastCellFinder cellFinder2(column4, column5, column6);
    change=cellFinder2.fill()||change;

    ColumnHolder column7=region1.RightColumn();
    ColumnHolder column8=region2.RightColumn();
    ColumnHolder column9=region3.RightColumn();
    LastCellFinder cellFinder3(column7, column8, column9);
    change=cellFinder3.fill()||change;

    Region region1New((column1.value()+column4.value())+column7.value(), true);
    Region region2New((column2.value()+column5.value())+column8.value(), true);
    Region region3New((column3.value()+column6.value())+column9.value(), true);

    //Changement des 3 colonnes suivantes

    region1=grid.N();
    region2=grid.C();
    region3=grid.S();

    column1=region1.LeftColumn();
    column2=region2.LeftColumn();
    column3=region3.LeftColumn();
    LastCellFinder cellFinder4(column1, column2, column3);
    change=cellFinder1.fill()||change;

    column4=region1.MiddleColumn();
    column5=region2.MiddleColumn();
    column6=region3.MiddleColumn();
    LastCellFinder cellFinder5(column4, column5, column6);
    change=cellFinder2.fill()||change;

    column7=region1.RightColumn();
    column8=region2.RightColumn();
    column9=region3.RightColumn();
    LastCellFinder cellFinder6(column7, column8, column9);
    change=cellFinder3.fill()||change;

    Region region4New((column1.value()+column4.value())+column7.value(), true);
    Region region5New((column2.value()+column5.value())+column8.value(), true);
    Region region6New((column3.value()+column6.value())+column9.value(), true);

    //Changement des 3 dernieres colonnes

    region1=grid.NE();
    region2=grid.E();
    region3=grid.SE();

    column1=region1.LeftColumn();
    column2=region2.LeftColumn();
    column3=region3.LeftColumn();
    LastCellFinder cellFinder7(column1, column2, column3);
    change=cellFinder1.fill()||change;

    column4=region1.MiddleColumn();
    column5=region2.MiddleColumn();
    column6=region3.MiddleColumn();
    LastCellFinder cellFinder8(column4, column5, column6);
    change=cellFinder2.fill()||change;

    column7=region1.RightColumn();
    column8=region2.RightColumn();
    column9=region3.RightColumn();
    LastCellFinder cellFinder9(column7, column8, column9);
    change=cellFinder3.fill()||change;

    Region region7New((column1.value()+column4.value())+column7.value(), true);
    Region region8New((column2.value()+column5.value())+column8.value(), true);
    Region region9New((column3.value()+column6.value())+column9.value(), true);

    // On reconstruit la grille
    grid=Grid(region1New, region4New, region7New, region2New, region5New, region8New, region3New, region6New, region9New);

    return change;


}
