#include "raylib.h"
#include <stdio.h>

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING} GameScreen;

typedef struct Ball {
    float speed;
    float radius;
    Color color;
    Vector2 pos;
} ball;

typedef struct Paddle {
    float speed;
    float width;
    float height;
    Color color;
    Vector2 pos;
} paddle;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong\tFPS: Calculating...");

    paddle pongPaddle = { 2, 20, 125, BLACK, {100, 100}};
    ball pongBall = { 2, 50, BLACK, {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}};

    GameScreen currScreen = LOGO;
    char windowTitle[255] = {};
    int framesCounter = 0;

    double lastTime = GetTime();
    double deltaTime = 0, nowTime = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        
        nowTime = GetTime();
        deltaTime += (nowTime - lastTime);
        lastTime = nowTime;

        sprintf(windowTitle, "Pong\tFPS: %i", GetFPS());

        switch(currScreen){
            case LOGO:
                framesCounter++;

                if(framesCounter > 120)
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
            if (IsKeyDown(KEY_RIGHT)) pongBall.pos.x += pongBall.speed;
        } else
            pongBall.pos.x--;
        if(pongBall.pos.x > (0 + pongBall.radius - 1)){
            if (IsKeyDown(KEY_LEFT)) pongBall.pos.x -= pongBall.speed;
        } else
            pongBall.pos.x++;
        
        if(pongBall.pos.y < (SCREEN_HEIGHT - pongBall.radius + 1)){
            if (IsKeyDown(KEY_DOWN)) pongBall.pos.y += pongBall.speed;
        } else 
            pongBall.pos.y--;
        if(pongBall.pos.y > (0 + pongBall.radius - 1)){
            if (IsKeyDown(KEY_UP)) pongBall.pos.y -= pongBall.speed;
        } else
            pongBall.pos.y++;

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
                    // TODO: Draw GAMEPLAY screen here!
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);
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

            DrawRectangle(pongPaddle.pos.x, pongPaddle.pos.y, pongPaddle.width, pongPaddle.height, pongPaddle.color);
            DrawCircleV(pongBall.pos, pongBall.radius, pongBall.color);
            SetWindowTitle(windowTitle);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}