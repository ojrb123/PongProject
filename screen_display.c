/** @file screen_display.c
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief screen display
 */


#include "screen_display.h"


#define MESSAGE_RATE 50

/** Define PIO pins driving LED matrix rows. */

static const pio_t rows[] = {
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO,
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};


/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] = {
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


/** Initialise the columns of the led matrix: */
void init_led_matrix (void)
{
    /* Initialise LED matrix pins.  */
    for (int i = 0; i < 5; i++) {
        pio_config_set(cols[i], PIO_OUTPUT_HIGH);
    }
    for (int i = 0; i < 7; i++) {
        pio_config_set(rows[i], PIO_OUTPUT_HIGH);
    }
}

static pio_t prev;

void display_column (uint8_t row_pattern, uint8_t current_column)
{
    pio_output_high(cols[prev]);
    prev = current_column;
    for (int current_row = 0; current_row < 7; current_row++) {
        if ((row_pattern >> current_row) & 1) {
            pio_output_low(rows[current_row]);
        } else {
            pio_output_high(rows[current_row]);
        }
    }
    pio_output_low(cols[current_column]);
}

/** Update the led matrix:
    @param bitmap the pattern to light up
    @param current_column the column we are in
    @return next col*/
uint8_t update_display (uint8_t bitmap[], uint8_t current_column)
{
    display_column (bitmap[current_column], current_column);

    current_column++;
    if (current_column > (LEDMAT_COLS_NUM - 1)) {
        current_column = 0;
    }
    return current_column;
}

/** Setup tinygl to display given text:
    @param text, the characters to display */
void scroll_text (char* text)
{
    tinygl_init (300);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set(TINYGL_TEXT_DIR_ROTATE);
    tinygl_text(text);
    tinygl_update();

}