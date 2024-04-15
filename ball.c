/** @file ball.c
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief ball behaviour module
 */


#include <stdint.h>
#include "display.h"
#include "pio.h"
#include "ball.h"
#include "bat.h"
#include "system.h"
#include "screen_display.h"
#include "ir_uart.h"

int8_t game_over = 0;


/** Initialise ball structure:
    @param ball pointer to struct being initialised
    @param x x coordinate to initialise ball at
    @param y y coordinate to initialise ball at
    @param x_dir initial horizontal component of direction
    @param y_dir initial vertical component of direction
    @param status if the ball is alive or dead*/
void ball_init(Ball* ball, uint8_t x, uint8_t y, int8_t y_dir, int8_t x_dir, uint8_t status) 
{
    ball->x = x;
    ball->y = y;
    ball->status = status;
    ball->x_dir = x_dir;
    ball->y_dir = y_dir;
}

/** Moving Ball Down:
    @param ball pointer to struct being initialised
    @param bat pointer to struct being initialised */
void ball_move_down(Ball* ball, Bat* bat)
{
    if (ball->y < HEIGHT-1) {
        ball->y++;
    } 
    else {
        // Ball has hit the bottom wall
        ball->y_dir = -1;
    }
    
    if (ball->y == 3 && ball->x == bat->pos) {
        ball->y_dir = -1;
    } 
    if (ball->y == 4 && ball->x == bat->pos + 1) {
        ball->y_dir = -2;
        ball->x_dir = 2;
    }
    if (ball->y == 3 && ball->x == bat->pos - 1) {
        ball->y_dir = -2;
        ball->x_dir = -2;
    }
    
}

/** Moving Ball Up:
   @param ball pointer to ball struct*/
void ball_move_up(Ball* ball)
{
    if (ball->y > 0 ) {
        ball->y--;
    } 
    else if (ball->y == 0) {
        char ch3 = 'A';
        ir_uart_putc(ch3); 
        ball->status = NOT_HERE;
        }
}

/** Moving Ball Left:
   @param ball pointer to ball struct*/
void ball_move_left(Ball* ball)
{
    if (ball->x < BALL_LIMIT_RIGHT) {
        ball->y--;
        ball->x++;
    } else {
        ball->x--;
        ball->y--;
    }
}

/** Moving Ball Right:
   @param ball pointer to ball struct*/
void ball_move_right(Ball* ball)
{
    if (ball->x > BALL_LIMIT_LEFT) {
        ball->y--;
        ball->x--;
    } else {
        ball->x++;
        ball->y--;
    }
}