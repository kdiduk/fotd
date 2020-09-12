#ifndef FOREST_H
#define FOREST_H

#include <stdint.h>
#include "tile.h"

#define FOREST_WIDTH (32)
#define FOREST_HEIGHT (20)

void forest_init(void);

enum tile_type forest_tile(uint8_t x, uint8_t y);

uint8_t forest_entrance_x(void);
uint8_t forest_entrance_y(void);

uint8_t forest_exit_x(void);
uint8_t forest_exit_y(void);


#endif /* FOREST_H */
