#include "inc/defines.h"
#include "inc/frontend.h"

UserAction_t handle_input(int user_input) {
  UserAction_t action = KEY_DOWN;

  if (user_input == KEY_UP)
    action = Up;
  else if (user_input == KEY_DOWN)
    action = Action;
  else if (user_input == KEY_LEFT)
    action = Left;
  else if (user_input == KEY_RIGHT)
    action = Right;
  else if (user_input == 'P' || user_input == 'p')
    action = Pause;
  else if (user_input == KEY_BACKSPACE)
    action = Terminate;
  else if (user_input == ENTER_KEY)
    action = Start;

  return action;
}

void game_loop() {
  bool break_flag = TRUE;

  while (break_flag) {
    UserAction_t currentAction = handle_input(getch());
    userInput(currentAction, FALSE);
    print_game(updateCurrentState());
  }
}

int main(void) {
  setlocale(LC_ALL, "");
  WIN_INIT(50);
  game_loop();
  endwin();

  return 0;
}