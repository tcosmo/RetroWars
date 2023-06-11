#include "map.h"

#include <iostream>
#include <iomanip>
#include "third_party_lib/tinyxml2.h"
#include "string.h"

using namespace tinyxml2;

static std::vector<MapLayer> parse_layers_from_list(const XMLElement* head);

Map Map::from_tmx(const std::string tmx_path) {

	XMLDocument map_xml;
	map_xml.LoadFile(tmx_path.c_str());

  // Extract metadata
  const XMLElement* root = map_xml.FirstChildElement("map");
  const TileDimension map_shape = {atoi(root->Attribute("width")),
                                  atoi(root->Attribute("height"))};
  const PixelDimension map_src_tileshape = {atoi(root->Attribute("tilewidth")),
                                       atoi(root->Attribute("tileheight"))};

	// Extract map layers
	const std::vector<MapLayer> layers = parse_layers_from_list(
			root->FirstChildElement("layer"));

	return Map(layers, map_shape, map_src_tileshape);
}

static MapLayer parse_layer_from_csv_sheet(const char* csv_sheet);
static MapLine parse_line_from_csv_line(const char* csv_line);

static std::vector<MapLayer> parse_layers_from_list(const XMLElement* head) {
	std::vector<MapLayer> layers;

	while (head != NULL) {
		const char* current_layer_csv = head->FirstChildElement("data")->GetText();
    const MapLayer current_layer = parse_layer_from_csv_sheet(current_layer_csv);
		layers.push_back(current_layer);

		head = head->NextSiblingElement();
	}

	return layers;
}

static MapLayer parse_layer_from_csv_sheet(const char* csv_sheet) {
  MapLayer output;

  const char* line_delim = "\n";

  char* str_line;
  char* mem;
  str_line = strtok_r((char*)csv_sheet, line_delim, &mem);

  while (str_line != NULL) {
    const MapLine map_line = parse_line_from_csv_line(str_line);
    output.push_back(map_line);

    str_line = strtok_r(NULL, line_delim, &mem);
  }

  return output;
}

static MapLine parse_line_from_csv_line(const char* csv_line) {
  MapLine output;

  const char* cell_delim = ",";

  char* cell;
  char* mem;
  cell = strtok_r((char*)csv_line, cell_delim, &mem);

  while (cell != NULL) {
    output.push_back(atoi(cell));

    cell = strtok_r(NULL, cell_delim, &mem);
  }

  return output;
}

static void print_map_layer(const MapLayer layer);
static void print_map_line(const MapLine line);

void Map::log() const {
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

static void print_map_layer(const MapLayer layer) {
	for (auto & line : layer) {
		print_map_line(line);
	}
	std::cout << std::endl;
}

static void print_map_line(const MapLine line) {
	for (auto & cell : line) {
		std::cout << std::setw(3) << cell << " ";
	}
	std::cout << "\n";
}
