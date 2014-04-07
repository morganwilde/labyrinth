#include "terrainRead.h"

typedef struct Grid {
    int     width,      // Horizontal length
            height,     // Vertical length
            entry[2],   // Point of entry [0] - x, [1] - y
            exit[2];    // Point of exit [0] - x, [1] - y
    char    **cells;    // 2D grid of terrain tiles
} Grid;

Grid gridInit(FILE *terrain);
Grid gridDelete(Grid grid);
