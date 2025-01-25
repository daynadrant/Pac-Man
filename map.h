// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

char * load_map(char * filename, int * map_height, int * map_width);

//for iswall function
#define NOT_WALL 0
#define YES_WALL 1

int is_wall(int y, int x);

void move_actor(int * x, int * y, char direction);

#endif //PROJECT_MAP_H
