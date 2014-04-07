#include <stdio.h>
#include <stdlib.h>

#ifndef DEBUG_H
#define DEBUG_H
#include "debug.h"
#endif

#ifndef TERRAIN_GRID_H
#define TERRAIN_GRID_H
#include "terrainGrid.h"
#endif

#ifndef TERRAIN_GRID_PRINT_H
#define TERRAIN_GRID_PRINT_H
#include "terrainGridPrint.h"
#endif

#include "terrainQueue.h"
#include "interface.h"

int main(int argc, char **argv) {
	char *terrName = malloc(sizeof(char));
	char *terrainName = labyrinthFile(terrName);
	char url[40] = "data/";
	strcat(url, terrainName);
	FILE *terrain = fopen(url, "r");
    
    if (terrain) {
        //
        // Try to read the terrain into a grid
        //
        Grid grid = gridInit(terrain);
        DEBUG_GRID_INIT;

        //
        // Traverse the terrain if it was loaded
        //
        if (grid.cells != NULL) {
            terrainGridPrint(grid);

            int steps = 0;
            Queue **queue = queueMakeFrom(grid, &steps);
            DEBUG_QUEUE_INIT(queue, 0);
            DEBUG_QUEUE_PRINT(queue, steps);

            if (steps > 0) {
                //
                // Walk the queue backwards
                //
                int walks = 0;
                Queue **walk = queueWalk(queue, steps, &walks);
                printf("road---->\n");
				DEBUG_QUEUE_PRINT(walk, walks);
            }
        }

        // We're done with the grid - delete it
        grid = gridDelete(grid);
        DEBUG_GRID_INIT;

    }

    return 0;
}
