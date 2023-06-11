#pragma once
#include <string>
#include <vector>

#include "geometry.h"

typedef std::vector<std::vector<int> > MapLayer;

class Map {
 public:
  static Map from_tmx(const std::string tmx_path);

  std::vector<MapLayer> layers;
  TileDimension shape;
  PixelDimension src_tileshape;
};
