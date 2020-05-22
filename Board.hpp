#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>


class Board
{
public:
  struct Index {int i, j;}; 
  struct Direction {int i, j;}; 
  struct Size { unsigned w, h; };
  struct Cell
  {
    bool visitted = false, bombed = false, flagged = false;
    unsigned neighbor_bombs = 0;
  };

  template <typename Function>
  inline void for_each_row(Function f)
  {
    for (int i = 0; i < size_.w; ++i)
      f(i);
  }

  template <typename Function>
  inline void for_each_cell(Function f)
  {
    for_each_row(
      [&](int i){ for (int j = 0; j < size_.h; ++j) f(i, j); }
    );     
  }

  void print();
  Cell& operator()(int i, int j) { return  *(cells_ + size_.w * i + j); };

  Board(Size size = {9, 9});
  ~Board();
private:
  void set_cell_values();
  bool index_is_valid(int i, int j);
  void plant_bombs();
  enum { directions_num_ = 8 };
  static const Direction directions_[directions_num_];
  Size size_;
  Cell *cells_;
};


#endif // GAME_HPP
