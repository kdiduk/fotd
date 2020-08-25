#ifndef PLAYER_H
#define PLAYER_H

#include <stdint.h>

enum direction {
    north,
    south,
    west,
    east,
    nortwest,
    northeast,
    southwest,
    southeast
};

void player_init(void);

void player_setpos(uint8_t x, uint8_t y);

uint8_t player_posx(void);

uint8_t player_posy(void);

void player_move(enum direction d);

void player_draw(void);

#endif /* PLAYER_H */
