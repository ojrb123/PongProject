/** @file bat.c
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief bat behaviour module
 */

#include <stdint.h>
#include "bat.h"
#include "pio.h"
#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "screen_display.h"
#include "ball.h"

void display_pixel_set(int y, int x, int val);

uint8_t get_bat_loc (Bat* bat) 
{
    return bat->pos;
}

void bat_init (Bat* bat) 
{
    bat->pos = BAT_START_POS;
    bat_bitmap(bat);
}

void bat_bitmap (Bat* bat)
{
    display_pixel_set(BAT_COL, BAT_LIMIT_RIGHT - bat->pos, 1);
    if (bat->pos > BAT_LIMIT_LEFT) {
        display_pixel_set(BAT_COL, BAT_LIMIT_RIGHT - bat->pos + 1, 1);
    }
    if (bat->pos < BAT_LIMIT_RIGHT) {
        display_pixel_set(BAT_COL, BAT_LIMIT_RIGHT - bat->pos - 1, 1);
    }
}

void bat_left (Bat* bat)
{
    if (bat->pos > BAT_LIMIT_LEFT) {
        bat->pos--;
    }
}

void bat_right (Bat* bat)
{
    if (bat->pos < BAT_LIMIT_RIGHT) {
        bat->pos++;
    }
}