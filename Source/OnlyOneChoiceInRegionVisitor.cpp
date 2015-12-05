
#include "OnlyOneChoiceInRegionVisitor.h"


OnlyOneChoiceInRegionVisitor::OnlyOneChoiceInRegionVisitor() {}

bool OnlyOneChoiceInRegionVisitor::Visit(Grid &grid) {
    bool change=false;

    //Changement des regions une par une

    RegionHolder region=grid.NO();
    RowHolder row1=region.TopRow();
    RowHolder row2=region.MiddleRow();
    RowHolder row3=region.BottomRow();
    LastCellFinder cellFinder1(row1, row2, row3);
    change=cellFinder1.fill()||change;
    Region region1New((row1.value()+row2.value())+row3.value());

    region=grid.N();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder2(row1, row2, row3);
    change=cellFinder2.fill()||change;
    Region region2New((row1.value()+row2.value())+row3.value());

    region=grid.NE();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder3(row1, row2, row3);
    change=cellFinder3.fill()||change;
    Region region3New((row1.value()+row2.value())+row3.value());

    region=grid.O();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder4(row1, row2, row3);
    change=cellFinder4.fill()||change;
    Region region4New((row1.value()+row2.value())+row3.value());

    region=grid.C();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder5(row1, row2, row3);
    change=cellFinder5.fill()||change;
    Region region5New((row1.value()+row2.value())+row3.value());

    region=grid.E();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder6(row1, row2, row3);
    change=cellFinder6.fill()||change;
    Region region6New((row1.value()+row2.value())+row3.value());

    region=grid.SO();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder7(row1, row2, row3);
    change=cellFinder7.fill()||change;
    Region region7New((row1.value()+row2.value())+row3.value());

    region=grid.S();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder8(row1, row2, row3);
    change=cellFinder8.fill()||change;
    Region region8New((row1.value()+row2.value())+row3.value());

    region=grid.SE();
    row1=region.TopRow();
    row2=region.MiddleRow();
    row3=region.BottomRow();
    LastCellFinder cellFinder9(row1, row2, row3);
    change=cellFinder9.fill()||change;
    Region region9New((row1.value()+row2.value())+row3.value());

    //On reconstruit la grille finale
    grid=Grid(region1New, region2New, region3New, region4New, region5New, region6New, region7New, region8New, region9New);

    return change;

}
