/** @file bat.h
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief bat behaviour module
 */

#ifndef BAT_H
#define BAT_H

#define BAT_LIMIT_LEFT 0
#define BAT_LIMIT_RIGHT 6
#define BAT_WIDTH 3
#define BAT_COL 4
#define BAT_START_POS 1

/** Sets bat struct */
typedef struct {
    uint8_t pos;
} Bat;

/** Gets the bat location:
    @param bat*/
uint8_t get_bat_loc (Bat* bat);

/** Initalises the bat
    @param bat*/
void bat_init (Bat* bat);

/** Moves bat left
    @param bat*/
void bat_left (Bat* bat);

/** Initialises bat */
void bat_bitmap (Bat* bat);


/** Moves bat left
    @param bat*/
void bat_right (Bat* bat);


#endif