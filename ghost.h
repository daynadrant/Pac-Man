// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#ifndef PROJECT_GHOST_H
#define PROJECT_GHOST_H

char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x);

int validDirn(int ghost_y, int ghost_x);

char status(int dirn, int ghost_x, int ghost_y);

#endif //PROJECT_GHOST_H
