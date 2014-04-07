#include "terrainRead.h"

char **terrainRead(FILE *terrain, int *width, int *height, int entry[], int exit[]) {
    // Containers
    char    **grid  = NULL,                         // A 2D grid
            c       = 0;                            // Current char read
    int     scan    = fscanf(terrain, "%c", &c);    // Status of fscanf
            *width  = 0;                            // How wide is the grid
            *height = 0;                            // How tall is the grid

    // Start reading
    int     h = 0, // Horizontal index
            v = 0; // Vertical index

    while (scan != EOF) {
        if (grid == NULL) {
            // Init the grid
            grid    = malloc(sizeof(char *));   // Vertical
            grid[v] = calloc(sizeof(char), 1);     // Horizontal
        } else {
            // Start filling the grid up
            if (c != '\n') {
                // Check of entry/exit tiles
                // TODO custom entry/exit tiles
                if (c == '+') {
                    entry[0] = h;
                    entry[1] = v;
                }
                if (c == '-') {
                    exit[0] = h;
                    exit[1] = v;
                }
                // Expand width
                h++;
                if (*width < h) {
                    *width = h;
                }
                if (!*height) {
                    // Add more memory to the grid, since this is the 1st line
                    grid[v] = realloc(grid[v], sizeof(char) * h);
                }
                // Save current tile aka c
                grid[v][h-1] = c;
            } else {
                // Expand height
                v++;
                if (*height < v) {
                    *height = v;
                }
                // Restart horizontal index;
                h = 0;
                // Add more memory to the grid
                grid    = realloc(grid, sizeof(char *) * (v + 1));
                grid[v] = calloc(sizeof(char), (*width + 1));
            }
            // Scan new char
            scan = fscanf(terrain, "%c", &c);
        }
    }

    // Adjust height for line numbering
    if (grid) {
        (*height)++;
    }

    return grid;
}
