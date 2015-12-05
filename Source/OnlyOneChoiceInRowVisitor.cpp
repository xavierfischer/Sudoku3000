
#include "OnlyOneChoiceInRowVisitor.h"

OnlyOneChoiceInRowVisitor::OnlyOneChoiceInRowVisitor() {}

bool OnlyOneChoiceInRowVisitor::Visit(Grid &grid) {
    bool change=false;

    RegionHolder region1;
    RegionHolder region2;
    RegionHolder region3;

    //On visite d'abord les 3 premieres lignes

    region1=grid.NO();
    region2=grid.N();
    region3=grid.NE();

    RowHolder row1=region1.TopRow();
    RowHolder row2=region2.TopRow();
    RowHolder row3=region3.TopRow();
    LastCellFinder cellFinder1(row1, row2, row3);
    change=cellFinder1.fill()||change;

    RowHolder row4=region1.MiddleRow();
    RowHolder row5=region2.MiddleRow();
    RowHolder row6=region3.MiddleRow();
    LastCellFinder cellFinder2(row4, row5, row6);
    change=cellFinder2.fill()||change;

    RowHolder row7=region1.BottomRow();
    RowHolder row8=region2.BottomRow();
    RowHolder row9=region3.BottomRow();
    LastCellFinder cellFinder3(row7, row8, row9);
    change=cellFinder3.fill()||change;

    Region region1New((row1.value()+row4.value())+row7.value());
    Region region2New((row2.value()+row5.value())+row8.value());
    Region region3New((row3.value()+row6.value())+row9.value());

    //On visite ensuite les 3 lignes suivantes

    region1=grid.O();
    region2=grid.C();
    region3=grid.E();

    row1=region1.TopRow();
    row2=region2.TopRow();
    row3=region3.TopRow();
    LastCellFinder cellFinder4(row1, row2, row3);
    change=cellFinder4.fill()||change;

    row4=region1.MiddleRow();
    row5=region2.MiddleRow();
    row6=region3.MiddleRow();
    LastCellFinder cellFinder5(row4, row5, row6);
    change=cellFinder5.fill()||change;

    row7=region1.BottomRow();
    row8=region2.BottomRow();
    row9=region3.BottomRow();
    LastCellFinder cellFinder6(row7, row8, row9);
    change=cellFinder6.fill()||change;

    Region region4New((row1.value()+row4.value())+row7.value());
    Region region5New((row2.value()+row5.value())+row8.value());
    Region region6New((row3.value()+row6.value())+row9.value());

    //On visite les 3 dernieres lignes

    region1=grid.SO();
    region2=grid.S();
    region3=grid.SE();

    row1=region1.TopRow();
    row2=region2.TopRow();
    row3=region3.TopRow();
    LastCellFinder cellFinder7(row1, row2, row3);
    change=cellFinder7.fill()||change;

    row4=region1.MiddleRow();
    row5=region2.MiddleRow();
    row6=region3.MiddleRow();
    LastCellFinder cellFinder8(row4, row5, row6);
    change=cellFinder8.fill()||change;

    row7=region1.BottomRow();
    row8=region2.BottomRow();
    row9=region3.BottomRow();
    LastCellFinder cellFinder9(row7, row8, row9);
    change=cellFinder9.fill()||change;

    Region region7New((row1.value()+row4.value())+row7.value());
    Region region8New((row2.value()+row5.value())+row8.value());
    Region region9New((row3.value()+row6.value())+row9.value());

    // On reconstruit la grille a partir des regions construites
    grid=Grid(region1New, region2New, region3New, region4New, region5New, region6New, region7New, region8New, region9New);

    return change;


}
