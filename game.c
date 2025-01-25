// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;
extern int num_dots;

int check_win() {
    if (num_dots == 0) {
        return 1;
    } else {
        return 0;
    }
}

//function to check if the player lost, if it moved into a ghost or a ghost moved into it
int check_loss(int pacman_y, int pacman_x, int
ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    //Compare the positions of the ghosts with the position of pacman to see if pacman has been eaten.
    //If so, the function should return YOU_LOSE.
    if ((pacman_y == ghosts_y[0] && pacman_x == ghosts_x[0]) || (pacman_y == ghosts_y[1] && pacman_x == ghosts_x[1])) {
        return 1; //indicates player loss
    }
        // If not, it should return KEEP_GOING.
    else {
        return 0;
    }
}

