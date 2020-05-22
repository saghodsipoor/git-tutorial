#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <vector>

#include "Board.hpp"


void Board::reset()
{
  delete[] cells_;
  cells_ = new Cell[size_.w * size_.h];
  plant_bombs();
  set_cell_values();
  game_is_on_ = true;
}

const std::string Board::cell_state(const Index& index)
{
  auto& cell = (*this)(index.i, index.j);
  
  if (cell.flagged)
    return "flagged";

  if (!cell.visitted)
    return "unclicked";

  // if visitted
  if (cell.bombed)
    return "bomb-clicked";

  if (cell.neighbor_bombs == 0)
    return "blank";

  return std::to_string(cell.neighbor_bombs);
}

void Board::toggle_flag(Index index)
{
  auto& cell = (*this)(index.i, index.j);
  if (!cell.visitted)
    cell.flagged ^= true;
}

void Board::visit(Index index)
{
  auto& board = *this;
  if (board(index.i, index.j).flagged)
    return;
  
  // if cell isn't flagged
  std::list<Index> to_visit({index});
  while(!to_visit.empty())
  {
    index = to_visit.front();
    auto& cell = board(index.i, index.j);
    if (cell.bombed)
    {
      cell.visitted = true;
      game_is_on_ = false;
      break;
    }
    if (cell.neighbor_bombs != 0)
    {
      cell.visitted = true;
      to_visit.pop_front();
      continue;
    }
    
    // checking neighbors' condition
    for (const auto& dir : directions_)
    {
      int i = index.i + dir.i, j = index.j + dir.j;
      // invalid index
      if (!board.index_is_valid(i, j))
        continue;
      
      if (board(i, j).flagged)
        continue;
      // blank cell
      if (!board(i,j).visitted)
        to_visit.push_back({i, j});
    }
    cell.visitted = true;
    to_visit.pop_front();
  }  
}

void Board::print()
{
  static char red   [] = "\e[38;5;196m";
  static char green [] = "\e[38;5;46m";
  static char blue  [] = "\e[38;5;26m";
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
        if (cell.visitted) std::cout << blue;
        std::cout << " " << cell.neighbor_bombs << " " << reset;
      }
    }
    std::cout << std::endl;
  });
}

Board::Board(Size size): size_(size), cells_(new Cell[size.w * size.h])
{
  plant_bombs();
  set_cell_values();
}

Board::~Board()
{
  delete[] cells_;
}

void Board::set_cell_values()
{
  
  for_each_cell([&](int i, int j){
    for (int k = 0; k < directions_num_; ++k)
      if (index_is_valid(i + directions_[k].i, j + directions_[k].j))
        if ((*this)(i + directions_[k].i, j + directions_[k].j).bombed)
          ++(*this)(i, j).neighbor_bombs;
  });
};

bool Board::index_is_valid(int i, int j)
{
  return i >= 0 && i < size_.w && j >= 0 && j < size_.h;
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

const std::vector<Board::Direction> Board::directions_ =
    {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1,-1}, {1,0}, {1,1}};
