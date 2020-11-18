#include <stdlib.h>
#include "forest.h"
#include "generator.h"
#include "tile.h"

#define RAND_VALUE (RAND_MAX / 2)

static uint8_t back_map[FOREST_HEIGHT][FOREST_WIDTH];

void generate_forest(uint8_t map[FOREST_HEIGHT][FOREST_WIDTH])
{
    for (uint8_t y = 0; y < FOREST_HEIGHT; ++y) {
	for (uint8_t x = 0; x < FOREST_WIDTH; ++x) {
	    if (rand() < RAND_VALUE) {
                 map[y][x] = tile_ground;
	    } else {
		map[y][x] = tile_tree;
	    }
	}
    }
}

/* EOF */
