#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define FRAME_RATE 60

float deltaTime = 0.0f;

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING} GameScreen;

typedef struct Ball {
    float speed;
    float deltaSpeed;
    float radius;
    #define LEFT 567678
    #define RIGHT 32768
    #define UP 3467
    #define DOWN 81267868
    // to go diagnal do direction = LEFT (yes, bitwise)& UP
    int direction;
    Color color;
    Vector2 pos;
} ball;

typedef struct Paddle {
    float speed;
    float deltaSpeed;
    float width;
    float height;
    Color color;
    Vector2 pos;
} paddle;

int ResetGame(paddle *Paddle, ball *Ball){
    Ball->pos.x = SCREEN_WIDTH/2;
    Ball->pos.y = SCREEN_HEIGHT/2;

    Paddle->pos.x = 26;
    Paddle->pos.y = 100;
}

int GetRandomDirection(int wall){
    int i = rand() % 3; // generate random number from 0 to 2

    switch(wall){
        case RIGHT:
            switch(i){
                case 0:
                    return LEFT;
                case 1:
                    return LEFT | UP;
                case 2:
                    return LEFT | DOWN;
            }
        case LEFT:
            switch(i){
                case 0:
                    return RIGHT;
                case 1:
                    return RIGHT | UP;
                case 2:
                    return RIGHT | DOWN;
            }
        case UP:
            switch(i){
                case 0:
                    return DOWN;
                case 1:
                    return DOWN | RIGHT;
                case 2:
                    return DOWN | LEFT;
            }
        case DOWN:
            switch(i){
                case 0:
                    return UP;
                case 1:
                    return UP | RIGHT;
                case 2:
                    return UP | LEFT;
            }
    }
}

void UpdateBallPos(ball *pongBall){
    pongBall->deltaSpeed = pongBall->speed * deltaTime;
    //ball movement
    if(!(pongBall->pos.x < (SCREEN_WIDTH - pongBall->radius + 1)))     //right 
        pongBall->direction = GetRandomDirection(RIGHT);
    if(!(pongBall->pos.x > (0 + pongBall->radius - 1)))                //left
        pongBall->direction = GetRandomDirection(LEFT);
                
    if(!(pongBall->pos.y < (SCREEN_HEIGHT - pongBall->radius + 1)))    // top
        pongBall->direction = GetRandomDirection(UP);
    if(!(pongBall->pos.y > (0 + pongBall->radius - 1)))                //bottom
        pongBall->direction = GetRandomDirection(DOWN);

    switch(pongBall->direction){
        case UP:
            pongBall->pos.y += pongBall->deltaSpeed;
            break;
        case DOWN:
            pongBall->pos.y -= pongBall->deltaSpeed;
            break;
        case LEFT:
            pongBall->pos.x -= pongBall->deltaSpeed;
            break;
        case RIGHT:
            pongBall->pos.x += pongBall->deltaSpeed;
            break;

        //diagnals
        case LEFT | UP:
            pongBall->pos.x -= pongBall->deltaSpeed/2;
            pongBall->pos.y += pongBall->deltaSpeed/2;
            break;
        case LEFT | DOWN:
            pongBall->pos.x -= pongBall->deltaSpeed/2;
            pongBall->pos.y -= pongBall->deltaSpeed/2;
            break;
        case RIGHT | UP:
            pongBall->pos.x += pongBall->deltaSpeed/2;
            pongBall->pos.y += pongBall->deltaSpeed/2;
            break;
        case RIGHT | DOWN:
            pongBall->pos.x += pongBall->deltaSpeed/2;
            pongBall->pos.y -= pongBall->deltaSpeed/2;
            break;
    }
}

void UpdatePaddlePos(paddle *pongPaddle, ball *pongBall){
    pongPaddle->deltaSpeed = pongPaddle->speed * deltaTime;
    // paddle collision
    if((pongBall->pos.x - (pongBall->radius + pongPaddle->width) - pongPaddle->pos.x) < 5.0           //x axis
        && pongBall->pos.y - pongPaddle->pos.y < 126 && pongBall->pos.y - pongPaddle->pos.y > 0){     //y axis
            pongBall->direction = GetRandomDirection(LEFT);
    }

    // paddle controls
    if(pongPaddle->pos.y < (SCREEN_HEIGHT - pongPaddle->height + 1)){
        if(IsKeyDown(KEY_DOWN)) pongPaddle->pos.y += pongPaddle->deltaSpeed;
    } else
        pongPaddle->pos.y--;
    if(pongPaddle->pos.y > (0)){
        if(IsKeyDown(KEY_UP)) pongPaddle->pos.y -= pongPaddle->deltaSpeed;
    } else
        pongPaddle->pos.y++;
}

int main(void) {
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong\tFPS: Calculating...");

    paddle pongPaddle = { 2, 0, 20, 125, BLACK, {26, 550}};
    ball pongBall = { 2, 0, 50, LEFT, BLACK, {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}};

    GameScreen currScreen = LOGO;
    char windowTitle[255] = {};
    int framesCounter = 0;

    float lastFrame = 0.0f, currentFrame = 0.0f;

    SetTargetFPS(FRAME_RATE);

    while (!WindowShouldClose()) {
        lastFrame = currentFrame;
        currentFrame = GetTime();
        deltaTime = (currentFrame - lastFrame) * 100;
        sprintf(windowTitle, "Pong\tFPS: %i", GetFPS());

        switch(currScreen){
            case LOGO:
                framesCounter++;

                //if(framesCounter > FRAME_RATE * 2)
                    currScreen = TITLE;

                break;
            case TITLE:
                if(IsKeyPressed(KEY_ENTER))
                    currScreen = GAMEPLAY;

                break;
            case GAMEPLAY:
                if(IsKeyDown(KEY_R))
                    ResetGame(&pongPaddle, &pongBall);

                UpdateBallPos(&pongBall);
                UpdatePaddlePos(&pongPaddle, &pongBall);

                if(pongBall.pos.x < pongPaddle.pos.x + pongBall.radius/2)
                    currScreen = ENDING;

                break;
            case ENDING:
                ResetGame(&pongPaddle, &pongBall);

                if(IsKeyPressed(KEY_ENTER))
                    currScreen = TITLE;

                break;
            default: break;
        }

        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            switch(currScreen){
                case LOGO:
                    // TODO: Draw LOGO screen here!
                    DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
                    DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);
                    break;
                case TITLE:
                    // TODO: Draw TITLE screen here!
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GREEN);
                    DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
                    DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
                    break;

                case GAMEPLAY:
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);

                    DrawRectangle(pongPaddle.pos.x, pongPaddle.pos.y, pongPaddle.width, pongPaddle.height, pongPaddle.color);
                    DrawCircleV(pongBall.pos, pongBall.radius, pongBall.color);
                    SetWindowTitle(windowTitle);

                    DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
                    break;

                case ENDING:
                    // TODO: Draw ENDING screen here!
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BLUE);
                    DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
                    DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);
                    break;
                default: break;
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}