#include "terrainGrid.h"

Grid gridInit(FILE *terrain) {
    Grid grid;
    
    grid.width      = 0; // Dimensions
    grid.height     = 0;
    grid.entry[0]   = 0; // Entry point
    grid.entry[1]   = 0;
    grid.exit[0]    = 0; // Exit point
    grid.exit[1]    = 0;
    grid.cells      = NULL;

    grid.cells = terrainRead(terrain, &grid.width, &grid.height, grid.entry, grid.exit);

    return grid;
}

Grid gridDelete(Grid grid) {
    grid.width      = 0;
    grid.height     = 0;
    grid.entry[0]   = 0;
    grid.entry[1]   = 0;
    grid.exit[0]    = 0;
    grid.exit[1]    = 0;
    free(grid.cells);
    grid.cells = NULL;
    
    return grid;
}
