// The Board.h header file
#ifndef _BOARD_H
#define _BOARD_H

#include "Tile.h"
#include <array>
#include <string>

class Board {
private:
  void place_mines(int);
  void update_counts();

  int mine_count;
  int board_width;
  int board_height;
  int size;
  int revealed_count {0};

  bool has_won {false};
  bool has_lost {false};
  bool valid_dig(int, int);
  
  // Pointer used so that we can dynamically allocate the tiles in implementation file
  Tile *tiles;

public:
  Board();
  Board(int, int, int);
  ~Board();
  void print();
  void reveal(int, int);
  void display_revealed();
  bool get_has_won() const;
  bool get_has_lost() const;
};

#endif