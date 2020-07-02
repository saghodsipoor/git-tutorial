#include <iostream>

#include "Board.hpp"

int main()
{
  Board b;
  b.print();

  bool game_is_on = true;
  char command; int i, j;
  while (game_is_on)
  {
    std::cin >> command;
    switch (command)
    {
    case 'v':
      std::cin  >> i >> j;
      b.visit({i, j});
      if (!b.game_is_on())
        game_is_on = false;
      break;
    
    case 'f':
      std::cin  >> i >> j;
      b.toggle_flag({i, j});
      break;

    case 'r':
      b.reset();
      break;

    case 'q':
      game_is_on = false;
      break;

    default:
      break;
    }
    b.print();
  }
  return 0;
}
