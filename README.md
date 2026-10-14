# Pac-Man

A terminal Pac-Man game written in C. You move Pac-Man around a maze, eat every dot to win, and lose if a ghost catches you. Built on the APSC 142 Engineering Programming Project starter code (© Sean Kauffman 2024).

## How to play

Move with the keyboard:

| Key | Direction |
| --- | --- |
| `w` | up |
| `a` | left |
| `s` | down |
| `d` | right |

- **Win:** eat all the dots (`.`).
- **Lose:** a ghost reaches you.
- The two ghosts chase Pac-Man when they have a line of sight to him, and otherwise wander in a random direction.

## Maps

The maze is loaded from `map.txt` when the game starts. It's a grid of space-separated characters:

| Character | Meaning |
| --- | --- |
| `W` | wall |
| `.` | dot |
| `P` | Pac-Man's starting position (exactly one) |
| `G` | ghost starting position (two) |

Edit `map.txt` to make your own maze.

## Building and running

Requires CMake 3.26+ and a C compiler.

```bash
cmake -S . -B build
cmake --build build --target project
cd build && ./project
```

Run it in a real terminal. The game reads single key presses and uses text colours, so the IDE's output pane won't work unless it emulates a terminal (in CLion, enable "Emulate terminal in output console"). CMake copies `map.txt` next to the executable.

## Code overview

| File | Contents |
| --- | --- |
| `apsc142project.c` | Main game loop: finds Pac-Man and the ghosts on the map, handles input, updates the board |
| `map.c` / `map.h` | Loading the map, wall checks and moving Pac-Man and the ghosts |
| `ghost.c` / `ghost.h` | Ghost line-of-sight, valid directions and movement |
| `game.c` / `game.h` | Win and loss checks |
| `colours.c` / `colours.h` | Terminal colours and key reading (provided) |
| `defines.h` | Shared constants (map symbols, keys, ghost count) |
| `tests.cpp` | Unit tests using [doctest](https://github.com/doctest/doctest) (`doctest.h` is bundled) |

## Tests

`tests.cpp` has a `tests` CMake target. As the repo stands, that target doesn't link, because the globals it needs (`num_dots`, `tempChar`) are defined in `apsc142project.c`, which the test build leaves out. Defining them in `tests.cpp`, next to the existing `map` and `dot_map`, fixes it.
