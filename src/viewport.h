/*
 * file: viewport.h
 *
 * The module 'viewport' represents the main part of the in-level game screen
 * that shows the current visible portion of the level where the player is.
 *
 * The main purpose of this module is to implement optimal draw of the
 * level and per-tile scrolling.
 */
#ifndef VAGABOND_VIEWPORT_H
#define VAGABOND_VIEWPORT_H

#include <stdint.h>

void viewport_init(void);

/* Update the tile at a given position.
 * 
 * Changes made with this function will be visible with the next call
 * of 'viewport_render()' function.
 *
 * Coordinates are relative, i.e. start from 0.
 */
void viewport_at(uint8_t x, uint8_t y, char ch, uint8_t ink);

void viewport_invalidate(uint8_t x, uint8_t y);

void viewport_render(void);


#endif /* VAGABOND_VIEWPORT_H */
