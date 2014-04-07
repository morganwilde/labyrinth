#include "interface.h"

char *hideExtension(char *filename, char *extension) {
    char *temp = malloc(sizeof(char) * 1);
    int i = 0;
    while (filename[i] != '\0') {
        if (filename[i] != extension[0]) {
            temp[i] = filename[i];
            temp = realloc(temp, sizeof(char) * (i+1));
            i++;
        } else {
            break;
        }
    }
    temp[i] = '\0';

    return temp;
}

char *labyrinthFile(char *labName) {
    // Look for *.labyrinth files in pwd
    DIR *directory = opendir("data/");
    struct dirent *dirStream = readdir(directory);;
    char **labyrinths = malloc(sizeof(char *) * 1);;

    int counter = 0;
    while (dirStream) {
        if ((dirStream = readdir(directory)) != NULL) {
            char *found = strstr(dirStream->d_name, ".terr");
            if (found != NULL) {
                // Save as an option
                labyrinths = realloc(labyrinths, sizeof(char *) * (counter+1));
                labyrinths[counter] = calloc(strlen(dirStream->d_name)+1, sizeof(char));
                strcpy(labyrinths[counter], dirStream->d_name);

                // Print the UI
                char *filename = malloc(sizeof(char) * 0);
                filename = hideExtension(dirStream->d_name, found);
                printf("%d. \x1B[32m%s\x1B[0m\n", (counter+1), filename);
                counter++;
            }
        }
    }
    closedir(directory);

    int pick;
    printf("Pick your labyrinth: ");
    // TODO replace this with AVIR
    scanf("%d", &pick);
    //printf("extension labyrinth[%d]: [%s]\n", pick, labyrinths[pick-1]);
    char *pickFilename = hideExtension(labyrinths[pick-1], strstr(labyrinths[pick-1], ".terr"));

    labName = realloc(labName, sizeof(char) * strlen(pickFilename));
    strcpy(labName, pickFilename);

    printf("Walking the '%s' labyrinth...\n", pickFilename);

    return labyrinths[pick-1];
}
