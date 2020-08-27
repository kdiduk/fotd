#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>


void level_init(void);

void level_draw(void);

void level_player_move(uint8_t direction);

#endif /* LEVEL_H */
