#include "forest.h"
#include "generator.h"

#define TILE_MASK_TYPE(tile) ((tile) & (0x07))


static uint8_t map[FOREST_HEIGHT][FOREST_WIDTH];


void forest_init(void)
{
    generate_forest(map);
}

enum tile_type forest_tile(uint8_t x, uint8_t y)
{
    return TILE_MASK_TYPE(map[y][x]);
}

uint8_t forest_entrance_x(void)
{
    return 1;
}

uint8_t forest_entrance_y(void)
{
    return 9;
}

uint8_t forest_exit_x(void)
{
    return 31;
}

uint8_t forest_exit_y(void)
{
    return 9;
}

/* EOF */
