// The implementation of the Tile.h file
#include "Tile.h"
#include <iostream>

Tile::Tile() {
  revealed = false;
  value = 0;
}

void Tile::set_revealed(bool status) { revealed = status; }

void Tile::display() {
  if (revealed) {
    if (value == 9){
      std::cout << "M";
    }else {
    std::cout << value;
    }  
  } else {
    std::cout << "#";
  }
}

int Tile::get_value() const { return value; }

void Tile::set_value(int val) { value = val; }

bool Tile::get_revealed() const { return revealed; }