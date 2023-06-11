#include "map.h"

#include <iostream>
#include <iomanip>
#include "third_party_lib/tinyxml2.h"


static MapLayer parse_layer_from_csv_matrix(std::string csv_matrix);
static MapLine parse_line_from_csv_line(std::string csv_line);

Map Map::from_tmx(const std::string tmx_path) {
	using namespace tinyxml2;

	XMLDocument map_xml;
	map_xml.LoadFile(tmx_path.c_str());

  // Extract metadata
  XMLElement* root = map_xml.FirstChildElement("map");
  TileDimension map_shape = {atoi(root->Attribute("width")),
                                  atoi(root->Attribute("height"))};
  PixelDimension map_src_tileshape = {atoi(root->Attribute("tilewidth")),
                                       atoi(root->Attribute("tileheight"))};


	std::vector<MapLayer> layers;

	return Map(layers, map_shape, map_src_tileshape);
}

static void print_map_layer(MapLayer layer);
static void print_map_line(MapLine line);

void Map::log() {
	std::cout << "Map shape tilewise\t" << shape << std::endl;
	std::cout << "Source tile shape\t" << src_tileshape << std::endl;
	if (layers.size() == 0)
	{
		std::cout << "Map is empty" << std::endl;
		return;
	}

	for (size_t layer_idx = 0; layer_idx < layers.size(); layer_idx++) {
		std::cout << "Layer " << layer_idx << "\n";
		print_map_layer(layers.at(layer_idx));
	}
}

static void print_map_layer(MapLayer layer) {
	for (size_t line_idx = 0; layer.size(); line_idx++) {
		print_map_line(layer.at(line_idx));
	}
	std::cout << std::endl;
}

static void print_map_line(MapLine line) {
	for (size_t cell_idx = 0; cell_idx < line.size(); cell_idx++) {
		std::cout << std::setw(3) << line.at(cell_idx) << " ";
	}
	std::cout << "\n";
}
