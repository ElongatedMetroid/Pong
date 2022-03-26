#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define FRAME_RATE 120

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
    Color color;
    Vector2 pos;
} paddle;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong\tFPS: Calculating...");

    paddle pongPaddle = { 2, 0, 20, 125, BLACK, {25, 100}};
    ball pongBall = { 2, 0, 50, BLACK, {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}};

    GameScreen currScreen = LOGO;
    char windowTitle[255] = {};
    int framesCounter = 0;

    float lastFrame = 0.0f, currentFrame = 0.0f;
    float deltaTime = 0.0f;

    SetTargetFPS(FRAME_RATE);

    while (!WindowShouldClose()) {
        lastFrame = currentFrame;
        currentFrame = GetTime();
        deltaTime = (currentFrame - lastFrame) * 100;
        pongBall.deltaSpeed = pongBall.speed * deltaTime;
        pongPaddle.deltaSpeed = pongPaddle.speed * deltaTime;
        sprintf(windowTitle, "Pong\tFPS: %i", GetFPS());

        switch(currScreen){
            case LOGO:
                framesCounter++;

                if(framesCounter > FRAME_RATE * 2)
                    currScreen = TITLE;

                break;
            case TITLE:
                if(IsKeyPressed(KEY_ENTER))
                    currScreen = GAMEPLAY;

                break;
            case GAMEPLAY:
                if(IsKeyPressed(KEY_ENTER))
                    currScreen = ENDING;

                break;
            case ENDING:
                if(IsKeyPressed(KEY_ENTER))
                    currScreen = TITLE;

                break;
            default: break;
        }

        if(pongBall.pos.x < (SCREEN_WIDTH - pongBall.radius + 1)){      // && pongBall.pos.x < SCREEN_WIDTH){
            if (IsKeyDown(KEY_RIGHT)) pongBall.pos.x += pongBall.deltaSpeed;
        } else
            pongBall.pos.x--;
        if(pongBall.pos.x > (0 + pongBall.radius - 1)){
            if (IsKeyDown(KEY_LEFT)) pongBall.pos.x -= pongBall.deltaSpeed;
        } else
            pongBall.pos.x++;
        
        if(pongBall.pos.y < (SCREEN_HEIGHT - pongBall.radius + 1)){
            if (IsKeyDown(KEY_DOWN)) pongBall.pos.y += pongBall.deltaSpeed;
        } else 
            pongBall.pos.y--;
        if(pongBall.pos.y > (0 + pongBall.radius - 1)){
            if (IsKeyDown(KEY_UP)) pongBall.pos.y -= pongBall.deltaSpeed;
        } else
            pongBall.pos.y++;

        // paddle controls
        if(pongPaddle.pos.y < (SCREEN_HEIGHT - pongPaddle.height + 1)){
            if(IsKeyDown(KEY_DOWN)) pongPaddle.pos.y += pongPaddle.deltaSpeed;
        } else
            pongPaddle.pos.y--;
        if(pongPaddle.pos.y > (0)){
            if(IsKeyDown(KEY_UP)) pongPaddle.pos.y -= pongPaddle.deltaSpeed;
        } else
            pongPaddle.pos.y++;

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
                    DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
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