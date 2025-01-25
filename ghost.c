// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "ghost.h"

extern char *map, *dot_map;
extern int width, height;

//function to see if a ghost is in view of pacman
char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int
ghost_x) {
    //if the ghost is in the same column as pacman, it can see pacman
    if (pacman_x == ghost_x) {
        //if ghost is below pacman, it should move up
        if (pacman_y < ghost_y) {
            return UP;
            //if ghost is above pacman, it should move down
        } else if (pacman_y > ghost_y) {
            return DOWN;
        }
    }

        //if ghost is in same row as pacman, it can see pacman
    else if (pacman_y == ghost_y) {
        //if ghost is to the left of pacman, it should move left
        if (pacman_x < ghost_x) {
            return LEFT;
            //if ghost is to the right of pacman, it should move right
        } else if (pacman_x > ghost_x) {
            return RIGHT;
        }
    } else {
        //ghost cannot see pacman
        return SEES_NOTHING;
    }
}

int validDirn(int ghost_y, int ghost_x) {
    if ((ghost_y != 0 && map[ghost_y * width + ghost_x - width] != WALL && map[ghost_y * width + ghost_x - width] != GHOST) || (ghost_x != width - 1 && map[ghost_y * width + ghost_x + 1] != WALL && map[ghost_y * width + ghost_x + 1] != GHOST) || (ghost_x != 0 && map[ghost_y * width + ghost_x - 1] != WALL && map[ghost_y * width + ghost_x - 1] != GHOST) || (ghost_y != height - 1 && map[ghost_y * width + ghost_x + width] != WALL && map[ghost_y * width + ghost_x + width] != GHOST)) {
        return 1; //ghost can move in at least one direction
    } else {
        return 0; //ghost CANNOT MOVE.
    }
}

//function to check if ghost can move in the random direction that was generated in the main
char status(int dirn, int ghost_x, int ghost_y) {
    //check if actor can move up, if its not on the edge of the map and if it's not a wall
    if (dirn == 0) {
        if (ghost_y != 0 && map[ghost_y * width + ghost_x - width] != WALL && map[ghost_y * width + ghost_x - width] != GHOST) {
            return UP;
        }
    } else if (dirn == 1) { //right
        if (ghost_x != width - 1 && map[ghost_y * width + ghost_x + 1] != WALL && map[ghost_y * width + ghost_x + 1] != GHOST) {
            return RIGHT;
        }
    } else if (dirn == 2) { //left
        if (ghost_x != 0 && map[ghost_y * width + ghost_x - 1] != WALL && map[ghost_y * width + ghost_x - 1] != GHOST) {
            return LEFT;
        }
    } else if (dirn == 3) { //down
        if (ghost_y != height - 1 && map[ghost_y * width + ghost_x + width] != WALL && map[ghost_y * width + ghost_x + width] != GHOST) {
            return DOWN;
        }
    }
    return 'v'; //ghost can't move in random direction generated in main, will try again
}
