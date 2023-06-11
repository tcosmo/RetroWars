#pragma once
#include <string>
#include <vector>

#include "geometry.h"

typedef std::vector<int> MapLine;
typedef std::vector<MapLine> MapLayer;

class Map {
 public:
  Map(std::vector<MapLayer> layers,
      TileDimension shape,
      PixelDimension src_tileshape)
      : layers{layers}, shape{shape}, src_tileshape{src_tileshape} {};
  static Map from_tmx(const std::string tmx_path);
  void log() const;

  std::vector<MapLayer> layers;
  TileDimension shape;
  PixelDimension src_tileshape;
};
