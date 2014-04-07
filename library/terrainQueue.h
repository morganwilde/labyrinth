#include <stdlib.h>

#ifndef TERRAIN_GRID_H
#define TERRAIN_GRID_H
#include "terrainGrid.h"
#endif

#ifndef DEBUG_H
#define DEBUG_H
#include "debug.h"
#endif

#define WALL '*'

typedef struct Queue {
    int x,
        y,
        counter;
} Queue;

Queue *queueInit(int x, int y, int counter);
Queue **queueMakeFrom(Grid grid, int *steps);

int queueIn(Queue **queue, Queue *needle, int count);
void queueAppend(Queue ***queue, int x, int y, int countT, int *count);
void queueRemove(Queue ***queue, Queue *needle, int *count);
char queueTile(Queue *queue, Grid grid, int x, int y);
void queuePrint(Queue **queue, int count);

Queue **queueWalk(Queue **queue, int count, int *walks);
