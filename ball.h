/** @file ball.h
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief ball behaviour module
 */

#ifndef BALL_H
#define BALL_H

#include <stdint.h>
#include <bat.h>

#define BALL_LIMIT_LEFT 0
#define BALL_LIMIT_RIGHT 6
#define BALL_LIMIT_TOP 0
#define BALL_LIMIT_BOTTOM 5
#define HEIGHT 5
#define ALIVE 1
#define DEAD 0
#define BOTTOM 0
#define NOT_HERE 2

/** Ball structure */
typedef struct {
    uint8_t x;   // X position
    uint8_t y;   // Y position
    uint8_t status;
    int8_t y_dir;
    int8_t x_dir;
} Ball;

/** Initialise ball structure:
    @param ball pointer to struct being initialised
    @param x x coordinate to initialise ball at
    @param y y coordinate to initialise ball at
    @param x_dir initial horizontal component of direction
    @param y_dir initial vertical component of direction
    @param status if the ball is alive or dead*/
void ball_init(Ball* ball, uint8_t x, uint8_t y, int8_t y_dir, int8_t x_dir, uint8_t status); 

/** Moving Ball Down:
    @param ball pointer to struct being initialised
    @param bat pointer to struct being initialised */
void ball_move_down(Ball* ball, Bat* bat);

/** Moving Ball Up:
   @param ball pointer to ball struct*/
void ball_move_up(Ball* ball);

/** Moving Ball Left:
   @param ball pointer to ball struct*/
void ball_move_left(Ball* ball);

/** Moving Ball Right:
   @param ball pointer to ball struct*/
void ball_move_right(Ball* ball);

#endif