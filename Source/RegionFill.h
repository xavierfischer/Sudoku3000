#ifndef __Sudoku__RegionFill__
#define __Sudoku__RegionFill__

#include <stdio.h>
#include "Region.h"

class RegionFill {

public:
    RegionFill();
    RegionFill(Region &reg);
    bool fill();

private:
    Region &region;
};
#endif /* defined(__Sudoku__RegionFill__) */
