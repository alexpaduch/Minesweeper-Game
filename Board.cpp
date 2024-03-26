// The implementation of the Board.h file
#include "Board.h"
#include "Tile.h"

#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>

Board::Board() {
  // Default constructor sets board to 8x8 with 10 mines
  board_width = 8;
  board_height = 8;
  size = board_width * board_height;
  // Dynamically allocates memory for the board of tiles (board can be any size
  // if need be)
  tiles = new Tile[size];

  // Initialize tiles array with Tiles (as defined in Tile.cpp)
  for (int i = 0; i < size; i++) {
    tiles[i] = Tile();
  }

  place_mines(10);
  update_counts();
}

Board::Board(int width, int height, int mines) {
  // Overloaded constructor sets board to user specified width x height with
  // mines
  board_width = width;
  board_height = height;
  mine_count = mines;
  size = width * height;
  // Dynamically allocates memory for the board of tiles (board can be any size
  // if need be)
  tiles = new Tile[size];

  // Initialize tiles array with Tiles (as defined in Tile.cpp)
  for (int i = 0; i < size; i++) {
    tiles[i] = Tile();
  }
  place_mines(mine_count);
  update_counts();
}

void Board::place_mines(int mine_count) {

  srand(time(0));

  while (mine_count > 0) {
    int mine_index = rand() % size;

    if (tiles[mine_index].get_value() != 9) {
      tiles[mine_index].set_value(9);
      mine_count--;
    }
  }
}

void Board::update_counts() {
  // First two for loops are going through each tile in the board
  for (int i = 0; i < board_height; i++) {
    for (int j = 0; j < board_width; j++) {
      int index = i * board_width + j;
      // If a tile contains a bomb (9)
      if (tiles[index].get_value() == 9) {

        // Then go through all spaces around the tile containing the bomb
        for (int ix = -1; ix <= 1; ix++) {
          for (int jx = -1; jx <= 1; jx++) {
            // coordinates for calculating index of neighboring tiles
            int x = i + ix;
            int y = j + jx;
            // If the space (one of the 8 around the bomb) is within the
            // bounds of the board
            if (x >= 0 && x < board_height && y >= 0 && y < board_width) {
              int surroundingIndex = x * board_width + y;
              // If the space is not already a bomb (9)
              if (tiles[surroundingIndex].get_value() != 9) {
                // Then increment the amount of bombs that space is touching by
                // 1
                tiles[surroundingIndex].set_value(
                    tiles[surroundingIndex].get_value() + 1);
              }
            }
          }
        }
      }
    }
  }
}

void Board::print() {
  // Prints top row of numbers
  std::cout << std::left << std::setw(1) << ' ';
  for (int k = 0; k < board_width; k++) {
    std::cout << "   " << k;
  }
  std::cout << std::endl;

  // Starts to print Board
  for (int i = 0; i < board_height; i++) {
    std::cout << std::left << std::setw(2) << ' ';
    for (int a = 0; a < board_width; a++) {
      std::cout << "|---";
    }
    std::cout << "|";
    std::cout << std::endl;
    // Prints the number of the row
    std::cout << i << ' ';
    for (int j = 0; j < board_width; j++) {
      int index = i * board_width + j;
      std::cout << "| ";
      tiles[index].display();
      std::cout << " ";
    }
    std::cout << "|";
    std::cout << std::endl;
  }
  std::cout << std::left << std::setw(2) << ' ';
  for (int b = 0; b < board_width; b++) {
    std::cout << "|---";
  }
  std::cout << "|";
  std::cout << std::endl;
}

bool Board::valid_dig(int row, int col) {
  if (row < 0 || row >= board_height || col < 0 || col >= board_width) {
    return false;
  } else {
    return true;
  }
}

void Board::reveal(int row, int col) {

  if (valid_dig(row, col) == false) {
    return;
  }

  int index = row * board_width + col;
  if (tiles[index].get_value() == 9) {
    has_lost = true;
    return;
  }

  if (tiles[index].get_revealed() == true) {
    return;
  }

  tiles[index].set_revealed(true);
  revealed_count++;

  if (revealed_count == (size - mine_count)) {
    has_won = true;
    return;
  }
}

void Board::display_revealed() {
  for (int i = 0; i < board_height; i++) {
    for (int j = 0; j < board_width; j++) {
      int index = i * board_width + j;
      tiles[index].set_revealed(true);
    }
  }

  print();
}

bool Board::get_has_won() const { return has_won; }

bool Board::get_has_lost() const { return has_lost; }

Board::~Board() { delete[] tiles; }