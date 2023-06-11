#pragma once

#include <iostream>

class Dimension {
 public:
  int w;
  int h;

  Dimension(int w, int h) : w{w}, h{h} {}
  friend std::ostream& operator<<(std::ostream& os, const Dimension& dim);
};
