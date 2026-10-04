#ifndef BACKEND_H
#define BACKEND_H

#include <ncurses.h>
#include <string.h>

#include "defines.h"
#include "frontend.h"
#include "library.h"
#include "objects.h"

typedef enum {
  START_SCREEN = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  PAUSED,
} GameState;

void game_init(GameInfo_t *game);
void rotate_figure(int **field, Tetromino *figure);
void add_score(GameInfo_t *game, int score);

GameInfo_t *GetGame();

GameState *GetState();

Tetromino getRandomFigure();
void generateNewFigure();

Tetromino *GetCurrentFigure();
Tetromino *GetNextFigure();

#endif
