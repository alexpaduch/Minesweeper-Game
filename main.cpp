// This should be the gameplay loop
#include "Board.h"
#include "Tile.h"
#include <iostream>

int main() {

  int rows;
  int columns;
  int mine_count;
  std::cout << "Enter a board size rows followed by columns: ";
  std::cin >> rows >> columns;
  std::cout << "Enter number of mines for custom difficulty: ";
  std::cin >> mine_count;
  std::cout << std::endl;

  Board play_area(rows, columns, mine_count);
  int dig_row;
  int dig_col;

  while (!play_area.get_has_lost() && !play_area.get_has_won()) {
    play_area.print();

    std::cout << "Enter a row and column to dig: ";
    std::cin >> dig_row >> dig_col;
    std::cout << std::endl;

    play_area.reveal(dig_row, dig_col);
  }

  if (play_area.get_has_won()) {
    std::cout << "YOU'VE WON!!!" << std::endl;
    std::cout << "Final Board:\n";
    play_area.print();

  } else {
    std::cout << "YOU'VE LOST!!!" << std::endl;
    std::cout << "Final Board:\n";
    play_area.display_revealed();
  }
}