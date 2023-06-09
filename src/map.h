#pragma once
#include <string>
#include <vector>

typedef std::vector<std::vector<int> > MapLayer;

class Map {
 public:
  static Map from_tmx(const std::string tmx_path);

  std::vector<MapLayer> layers;
};
