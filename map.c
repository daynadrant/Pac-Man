// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"

extern char *map, *dot_map;
extern int width, height;
extern int num_dots;
extern char tempChar;

void move_actor(int * x, int * y, char direction) {
    //if character is pacman
    if (map[*y * width + *x] == PACMAN) {
        if (direction == UP) { //up
            //make sure pacman doesn't move off the map
            if (*y != 0) {
                //if the spot pacman is moving to is a dot
                if (map[* y * width + * x - width] == DOT) {
                    //eat the dot and replace it with pacman, update his co-ordinates as well
                    map[* y * width + * x - width] = PACMAN;
                    map[* y * width + * x] = EMPTY;
                    //update dot map and decrease #dots by 1
                    dot_map[* y * width + * x - width] = EMPTY;
                    *y = *y - 1;
                    num_dots--;
                    //update dot map
                } else if (map[* y * width + * x - width] == GHOST) {
                    //if pacman moves into a ghost you lose, but this will be detected by check_loss function in the main function
                } else if (map[* y * width + * x - width] == WALL) {
                    //nothing happens b/c he moved into a wall
                } else if (map[* y * width + * x - width] == EMPTY) {
                    //pacman moves up as normal and no dots are affected
                    map[* y * width + * x - width] = PACMAN;
                    map[* y * width + * x] = EMPTY;
                    *y = *y - 1;
                }
            } else {
            }
        } else if (direction == LEFT) { //left
            //make sure pacman doesn't move off the map
            if (*x != 0) {
                if (map[* y * width + * x - 1] == DOT) {
                    map[* y * width + * x - 1] = PACMAN;
                    map[* y * width + * x] = EMPTY;
                    dot_map[* y * width + * x - 1] = EMPTY;
                    *x = *x - 1;
                    num_dots--;
                } else if (map[* y * width + * x - 1] == GHOST) {
                } else if (map[* y * width + * x - 1] == WALL) {
                    //nothing happens
                } else if (map[*y * width + *x - 1] == EMPTY) {
                    map[*y * width + *x - 1] = PACMAN;
                    map[*y * width + *x] = EMPTY;
                    *x = *x - 1;
                }
            } else {}
        } else if (direction == DOWN) { //down
            //make sure pacman doesn't move off the map
            if (*y != height - 1) {
                if (map[*y * width + *x + width] == DOT) {
                    map[*y * width + *x + width] = PACMAN;
                    map[*y * width + *x] = EMPTY;
                    dot_map[*y * width + *x + width] = EMPTY;
                    *y = *y + 1;
                    num_dots--;
                } else if (map[*y * width + *x + width] == GHOST) {
                } else if (map[*y * width + *x + width] == WALL) {
                    //nothing happens
                } else if (map[*y * width + *x + width] == EMPTY)
                {
                    map[*y * width + *x + width] = PACMAN;
                    map[*y * width + *x] = EMPTY;
                    *y = *y + 1;
                }
            } else {}
        } else if (direction == RIGHT) { //right
            //make sure pacman doesn't move off the map
            if (*x != width - 1) {
                if (map[*y * width + *x + 1] == DOT) {
                    map[*y * width + *x + 1] = PACMAN;
                    map[*y * width + *x] = EMPTY;
                    dot_map[*y * width + *x + 1] = EMPTY;
                    *x = *x + 1;
                    num_dots--;
                } else if (map[*y * width + *x + 1] == GHOST) {
                } else if (map[*y * width + *x + 1] == WALL) {
                    //nothing happens
                } else if (map[*y * width + *x + 1] == EMPTY) {
                    map[*y * width + *x + 1] = PACMAN;
                    map[*y * width + *x] = EMPTY;
                    *x = *x + 1;
                }
            } else {}
        }
    } else if (map[*y * width + *x] == GHOST) {
        if (direction == UP) { //up
            map[*y * width + *x - width] = GHOST;
            // replace ghost's old position according to whether dot_map says it was a dot or an empty
            if (dot_map[*y * width + *x] == EMPTY) {
                map[*y * width + *x] = EMPTY;
            } else if (dot_map[*y * width + *x] == DOT) {
                map[*y * width + *x] = DOT;
            }
            *y = *y - 1;
        } else if (direction == LEFT) { //left
            map[*y * width + *x - 1] = GHOST;
            // replace ghost's old position
            if (dot_map[*y * width + *x] == EMPTY) {
                map[*y * width + *x] = EMPTY;
            } else if (dot_map[*y * width + *x] == DOT) {
                map[*y * width + *x] = DOT;
            }
            *x = *x - 1;
        } else if (direction == DOWN) { //down
            map[*y * width + *x + width] = GHOST;
            // replace ghost's old position
            if (dot_map[*y * width + *x] == EMPTY) {
                map[*y * width + *x] = EMPTY;
            } else if (dot_map[*y * width + *x] == DOT) {
                map[*y * width + *x] = DOT;
            }
            *y = *y + 1;
        } else if (direction == RIGHT) { //right
            map[*y * width + *x + 1] = GHOST;
            // replace ghost's old position
            if (dot_map[*y * width + *x] == EMPTY) {
                map[*y * width + *x] = EMPTY;
            } else if (dot_map[*y * width + *x] == DOT) {
                map[*y * width + *x] = DOT;
            }
            *x = *x + 1;
        }
    }
}

int is_wall(int y, int x) {
    int is_wall;
    char wall = map[y * width + x];
    if (wall == WALL) {
        is_wall = YES_WALL;
    } else {
        is_wall = NOT_WALL;
    }
    return is_wall;
}

//function to load the maptxt file
char * load_map(char * filename, int * map_height, int
*map_width) {
    int index = 0;
    //open file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        // File opening failed
        return (char *) ERR_NO_MAP;
    }

    while ((tempChar = fgetc(file)) != EOF) {
        if (tempChar == '\n') {
            //if there's a newline while reading the file increase the map height
            (*map_height)++;
        } else if (tempChar != EMPTY) {
            //if it's detected a character that isn't an empty space, increase the map width
            (*map_width)++;
        }
    }

    //set map width properly
    *map_width = *map_width / *map_height;

    //once dimensions are set, allocate memory for the map and set the map
    rewind(file);

    //allocate memory for the map
    char *tempMap = (char *)malloc((height * width) * sizeof(char));

    //check if it worked
    if (tempMap == NULL) {
        printf("Memory allocation failed");
        fclose(file);
        return NULL;
    }

    //read file character by character and sort them into the array properly
    while ((tempChar = fgetc(file)) != EOF) {
        if (tempChar != '\n' && tempChar != EMPTY) {
            if (tempChar == DOT) {
                tempMap[index] = DOT;
                num_dots++;
            } else if (tempChar == PACMAN) {
                tempMap[index] = PACMAN;
            } else if (tempChar == GHOST) {
                tempMap[index] = GHOST;
            } else if (tempChar == WALL) {
                tempMap[index] = WALL;
            }
            index++;
        }
    }

    fclose(file);
    return tempMap;
}
