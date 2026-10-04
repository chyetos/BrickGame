#include <check.h>
#include <stdio.h>

#include "../inc/backend.h"

START_TEST(user_input_test)
{
    GameInfo_t* game = GetGame();
    game_init(game);
    GameState* state = GetState();
    updateCurrentState();
    userInput(Start, true);
    userInput(Start, true);
    userInput(Pause, true);
    updateCurrentState();
    userInput(Pause, true);
    int counter = 0;
    while(*state != GAMEOVER)
    {
      if(*state == SPAWN)
        counter++;
      userInput(Up, true);
      userInput(Action, true);
      userInput(counter % 2 == 0 ? Left : Right, true);

      updateCurrentState();
    }
    updateCurrentState();
}

START_TEST(game_cycle) {
    GameInfo_t* game = GetGame();
    GameState* state = GetState();
    int spawn_counter = 0;
    game->high_score = 0;
    *state = SPAWN;
    add_score(game, 1000);
    while(*state != GAMEOVER)
    {
      if(*state == SPAWN && spawn_counter < 6)
      {
        generateNewFigure();
        Tetromino o = FIGURE_O;
        Tetromino i = FIGURE_I;

        *GetCurrentFigure() = spawn_counter % 6 == 0 ? o : i;
        GetCurrentFigure()->pos.x = spawn_counter % 6 == 0 ? 8 : (spawn_counter % 3 == 1 ? 0 : 4);
        spawn_counter++;
        *state = MOVING;
      }
      updateCurrentState();
    }
    updateCurrentState();

}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  suite_add_tcase(s1, tc1_1);

  tcase_add_test(tc1_1, game_cycle);
  tcase_add_test(tc1_1, user_input_test);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return 0;
}