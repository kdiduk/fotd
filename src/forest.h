#ifndef FOREST_H
#define FOREST_H

#include <stdint.h>
#include "tile.h"

/* randomly generates a new forest
   and randomly sets player spawn point */
void forest_init(void);

/* forest always bigger than single screen */
uint8_t forest_width(void);
uint8_t forest_height(void);

enum tile_type forest_tile(uint8_t x, uint8_t y);

/* returns player's spawn point */
uint8_t forest_spawnx(void);
uint8_t forest_spawny(void);

#endif /* FOREST_H */
