#include "Array2D.h"

#include <iostream>

using stdsize = std::size_t;

class World {

private:
  Array2D<bool> board;

  stdsize neighbour_counter(const stdsize h_index, const stdsize w_index) const {
    stdsize lives = 0;

    for (stdsize i = h_index + board.get_height() - 1;
         i <= h_index + board.get_height() + 1; ++i)
      for (stdsize j = w_index + board.get_width() - 1;
           j <= w_index + board.get_width() + 1; ++j)
        if (board[i % board.get_height()][j % board.get_width()])
          lives++;

    if (board[h_index][w_index])
      lives--;

    return lives;
  };

public:
  World(const Array2D<bool> &worldb) : board(worldb){};

  ssize_t get_height() const { return board.get_height(); };

  ssize_t get_width() const { return board.get_width(); };

  void evolution() {
    Array2D<bool> newWorld(board.get_height(), board.get_width());
    int lives;

    for (std::size_t i = 0; i != board.get_height(); ++i)
      for (std::size_t j = 0; j != board.get_width(); ++j) {
        lives = neighbour_counter(i, j);
        if (board[i][j])
          newWorld[i][j] = (lives == 3 || lives == 2);
        else
          newWorld[i][j] = (lives == 3);
      }

    board = newWorld;
  };

  bool operator==(const World &other) const { return board == other.board; };

  bool operator!=(const World &other) const { return !operator==(other); };

  void next_world() {
    int max_h = board.get_height() - 1;
    int max_w = board.get_width() - 1;

    if (board[max_h][max_w]) {
      for (ssize_t i = board.get_height() * board.get_width() - 1; i > 0; --i) {
        if (!board[0][i]) {
          board[0][i] = true;
          break;
        }

        board[0][i] = false;
      }
    } else {
      board[max_h][max_w] = true;
    }
  };

  friend std::ostream &operator<<(std::ostream &os, const World &w);
};

std::ostream &operator<<(std::ostream &os, const World &w) {
  for (std::size_t i = 0; i < w.board.get_height(); i++) {
    for (std::size_t j = 0; j < w.board.get_width(); j++)
      os << (w.board[i][j] ? "*" : ".");
    os << std::endl;
  }
  os << std::endl;

  return os;
};