#include "../../inc/backend.h"

#include <stdlib.h>

int save_high_score(int score) {
  const char *home = getenv("HOME");
  if (!home) {
    fprintf(stderr, "Не удалось получить домашнюю директорию.\n");
  }

  char path[512];
  snprintf(path, sizeof(path), "%s/%s", home, "highscore.txt");

  FILE *f = fopen(path, "w");
  if (f == NULL) {
    perror("Ошибка открытия файла для записи");
    return -1;
  }

  fprintf(f, "%d\n", score);
  fclose(f);
  return 0;
}

int load_high_score() {
  const char *home = getenv("HOME");
  if (!home) {
    fprintf(stderr, "Не удалось получить домашнюю директорию.\n");
    perror("Не удалось получить домашнюю директорию.\n");
    return -1;
  }

  char path[512];
  snprintf(path, sizeof(path), "%s/%s", home, "highscore.txt");

  FILE *f = fopen(path, "r");
  int high_score = 0;
  if (f != NULL) {
    if (fscanf(f, "%d", &high_score) != 1) {
      high_score = 0;
    }
    fclose(f);
  }
  return high_score;
}

void add_score(GameInfo_t *game, int score) {
  game->score += score;
  if (game->high_score < game->score) {
    game->high_score = game->score;
    save_high_score(game->high_score);
  }
  if (game->score > game->level * 600 && game->level < MAX_LEVEL) {
    game->level = 1 + game->score / 600;
  }
}

void clear_next_field(GameInfo_t *game) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game->next[i][j] = 0;
    }
  }
}

void copy_from_next_to_field(GameInfo_t *game) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game->field[i][j] = game->next[i][j];
    }
  }
}

void add_figure_to_next(GameInfo_t *game) {
  Tetromino *figure = GetCurrentFigure();
  for (int i = 0; i < BLOCKS; i++) {
    Vector2 worldPos = getWorldPos(*figure, i);
    if (worldPos.y >= 0) game->next[worldPos.y][worldPos.x] = 1;
  }
}

void add_next_figure_to_next(GameInfo_t *game) {
  Tetromino *next = GetNextFigure();
  for (int i = 0; i < FIGURE_DISPLAY_HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game->next[HEIGHT + i][j] = 0;
    }
  }

  for (int i = 0; i < BLOCKS; i++) {
    Vector2 worldPos = next->display_info.blocks[i];
    game->next[worldPos.y + HEIGHT][worldPos.x] = 1;
  }
}

void copy_from_field_to_next(GameInfo_t *info) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      info->next[i][j] = info->field[i][j];
    }
  }
}

