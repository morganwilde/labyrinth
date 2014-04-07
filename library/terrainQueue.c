#include "terrainQueue.h"

Queue *queueInit(int x, int y, int counter) {
    Queue *queue = malloc(sizeof(Queue));

    queue->x = x;
    queue->y = y;
    queue->counter = counter;

    return queue;
}

Queue **queueMakeFrom(Grid grid, int *steps) {
    // Containers
    Queue   **queue = malloc(sizeof(Queue *)),
            *temp  = NULL; // Holds current focused queue
    char    tile    = 0; // Current grid tile
    int     countQ  = 0, // How many elements in the queue
            countT  = 0; // How many turns taken (counter)

    // Initialize the queue with the exit tile coordinates
    queue[countQ] = queueInit(grid.exit[0], grid.exit[1], countT);
    countQ++;

    // Start traversing the grid
    int i;
    for (i = 0; i < countQ; i++) {
        temp = queue[i];
        countT = temp->counter;
        if (queueTile(temp, grid, 0, 0) == '+') {
            // Exit found !
            queueRemove(&queue, temp, &countQ);
            *steps = countQ;
            return queue;
        } else {
            if (((temp->y-1) >= 0) && (queueTile(temp, grid, 0, -1) != WALL)) {
                // Go south
                queueAppend(&queue, temp->x, temp->y-1, countT+1, &countQ);
            }
            if (((temp->x+1) >= 0) && (queueTile(temp, grid, 1, 0) != WALL)) {
                // Go east
                queueAppend(&queue, temp->x+1, temp->y, countT+1, &countQ);
            }
            if (((temp->y+1) >= 0) && (queueTile(temp, grid, 0, 1) != WALL)) {
                // Go north
                queueAppend(&queue, temp->x, temp->y+1, countT+1, &countQ);
            }
            if (((temp->x-1) >= 0) && (queueTile(temp, grid, -1, 0) != WALL)) {
                // Go west
                queueAppend(&queue, temp->x-1, temp->y, countT+1, &countQ);
            }
        }
    }

    return queue;
}

int queueIn(Queue **queue, Queue *needle, int count) {
    int i;
    for (i = 0; i < count; i++) {
        if (queue[i]->x == needle->x && queue[i]->y == needle->y) {
            // Found it
            if (!(queue[i]->counter >= needle->counter)) {
                //queue[i]->counter = needle->counter;
            }
            return 1;
        }
    }
    return 0;
}

void queueAppend(Queue ***queue, int x, int y, int countT, int *count) {
    Queue *append = queueInit(x, y, countT);
    if (!queueIn(*queue, append, *count)) {
        // This tile is not represented - append it to the queue
        queue[0] = realloc(queue[0], sizeof(Queue *) * (*count + 1));
        queue[0][*count] = append;
        (*count)++;
    } else {
        free(append);
    }
}

void queueRemove(Queue ***queue, Queue *needle, int *count) {
    int i;
    for (i = (*count)-1; i >= 0; i--) {
        if (queue[0][i]->counter >= needle->counter) {
            if (queue[0][i] != needle) {
                if (queue[0][i] > needle) {
                    // After needle
                    free(queue[0][i]);
                } else {
                    // Before needle - move it back
                    free(queue[0][i]);
                    queue[0][i] = queueInit(needle->x, needle->y, needle->counter);
                    //printf("needle->counter:%d\n", queue[0][i]->counter);
                    //needle = queue[0][i];
                }
                (*count)--;
            }
        }
    }
    queue[0] = realloc(queue[0], sizeof(Queue *) * (*count));
}

char queueTile(Queue *queue, Grid grid, int x, int y) {
    return grid.cells[(queue->y)+y][(queue->x)+x];
}

void queuePrint(Queue **queue, int count) {
    int i;
    for (i = 0; i < count; i++) {
        printf(" (%d, %d, %d)", queue[i]->x, queue[i]->y, queue[i]->counter);
    }
    printf("\n");
}

Queue **queueWalk(Queue **queue, int count, int *walks) {
    // Containers
    Queue   **walk    = malloc(sizeof(Queue *)),
            *temp     = queue[count-1];
    int     countW    = 0;

    walk = realloc(walk, sizeof(Queue *) * (countW + 1));
    walk[countW] = queueInit(temp->x, temp->y, temp->counter);
    countW++;

    int i;
    for (i = count-2; i >= 0; i--) {
        if ((queue[i]->counter < temp->counter) && \
            (queue[i]->x+1 == temp->x || queue[i]->x-1 == temp->x || queue[i]->x == temp->x) && \
            (queue[i]->y+1 == temp->y || queue[i]->y-1 == temp->y || queue[i]->y == temp->y)) {
            temp = queue[i];
            countW++;
            walk = realloc(walk, sizeof(Queue *) * (countW + 1));
            walk[countW-1] = queueInit(temp->x, temp->y, temp->counter);
        } else {
            //break;
        }
    }
    (*walks) = countW;
    return walk;
}
