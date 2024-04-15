/** @file game.c
 * @author Oliver Butler, William Hogan,
 * @Group 422
 * @date 19 October 2023
 * @brief main game
 */


#include <stdint.h>
#include "system.h"
#include "bat.h"
#include "ball.h"
#include "screen_display.h"
#include "navswitch.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "ir_uart.h"
#include <stdio.h>

#define START_MENU 0
#define WAITING_PLAYER 1
#define PLAY_GAME 2

#define TICK_RATE 300
#define TYPE 10
#define UP 1
#define DOWN -1

#define INITIAL_COlUMN_VALUE 0

int game_started = 0; 
int tick;

/* Game structure*/
typedef struct {
    uint8_t game_mode;
    uint8_t column_count;
} Game;

Ball ball;
Game game;
Bat bat;

void display_pixel_set(int y, int x, int val);


/** Wait for user to signal they wish to begin game:
    @param game a pointer to the game object */
static void game_menu(Game* game)
{
    tinygl_update();
    navswitch_update();
    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
        game->game_mode = PLAY_GAME;
        ball_init(&ball, 3, 0, 1, 0, ALIVE);
        bat_init(&bat);
        ir_uart_putc('S');
    }
    if (ir_uart_read_ready_p()) {
        char ch = ir_uart_getc();
        if (ch == 'S') {
            ball_init(&ball, 3, 0, 1, 0, NOT_HERE);
            bat_init(&bat);
            tinygl_clear();
            game->game_mode = PLAY_GAME;
        }
    }
}


/** Recieves the ball once at top of matrix
    @param ball a pointer to the ball object */
static void receive_ball(Ball* ball) {
    char ch9 = ir_uart_getc();
    if (ch9 == 'A') {
        ball->status = ALIVE;
    }
}

/** Moves the bat based on navswitch pushes
    @param bat a pointer to the bat object */
static void move_bat(Bat* bat) 
{

    navswitch_update();

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        bat_left(bat);
    }
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        bat_right(bat);
    }
}

/** Updates the display based on inputs
    @param bat a pointer to the bat object
    @param ball a pointer to the ball object */
static void update_game(Bat* bat,Ball* ball)
{
    move_bat(bat);
    bat_bitmap(bat);
    tinygl_update();
    display_pixel_set(ball->y, ball->x, 1);
    tinygl_update();
}

/** Moves the ball based on bat pos
    @param bat a pointer to the bat object
    @param ball a pointer to the ball object */
static void move_ball(Ball* ball, Bat* bat)
{
    if(ball->y_dir == 1 && ball->x_dir == 0) {
        ball_move_down(ball, bat);
    } else if (ball->y_dir == -1 && ball->x_dir == 0) {
        ball_move_up(ball);
    }

    if(ball->y_dir == -2 && ball->x_dir == 2) {
        ball_move_left(ball);
    }
    if(ball->y_dir == -2 && ball->x_dir == -2) {
        ball_move_right(ball);
    }

}


/** Initialise each of the components */
static void initialise (void)
{
    system_init();
    pacer_init(TICK_RATE);
    navswitch_init();
    init_led_matrix();
    ir_uart_init();
}


int main (void)
{
    // initialise game play variables
    initialise();
    Game game = {
        START_MENU,
        INITIAL_COlUMN_VALUE
    };
    bat_init(&bat);

    //set scroll text to main menu
    scroll_text("PRESS TO START");
    while (1)
    {
        pacer_wait();
        
        switch(game.game_mode) {
            case START_MENU:
                game_menu(&game);
                break;
            case PLAY_GAME:
                tinygl_clear();
                update_game(&bat, &ball);
                if(ball.status == DEAD) {
                    scroll_text("PRESS TO START");
                    game.game_mode = START_MENU;
                }
                tick ++;
                if (tick >= 80) {
                    tick = 0;
                    if (ball.status == ALIVE) {
                        move_ball(&ball, &bat);
                    } else {
                        receive_ball(&ball);
                        ball.y_dir*=-1;
    

                    }
                
                }   
                break;
        }
    }

}