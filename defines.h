// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#ifndef PROJECT_DEFINES_H
#define PROJECT_DEFINES_H

#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
// then, the keys that are valid inputs
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define SEES_NOTHING 'n'

// some constants that may be useful
#define NUM_GHOSTS 2
#define MAP_NAME "map.txt"

// error codes that you need to use in your program
#define NO_ERROR 0
#define ERR_NO_MAP 1
#define ERR_NO_PACMAN 2
#define ERR_NO_GHOSTS 3

//for iswall function
#define NOT_WALL 0
#define YES_WALL 1

#endif //PROJECT_DEFINES_H
