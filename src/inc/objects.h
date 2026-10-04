#ifndef OBJECTS_H
#define OBJECTS_H

#include "defines.h"
#include "game_settings.h"

#define BLOCKS 4
#define NUM_ROTATIONS 4

typedef struct {
  int x;
  int y;
} Vector2;

typedef struct {
  Vector2 blocks[BLOCKS];
} TetrominoRotation;

typedef struct {
  TetrominoRotation rotations[NUM_ROTATIONS];
  int current_rotation;
  Vector2 pos;
  TetrominoRotation display_info;
} Tetromino;

Vector2 getWorldPos(Tetromino fig, int block);

#define FIGURE_S                                       \
  {                                                    \
    .rotations = {{{{0, 2}, {1, 2}, {1, 1}, {2, 1}}},  \
                  {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}},  \
                  {{{0, 2}, {1, 2}, {1, 1}, {2, 1}}},  \
                  {{{0, 0}, {0, 1}, {1, 1}, {1, 2}}}}, \
    .display_info = {                                  \
      {{0, 1}, {1, 1}, {1, 0}, {2, 0}}                 \
    }                                                  \
  }
#define FIGURE_Z                                       \
  {                                                    \
    .rotations = {{{{0, 1}, {1, 1}, {1, 2}, {2, 2}}},  \
                  {{{1, 2}, {1, 1}, {2, 1}, {2, 0}}},  \
                  {{{0, 1}, {1, 1}, {1, 2}, {2, 2}}},  \
                  {{{1, 2}, {1, 1}, {2, 1}, {2, 0}}}}, \
    .display_info = {                                  \
      {{0, 0}, {1, 0}, {1, 1}, {2, 1}}                 \
    }                                                  \
  }
#define FIGURE_T                                       \
  {                                                    \
    .rotations = {{{{0, 1}, {1, 1}, {2, 1}, {1, 0}}},  \
                  {{{1, 0}, {1, 1}, {1, 2}, {2, 1}}},  \
                  {{{0, 1}, {1, 1}, {2, 1}, {1, 2}}},  \
                  {{{1, 0}, {1, 1}, {1, 2}, {0, 1}}}}, \
    .display_info = {                                  \
      {{0, 1}, {1, 1}, {2, 1}, {1, 0}}                 \
    }                                                  \
  }
#define FIGURE_L                                       \
  {                                                    \
    .rotations = {{{{2, 0}, {2, 1}, {1, 1}, {0, 1}}},  \
                  {{{1, 0}, {1, 1}, {1, 2}, {2, 2}}},  \
                  {{{0, 2}, {0, 1}, {1, 1}, {2, 1}}},  \
                  {{{0, 0}, {1, 0}, {1, 1}, {1, 2}}}}, \
    .display_info = {                                  \
      {{2, 0}, {2, 1}, {1, 1}, {0, 1}}                 \
    }                                                  \
  }
#define FIGURE_J                                       \
  {                                                    \
    .rotations = {{{{0, 0}, {0, 1}, {1, 1}, {2, 1}}},  \
                  {{{1, 0}, {2, 0}, {1, 1}, {1, 2}}},  \
                  {{{0, 1}, {1, 1}, {2, 1}, {2, 2}}},  \
                  {{{0, 2}, {1, 2}, {1, 1}, {1, 0}}}}, \
    .display_info = {                                  \
      {{0, 0}, {0, 1}, {1, 1}, {2, 1}}                 \
    }                                                  \
  }
#define FIGURE_O                                       \
  {                                                    \
    .rotations = {{{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},  \
                  {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},  \
                  {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}},  \
                  {{{0, 0}, {0, 1}, {1, 0}, {1, 1}}}}, \
    .display_info = {                                  \
      {{1, 0}, {2, 0}, {1, 1}, {2, 1}}                 \
    }                                                  \
  }
#define FIGURE_I                                       \
  {                                                    \
    .rotations = {{{{0, 1}, {1, 1}, {2, 1}, {3, 1}}},  \
                  {{{2, 0}, {2, 1}, {2, 2}, {2, 3}}},  \
                  {{{0, 2}, {1, 2}, {2, 2}, {3, 2}}},  \
                  {{{1, 0}, {1, 1}, {1, 2}, {1, 3}}}}, \
    .display_info = {                                  \
      {{0, 1}, {1, 1}, {2, 1}, {3, 1}}                 \
    }                                                  \
  }

#endif