#ifndef FRONTEND_H
#define FRONTEND_H

#include <locale.h>
#include <string.h>

#include "game_settings.h"
#include "library.h"

void print_game(GameInfo_t game_info);
void print_overlay();
void print_levelerror();
void print_boxes();
void print_info();
void draw_row(int row, int show);

#endif