// Your Tile.h File
#ifndef _TILE_H
#define _TILE_H

class Tile {
private:
  int value;
  bool revealed;

public:
  Tile();

  void display();
  void set_revealed(bool);
  int get_value() const;
  void set_value(int);
  bool get_revealed() const;
};

#endif