#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

#include "Board.hpp"


void Board::print()
{
  static char red   [] = "\e[38;5;196m";
  static char green [] = "\e[38;5;46m";
  static char blue  [] = "\e[38;5;46m";
  static char reset [] = "\e[0m";
  
  for_each_row([&](int i){
    for (auto j=0; j<size_.h; ++j)
    {
      const auto& cell = (*this)(i,j);
      if (cell.flagged)
        std::cout << green << " f " << reset;
      else
      if (cell.bombed)
        std::cout << red << " b " << reset;
      else
      {
        if (cell.visitted) std::cout << green;
        else std::cout << " " << cell.neighbor_bombs << " " << reset;
      }
    }
    std::cout << std::endl;
  });
}

Board::Board(Size size): size_(size), cells_(new Cell[size.w * size.h])
{
  plant_bombs();
}

Board::~Board()
{
  delete[] cells_;
}

void Board::plant_bombs()
{
  unsigned bombs_num = size_.h * size_.w / 10;
  
  // make list of indices
  std::vector<Board::Index> indices;
  for_each_cell([&](int i, int j){
    indices.push_back({i, j});
  });

  // shuffle indices
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::shuffle(indices.begin(), indices.end(), std::default_random_engine(seed));

  // plant bombs for list of indices
  for (auto i = 0; i < bombs_num; ++i)
    (*this)(indices[i].i, indices[i].j).bombed = true;
}
