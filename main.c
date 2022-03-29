#include "raylib.h"
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define FRAME_RATE 60

float deltaTime = 0.0f;

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING} GameScreen;

typedef struct Ball {
    float speed;
    float deltaSpeed;
    float radius;
    Color color;
    Vector2 pos;
} ball;

typedef struct Paddle {
    float speed;
    float deltaSpeed;
    float width;
    float height;
    #define LEFT 0
    #define RIGHT 1
    #define UP 2
    #define DOWN 3
    // to go diagnal do direction = LEFT (yes, bitwise)& UP
    int direction;
    Color color;
    Vector2 pos;
} paddle;

void ResetGame(paddle *Paddle, ball *Ball){
    Ball->pos.x = SCREEN_WIDTH/2;
    Ball->pos.y = SCREEN_HEIGHT/2;

    Paddle->pos.x = 26;
    Paddle->pos.y = 100;
}

void UpdateBallPos(ball *pongBall){
    pongBall->deltaSpeed = pongBall->speed * deltaTime;
    //ball movement
    if(pongBall->pos.x < (SCREEN_WIDTH - pongBall->radius + 1)){
        if (IsKeyDown(KEY_RIGHT)) pongBall->pos.x += pongBall->deltaSpeed;
    } else // hit a wall
        pongBall->pos.x--;
    if(pongBall->pos.x > (0 + pongBall->radius - 1) || pongBall->pos.x){
        if (IsKeyDown(KEY_LEFT)) pongBall->pos.x -= pongBall->deltaSpeed;
    } else
        pongBall->pos.x++;
                
    if(pongBall->pos.y < (SCREEN_HEIGHT - pongBall->radius + 1)){
        if (IsKeyDown(KEY_DOWN)) pongBall->pos.y += pongBall->deltaSpeed;
    } else 
        pongBall->pos.y--;
    if(pongBall->pos.y > (0 + pongBall->radius - 1)){
        if (IsKeyDown(KEY_UP)) pongBall->pos.y -= pongBall->deltaSpeed;
    } else
        pongBall->pos.y++;
}

void UpdatePaddlePos(paddle *pongPaddle, ball *pongBall){
    pongPaddle->deltaSpeed = pongPaddle->speed * deltaTime;
    // paddle collision
    if((pongBall->pos.x - (pongBall->radius + pongPaddle->width) - pongPaddle->pos.x) < 5.0         //x axis
        && pongBall->pos.y - pongPaddle->pos.y < 126 && pongBall->pos.y - pongPaddle->pos.y > 0)     //y axis
            pongBall->pos.x += 20;

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
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong\tFPS: Calculating...");

    paddle pongPaddle = { 2, 0, 20, 125, LEFT, BLACK, {26, 550}};
    ball pongBall = { 2, 0, 50, BLACK, {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}};

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