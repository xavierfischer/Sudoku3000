
#ifndef __Sudoku__Grid__
#define __Sudoku__Grid__

#include <stdio.h>
#include "Header.h"
#include "Region.h"
#include "RegionHolder.h"

class Grid {
public:
    Grid();
    Grid(Region NO1, Region N1, Region NE1, Region O1, Region C1, Region E1, Region SO1, Region S1, Region SE1);
    list<Region> regions;
    bool isFull();
    void Accept();
    bool isConsistent();
    void Solve();
    void create();
    bool isEmpty();

    RegionHolder &NO();
    RegionHolder &N();
    RegionHolder &NE();
    RegionHolder &O();
    RegionHolder &C();
    RegionHolder &E();
    RegionHolder &SO();
    RegionHolder &S();
    RegionHolder &SE();
};

#endif /* defined(__Sudoku__Grid__) */
