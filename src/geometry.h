#pragma once

#include <iostream>

class Dimension {
 public:
  int w;
  int h;

  Dimension(int w = 0, int h = 0) : w{w}, h{h} {}
  friend std::ostream& operator<<(std::ostream& os, const Dimension& dim);
};

class TileDimension : public Dimension {
 public:
  TileDimension(int w = 0, int h = 0) : Dimension(w, h) {}
};

class PixelDimension : public Dimension {
 public:
  PixelDimension(int w = 0, int h = 0) : Dimension(w, h) {}
};
