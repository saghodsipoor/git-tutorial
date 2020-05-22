#include <iostream>

#include "Board.hpp"

int main()
{
  Board b;
  b.print();

  bool flag = true;
  char command; int i, j;
  while (flag)
  {
    std::cin >> command;
    switch (command)
    {
    case 'v':
      std::cin  >> i >> j;
      b.visit({i, j});
      break;
    
    case 'f':
      std::cin  >> i >> j;
      b.toggle_flag({i, j});
      break;

    case 'r':
      b.reset();
      break;

    case 'q':
      flag = false;
      break;

    default:
      break;
    }
    b.print();
  }
  return 0;
}
