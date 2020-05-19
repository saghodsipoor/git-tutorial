#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <vector>


class Board
{
public:
  struct Direction {int i, j;}; 
  struct Size { unsigned w, h; };
  struct Cell
  {
    bool visitted = false, bombed = false, flagged = false;
    unsigned neighbor_bombs = 0;
  };
  class Iterator
  {
  public:


  private:
    Cell *cells_[];
  };

private:
  Iterator cells_;
};



#endif // GAME_HPP
