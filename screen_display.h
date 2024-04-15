/** @file screen_display.h
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief screen display
 */


#ifndef DISPLAY_H
#define DISPLAY_H

#include "display.h"
#include "pio.h"
#include "system.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "../fonts/font3x5_1.h"

#define PACER_RATE 500


void init_led_matrix (void);

void scroll_text(char* text);

void display_column (uint8_t row_pattern, uint8_t current_column);

uint8_t update_display (uint8_t bitmap[], uint8_t current_column);

#endif