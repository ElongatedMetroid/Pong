#include <game.h>

void ResetGame(paddle *Paddle, ball *Ball){
    Ball->pos.x = SCREEN_WIDTH/2;
    Ball->pos.y = SCREEN_HEIGHT/2;
    Ball->direction = LEFT;

    Paddle->pos.x = 26;
    Paddle->pos.y = 100;
}