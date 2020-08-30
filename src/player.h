#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>


void player_init(void);

void player_setpos(uint8_t x, uint8_t y);

void player_moveby(uint8_t dx, uint8_t dy);

uint8_t player_posx(void);

uint8_t player_posy(void);

void player_move(uint8_t direction);

#endif /* PLAYER_H */
