// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int YOU_WIN = 0;
int YOU_LOSE = 0;

//initializing dimensions of array
int height = 1;
int width = 0;

//for loadmap function and for maps
char tempChar;
char *map;
char *dot_map;

//keep track of dots and if player wins
int num_dots = 0;

//player co-ordinates
int player_x = 0;
int player_y = 0;

//for ghost in random dir if it doesn't see player
int random_dir;

//arrays for the ghost co-ordinates
int ghosts_x[NUM_GHOSTS];
int ghosts_y[NUM_GHOSTS];

int main(void) {
    //setbuf(stdout, NULL);

    //load the map
    map = load_map(MAP_NAME, &height, &width);

    //allocate memory for the dot_map
    dot_map = (char *)malloc((height * width) * sizeof(char));

    //set dot map indicies
    for (int i = 0; i < height * width; i++) {
        if (map[i] == DOT) {
            dot_map[i] = DOT;
        } else {
            dot_map[i] = EMPTY;
        }
    }

    //while the player has neither won nor lost
    while (YOU_WIN == 0 && YOU_LOSE == 0) {

        int test2 = 0;
        //Find pacman co-ordinates on map
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (map[y * width + x] == PACMAN) {
                    player_x = x; {
                        player_y = y;
                        test2++;
                    }
                }
            }
        }

        if (test2 != 1) {
            return ERR_NO_PACMAN;
        }

        /* WIN CHECK MAP used to test win and lose functions
          G  W  W  W  W  W  W  W  W
          W  W  W  W  W  W  W  W  W
          W  W  W  W  W  W  W  W  W
          W  W  W  W  W  W  W  W  W
          W  W  .  .  P  .  .  W  W
          W  W  W  W  W  W  W  W  W
          W  W  W  W  W  W  W  W  W
          W  W  W  W  W  W  W  W  W
          W  W  W  W  W  W  W  W  G

          G  .  .  .  W  .  .  .  .
          .  W  W  .  W  .  W  W  .
          .  W  .  .  .  .  .  W  .
          .  W  .  W  W  W  .  W  .
          .  .  .  .  P  .  .  .  .
          .  W  .  W  W  W  .  W  .
          .  W  .  .  .  .  .  W  .
          .  W  W  .  W  .  W  W  .
          .  .  .  .  W  .  .  .  G
          */

        //Find both ghosts co-ordinates on map
        int test = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (map[y * width + x] == GHOST) {
                    if (test == 0) {
                        ghosts_x[0] = x;
                        ghosts_y[0] = y;
                        test++;
                    } else if (test == 1) {
                        ghosts_x[1] = x;
                        ghosts_y[1] = y;
                    }
                }
            }
        }

        if (test != 1) {
            return ERR_NO_GHOSTS;
        }

        for (int i =0; i <width + 2; i++) {
            printf("W ");
        }

        printf("\n");

        //Print updated map
        for (int i = 0; i < height; i++) {
            printf("W ");
            for (int j = 0; j < width; j++) {
                // Calculate the index for the current element
                int index = i * width + j;
                // Print the value of the current element
                printf("%c ", map[index]);
                if (j == width - 1) {
                    printf("W ");
                    printf("\n");
                }
            }
        }

        //print walls around map
        for (int i =0; i <width + 2; i++) {
            printf("W ");
        }

        printf("\n");

        //user input
        printf("Enter a direction (WASD): ");
        char direction;
        scanf(" %c", &direction);

        //Check if the direction is valid
        if (direction != UP && direction != DOWN && direction != LEFT && direction != RIGHT) {
        } else {
            move_actor(&player_x, &player_y, direction);
        }

        //check if player moved into ghost
        YOU_LOSE = check_loss(player_y, player_x, ghosts_y, ghosts_x);

        //move each ghost
        for (int z = 0; z < NUM_GHOSTS; z++) {

            //check if ghost can see pacman and if so what direction
            char dirn = sees_pacman(player_y, player_x, ghosts_y[z], ghosts_x[z]);

            int iswall = 0;


            if (dirn == UP) {
                for (int i = player_y + 1; i < ghosts_y[z]; i++) {
                    if (iswall == 0) {
                        //check if wall between ghost and pacman
                        iswall=is_wall(i, player_x);
                    }
                }
                if (iswall == 0) {
                    //if no wall move ghost up
                    move_actor(&ghosts_x[z], &ghosts_y[z], UP);
                } else if (iswall == 1) {
                    //if yes wall generate random dir for ghost to move in
                    if (validDirn(ghosts_y[z], ghosts_x[z]) == 1) {
                        char valid;
                        do {
                            random_dir = rand() % 4;
                            valid = status(random_dir, ghosts_x[z], ghosts_y[z]);
                        } while (status(random_dir, ghosts_x[z], ghosts_y[z]) == 'v');
                        move_actor(&ghosts_x[z], &ghosts_y[z], valid);
                    } else if (validDirn(ghosts_y[z], ghosts_x[z]) == 0) {
                        //if there's no valid direction for ghost to randomly move in it doesn't move
                    }
                }
            } else if (dirn == DOWN) { //repeat for each dirn
                for (int i = ghosts_y[z] + 1; i < player_y; i++) {
                    if (iswall == 0) {
                        iswall=is_wall(i, player_x);
                    }
                }
                if (iswall == 0) {
                    // move ghost down
                    move_actor(&ghosts_x[z], &ghosts_y[z], DOWN);
                } else if (iswall == 1) {
                    //generate random dir for ghost to move in

                    if (validDirn(ghosts_y[z], ghosts_x[z]) == 1) {
                        char valid;
                        do {
                            random_dir = rand() % 4;
                            valid = status(random_dir, ghosts_x[z], ghosts_y[z]);
                        } while (status(random_dir, ghosts_x[z], ghosts_y[z]) == 'v');
                        move_actor(&ghosts_x[z], &ghosts_y[z], valid);
                    } else if (validDirn(ghosts_y[z], ghosts_x[z]) == 0) {
                    }
                }
            } else if (dirn == LEFT) {
                for (int i = player_x + 1; i < ghosts_x[z]; i++) {
                    if (iswall == 0) {
                        iswall=is_wall(player_y, i);
                    }
                }
                if (iswall == 0) {
                    // move ghost left
                    move_actor(&ghosts_x[z], &ghosts_y[z], LEFT);
                } else if (iswall == 1) {
                    //generate random dir for ghost to move in

                    if (validDirn(ghosts_y[z], ghosts_x[z]) == 1) {
                        char valid;
                        do {
                            random_dir = rand() % 4;
                            valid = status(random_dir, ghosts_x[z], ghosts_y[z]);
                        } while (status(random_dir, ghosts_x[z], ghosts_y[z]) == 'v');
                        move_actor(&ghosts_x[z], &ghosts_y[z], valid);
                    } else if (validDirn(ghosts_y[z], ghosts_x[z]) == 0) {
                    }
                }
            } else if (dirn == RIGHT) {
                for (int i = ghosts_x[z] + 1; i < player_x; i++) {
                    if (iswall == 0) {
                        iswall=is_wall(player_y, i);
                    }
                }
                if (iswall == 0) {
                    // move ghost right
                    move_actor(&ghosts_x[z], &ghosts_y[z], RIGHT);
                } else if (iswall == 1) {
                    //generate random dir for ghost to move in
                    if (validDirn(ghosts_y[z], ghosts_x[z]) == 1) {
                        char valid;
                        do {
                            random_dir = rand() % 4;
                            valid = status(random_dir, ghosts_x[z], ghosts_y[z]);
                        } while (status(random_dir, ghosts_x[z], ghosts_y[z]) == 'v');
                        move_actor(&ghosts_x[z], &ghosts_y[z], valid);
                    } else if (validDirn(ghosts_y[z], ghosts_x[z]) == 0) {
                    }
                }
            } else if (dirn == SEES_NOTHING) {
                //generate random dir for ghost to move in
                if (validDirn(ghosts_y[z], ghosts_x[z]) == 1) {
                    char valid;
                    do {
                        random_dir = rand() % 4;
                        valid = status(random_dir, ghosts_x[z], ghosts_y[z]);
                    } while (status(random_dir, ghosts_x[z], ghosts_y[z]) == 'v');
                    move_actor(&ghosts_x[z], &ghosts_y[z], valid);
                } else if (validDirn(ghosts_y[z], ghosts_x[z]) == 0) {
                }
            }
        }

        //check if ghost moved into player
        YOU_LOSE = check_loss(player_y, player_x, ghosts_y, ghosts_x);
        if (YOU_LOSE == 1) {
            printf(
                    "Sorry, you lose.\n");
        }

        //check win
        YOU_WIN = check_win();

        if (YOU_WIN == 1) {
            printf("Congratulations! You win!\n");
        }
    }
    free(map);
    free(dot_map);
}
