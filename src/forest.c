#include <stdlib.h>
#include "forest.h"

/* macro implements a bitmask that returns bits
   representing the tile type from the map cell */
#define TILE_MASK_TYPE(tile) ((tile) & (0x07))

#define GROUND_PROBABILITY ((RAND_MAX / 7) * 4)
#define MAX_WIDTH (160)
#define MAX_HEIGHT (120)


static uint8_t width;
static uint8_t height;
static uint8_t map[MAX_WIDTH*MAX_HEIGHT];
static uint8_t spawnx;
static uint8_t spawny;


static void generate_forest(void);


void forest_init(void)
{
        width = 160; /* 5 screen levels */
        height = 120; /* 6 screen levels */
        generate_forest();

        do {
                spawnx = rand() % width;
                spawny = rand() % height;
        } while (forest_tile(spawnx, spawny) != tile_ground);
}

uint8_t forest_width(void)
{
        return width;
}

uint8_t forest_height(void)
{
        return height;
}

enum tile_type forest_tile(uint8_t x, uint8_t y)
{
        return TILE_MASK_TYPE(map[y*width+x]);
}

uint8_t forest_spawnx(void)
{
        return spawnx;
}

uint8_t forest_spawny(void)
{
        return spawny;
}

static void generate_forest(void)
{
        uint16_t yy = width * (height-1);
        for (uint8_t x = 0; x < width; ++x) {
                map[x] = tile_tree;
                map[yy + x] = tile_tree;
        }

        for (uint8_t y = 1; y < height-1; ++y) {
                yy = y * width;
                map[yy] = tile_tree;
                map[yy+width-1] = tile_tree;
                for (uint8_t x = 1; x < width-1; ++x) {
                        if (rand() < GROUND_PROBABILITY) {
                                map[yy+x] = tile_ground;
                        } else {
                                map[yy+x] = tile_tree;
                        }
                }
        }
}


/* EOF */
