//#define DEBUG

// Debug gridInit() 
#ifdef DEBUG
#define DEBUG_GRID_INIT {                                           \
    printf("Debugging gridInit()\n");                               \
    printf(" - width: %d\n", grid.width);                           \
    printf(" - height: %d\n", grid.height);                         \
    printf(" - grid: %p\n", grid.cells);                            \
    printf(" - entry: (%d, %d)\n", grid.entry[0], grid.entry[1]);   \
    printf(" - exit: (%d, %d)\n", grid.exit[0], grid.exit[1]);      \
}
#endif
#ifndef DEBUG
#define DEBUG_GRID_INIT {}
#endif

// Debug queueInit()
#ifdef DEBUG
#define DEBUG_QUEUE_INIT(queue, i) { \
    printf("Debugging queueInit()\n"); \
    printf(" - queue[%d]->x: %d\n", i, queue[i]->x); \
    printf(" - queue[%d]->y: %d\n", i, queue[i]->y); \
    printf(" - queue[%d]->counter: %d\n", i, queue[i]->counter); \
}
#endif
#ifndef DEBUG
#define DEBUG_QUEUE_INIT(queue, i) {}
#endif

#ifdef DEBUG
#define DEBUG_QUEUE_PRINT(queue, countQ) { \
    queuePrint(queue, countQ); \
}
#endif
#ifndef DEBUG
#define DEBUG_QUEUE_PRINT(queue, countQ) {}
#endif