void game_init(GameInfo_t *game) {
  game->level = 1;
  game->score = 0;
  game->speed = BASE_SPEED;
  game->high_score = load_high_score();

  if (game->field == NULL) {
    game->field = calloc(sizeof(int *), HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
      game->field[i] = calloc(sizeof(int), WIDTH);
  }

  if (game->next == NULL) {
    game->next = calloc(sizeof(int *), HEIGHT + FIGURE_DISPLAY_HEIGHT);
    for (int i = 0; i < HEIGHT + FIGURE_DISPLAY_HEIGHT; i++)
      game->next[i] = calloc(sizeof(int), WIDTH);
  }

  for (int i = 0; i < HEIGHT; i++) {
    memset(game->field[i], 0, sizeof(int) * WIDTH);
  }
  for (int i = 0; i < HEIGHT + FIGURE_DISPLAY_HEIGHT; i++) {
    memset(game->next[i], 0, sizeof(int) * WIDTH);
  }

  Tetromino *currentFigure = GetCurrentFigure();
  Tetromino *nextFigure = GetNextFigure();
  GameState *state = GetState();

  *state = START_SCREEN;
  *currentFigure = getRandomFigure();
  currentFigure->pos.x = 5;
  currentFigure->pos.y = 1;
  *nextFigure = getRandomFigure();
  add_next_figure_to_next(game);
}

Tetromino getRandomFigure() {
  Tetromino figures[] = {FIGURE_L, FIGURE_J, FIGURE_O, FIGURE_I,
                         FIGURE_T, FIGURE_S, FIGURE_Z};
  int count = sizeof(figures) / sizeof(figures[0]);
  int random_index = rand() % count;

  return figures[random_index];
}

GameInfo_t *GetGame() {
  static GameInfo_t game = {0};
  static int initialized = 0;
  if (!initialized) {
    game_init(&game);
    initialized = 1;
  }
  return &game;
}

GameState *GetState() {
  static GameState state = {0};
  return &state;
}

Tetromino *GetCurrentFigure() {
  static Tetromino currentFigure = {0};
  return &currentFigure;
}

Tetromino *GetNextFigure() {
  static Tetromino currentFigure = {0};
  return &currentFigure;
}

int collision_check(int **field, Tetromino figure) {
  int collide = 0;
  for (int i = 0; i < BLOCKS && collide == 0; i++) {
    Vector2 worldPos = getWorldPos(figure, i);
    if (worldPos.y >= 0)
      collide = worldPos.y > HEIGHT - 1 || worldPos.x < 0 ||
                worldPos.x > WIDTH - 1 || field[worldPos.y][worldPos.x] == 1;
  }

  return collide;
}

int y_collision_check(int **field, Tetromino figure) {
  int collide = 0;

  for (int i = 0; i < BLOCKS && collide == 0; i++) {
    Vector2 worldPos = getWorldPos(figure, i);
    if (worldPos.y >= 0)
      collide = worldPos.y > HEIGHT - 1 || field[worldPos.y][worldPos.x] == 1;
  }

  return collide;
}

int x_collision_check(int **field, Tetromino figure) {
  int collide = 0;

  for (int i = 0; i < BLOCKS && collide == 0; i++) {
    Vector2 worldPos = getWorldPos(figure, i);
    if (worldPos.y >= 0)
      collide = worldPos.x < 0 || worldPos.x > WIDTH - 1 ||
                field[worldPos.y][worldPos.x] == 1;
  }

  return collide;
}

void generateNewFigure() {
  Tetromino new = getRandomFigure();

  Tetromino *figure = GetCurrentFigure();
  Tetromino *nextFigure = GetNextFigure();
  *figure = *nextFigure;

  figure->pos.x = 5;
  figure->pos.y = -1;

  *nextFigure = new;
  add_next_figure_to_next(GetGame());
}

void remove_rows(GameInfo_t *info, int removed_rows[HEIGHT]) {
  int removed = 0;
  for (int i = HEIGHT - 1; i >= 0; i--) {
    if (removed_rows[i]) {
      removed++;
    } else {
      for (int j = 0; j < WIDTH; j++) {
        info->next[i + removed][j] = info->field[i][j];
      }
    }
  }

  switch (removed) {
    case 1:
      add_score(info, 100);
      break;
    case 2:
      add_score(info, 300);
      break;
    case 3:
      add_score(info, 700);
      break;
    case 4:
      add_score(info, 1500);
      break;
  }

  copy_from_next_to_field(info);
}

void update_rows(GameInfo_t *info, int removed_rows[HEIGHT]) {
  int removed = 0;
  for (int i = HEIGHT - 1; i >= 0; i--) {
    int count = 0;
    for (int j = 0; j < WIDTH; j++) count += info->field[i][j];

    removed_rows[i] = count == WIDTH;
    removed += count == WIDTH;
  }
  if (removed) *GetState() = ATTACHING;
}

void rotate_figure(int **field, Tetromino *fig) {
  int old_rotation = fig->current_rotation;
  int new_rotation = (fig->current_rotation + 1) % NUM_ROTATIONS;
  fig->current_rotation = new_rotation;
  if (collision_check(field, *fig)) {
    fig->current_rotation = old_rotation;
  }
}

Vector2 getWorldPos(Tetromino figure, int block) {
  int worldX =
      figure.pos.x + figure.rotations[figure.current_rotation].blocks[block].x;
  int worldY =
      figure.pos.y + figure.rotations[figure.current_rotation].blocks[block].y;
  Vector2 WorldPos = {worldX, worldY};
  return WorldPos;
}

int addToField(int **field, Tetromino figure) {
  int result = 0;

  for (int i = 0; i < BLOCKS && result == 0; i++) {
    Vector2 worldPos = getWorldPos(figure, i);
    if (worldPos.y <= 0)
      result = 1;
    else
      field[worldPos.y][worldPos.x] = 1;
  }

  return result;
}

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *currentInfo = GetGame();
  GameState *state = GetState();
  if ((action == Start && *state == GAMEOVER) || action == Terminate)
    game_init(currentInfo);
  else if (action == Start && *state == START_SCREEN)
    *state = SPAWN;
  else if (action == Pause && *state != START_SCREEN && *state != GAMEOVER)
    *state = *state == PAUSED ? MOVING : PAUSED;
  else if (*state == MOVING) {
    Tetromino *currentFigure = GetCurrentFigure();
    int prevX = currentFigure->pos.x;
    currentInfo->speed = BASE_SPEED * currentInfo->level / 2.f;
    switch (action) {
      case Left:
        currentFigure->pos.x -= 1;
        break;
      case Right:
        currentFigure->pos.x += 1;
        break;
      case Up:
        rotate_figure(currentInfo->field, currentFigure);
        break;
      case Action:
        currentInfo->speed *= 10;
        break;
      default:
        break;
    }

    if (x_collision_check(currentInfo->field, *currentFigure)) {
      currentFigure->pos.x = prevX;
    }
    prevX = hold;
  }
}

GameInfo_t updateCurrentState() {
  static int tick = 0;
  static int attaching_tick = 0;
  static int removed_rows[HEIGHT] = {0};
  GameInfo_t *currentInfo = GetGame();
  GameState *state = GetState();
  Tetromino *currentFigure = GetCurrentFigure();
  if (*state == GAMEOVER)
    currentInfo->pause = -2;
  else if (*state == START_SCREEN)
    currentInfo->pause = -1;
  else if (*state == SPAWN) {
    generateNewFigure();
    *state = MOVING;
  } else if (*state == PAUSED)
    currentInfo->pause = 1;
  else if (*state == ATTACHING) {
    attaching_tick += 1;

    for (int i = 0; i < HEIGHT; i++) {
      for (int j = 0; j < WIDTH && removed_rows[i] == 1; j++)
        currentInfo->next[i][j] = attaching_tick % 5 == 0;
    }
    if (attaching_tick >= 30) {
      *state = SPAWN;
      attaching_tick = 0;
      remove_rows(currentInfo, removed_rows);
    }
  } else {
    currentInfo->pause = 0;
    tick += currentInfo->speed;
    clear_next_field(currentInfo);
    if (tick >= 100) {
      currentFigure->pos.y += 1;
      if (y_collision_check(currentInfo->field, *currentFigure)) {
        currentFigure->pos.y -= 1;
        int end = addToField(currentInfo->field, *currentFigure);
        *state = end == 1 ? GAMEOVER : SPAWN;
        update_rows(currentInfo, removed_rows);
      }
      tick = 0;
    }

    copy_from_field_to_next(currentInfo);
    add_figure_to_next(currentInfo);
  }

  return *currentInfo;
}