#ifndef BALL_H_
#define BALL_H_

#include <raylib.h>
#include <stdlib.h>
#include <shared.h>

//numbers are random so bitwise operations/combining directions works
#define LEFT 567678
#define RIGHT 32768
#define UP 3467
#define DOWN 81267868

typedef struct Ball {
    float speed;
    float deltaSpeed;
    float radius;
    int direction;
    Color color;
    Vector2 pos;
} ball;

int GetRandomDirection(int wall, ball *pongBall);
void UpdateBallPos(ball *pongBall);

#endif