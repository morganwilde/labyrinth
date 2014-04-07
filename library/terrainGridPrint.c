#include "terrainGridPrint.h"

void terrainGridPrint(Grid grid) {
    int v, h;
    for (v = 0; v < grid.height; v++) {
        for (h = 0; h < grid.width; h++) {
            printf("%c", grid.cells[v][h]);
        }
        printf("\n");
    }
}
