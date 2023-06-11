#pragma once
#include <string>
#include <vector>

#include "geometry.h"

typedef std::vector<int> MapLine;
typedef std::vector<MapLine> MapLayer;

class Map {
 public:
  static Map from_tmx(const std::string tmx_path);
  void log();

  std::vector<MapLayer> layers;
  TileDimension shape;
  PixelDimension src_tileshape;
};
