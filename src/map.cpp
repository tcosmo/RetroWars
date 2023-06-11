#include "map.h"

#include "third_party_lib/tinyxml2.h"

typedef std::vector<int> MapLine;

static MapLayer parse_layer_from_csv_matrix(std::string csv_matrix);
static MapLine parse_line_from_csv_line(std::string csv_line);

Map Map::from_tmx(const std::string tmx_path) {
	Map map;

	return map;
}
