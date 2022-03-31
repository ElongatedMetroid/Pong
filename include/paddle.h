#ifndef PADDLE_H_
#define PADDLE_H_

#include <ball.h>
#include <shared.h>
#include <raylib.h>

typedef struct Paddle {
    float speed;
    float deltaSpeed;
    float width;
    float height;
    Color color;
    Vector2 pos;
} paddle;

void UpdatePaddlePos(paddle *pongPaddle, ball *pongBall);

#endif