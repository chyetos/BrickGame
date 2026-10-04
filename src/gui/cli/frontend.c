#include "../../inc/frontend.h"

void draw_row(int row, int show) {
  wmove(stdscr, row + 1, 1);
  for (int i = 0; i < SCALED_WIDTH; i++) {
    waddstr(stdscr, show == 1 ? "▒" : "▓");
  }
}

void print_start() {
  wmove(stdscr, HEIGHT / 2, 5);
  printw("Нажми Enter!");
}

void print_pause() {
  wmove(stdscr, HEIGHT / 2, 6);
  printw("На паузе!");
}

void print_gameover() {
  wmove(stdscr, HEIGHT / 2, 6);
  printw("GAME OVER!");
}

void print_game(GameInfo_t info) {
  werase(stdscr);
  for (int i = 0; i < HEIGHT; i++) {
    wmove(stdscr, i + 1, 1);
    for (int j = 0; j < WIDTH; j++) {
      waddstr(stdscr, info.next[i][j] == 1 ? "▒" : "▓");
      waddstr(stdscr, info.next[i][j] == 1 ? "▒" : "▓");
    }
  }
  print_info(info);
  print_overlay();
  if (info.pause == -2)
    print_gameover();
  else if (info.pause == -1)
    print_start();
  else if (info.pause == 1)
    print_pause();

  refresh();
}

void print_info(GameInfo_t game) {
  for (int i = 0; i < FIGURE_DISPLAY_HEIGHT; i++) {
    wmove(stdscr, 1 + i, SCALED_WIDTH + 3 + PADDING);
    for (int j = 0; j < FIGURE_DISPLAY_WIDHT / 2; j++) {
      waddstr(stdscr, game.next[HEIGHT + i][j] == 1 ? "▒" : "▓");
      waddstr(stdscr, game.next[HEIGHT + i][j] == 1 ? "▒" : "▓");
    }
  }

  wmove(stdscr, 2 + FIGURE_DISPLAY_HEIGHT, SCALED_WIDTH + 3 + PADDING);
  printw("Score: %d", game.score);

  wmove(stdscr, 3 + FIGURE_DISPLAY_HEIGHT, SCALED_WIDTH + 3 + PADDING);
  printw("High score: %d", game.high_score);

  wmove(stdscr, 4 + FIGURE_DISPLAY_HEIGHT, SCALED_WIDTH + 3 + PADDING);
  printw("Level: %d", game.level);
}

void print_overlay() {
  // main window
  wmove(stdscr, 0, 0);
  for (int i = 0; i < SCALED_WIDTH + 2; i++) {
    waddstr(stdscr, "▄");
  }

  for (int i = 1; i < HEIGHT + 1; i++) {  // lr_borders
    wmove(stdscr, i, 0);
    waddstr(stdscr, "█");
    wmove(stdscr, i, SCALED_WIDTH + 1);
    waddstr(stdscr, "█");
  }

  wmove(stdscr, HEIGHT + 1, 0);
  for (int i = 0; i < SCALED_WIDTH + 2; i++) {
    waddstr(stdscr, "▀");
  }

  // additional info
  wmove(stdscr, 0, SCALED_WIDTH + PADDING + 2);
  for (int i = 0; i < FIGURE_DISPLAY_WIDHT + 2; i++) {
    waddstr(stdscr, "▄");
  }

  for (int i = 0; i < FIGURE_DISPLAY_HEIGHT; i++) {  // lr_borders
    wmove(stdscr, 1 + i, SCALED_WIDTH + 2 + PADDING);
    waddstr(stdscr, "█");
    wmove(stdscr, 1 + i, SCALED_WIDTH + 3 + FIGURE_DISPLAY_WIDHT + PADDING);
    waddstr(stdscr, "█");
  }

  wmove(stdscr, 1 + FIGURE_DISPLAY_HEIGHT, SCALED_WIDTH + 2 + PADDING);
  for (int i = 0; i < FIGURE_DISPLAY_WIDHT + 2; i++) {
    waddstr(stdscr, "▀");
  }
}