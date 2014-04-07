all: library/main.c \
    library/terrainQueue.c \
    library/terrainGrid.c \
    library/terrainGridPrint.c \
    library/terrainRead.c \
    library/debug.c
	gcc library/main.c \
	    library/terrainQueue.c \
	    library/terrainGrid.c \
	    library/terrainGridPrint.c \
	    library/terrainRead.c \
	    library/debug.c \
	    -o main
