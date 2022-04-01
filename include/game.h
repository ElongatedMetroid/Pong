#ifndef GAME_H_
#define GAME_H_

#include <raylib.h>
#include <shared.h>
#include <paddle.h>
#include <ball.h>

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

void ResetGame(paddle *Paddle, ball *Ball);

#endif