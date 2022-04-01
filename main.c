#define RAYGUI_IMPLEMENTATION

#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include <shared.h>
#include <paddle.h>
#include <ball.h>
#include <game.h>

#include <GUI/startmenu.h>

float deltaTime = 0.0f;

int main(void) {
    srand(time(NULL));
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong\tFPS: Calculating...");

    paddle pongPaddle = { 2, 0, 20, 125, BLACK, {26, 550}};
    ball pongBall = { 5, 0, 50, LEFT, BLACK, {SCREEN_WIDTH/2, SCREEN_HEIGHT/2}};

    GameScreen currScreen = LOGO;
    char windowTitle[255] = {};
    int framesCounter = 0;

    float lastFrame = 0.0f, currentFrame = 0.0f;

    SetTargetFPS(FRAME_RATE);

    while (!WindowShouldClose()) {
        lastFrame = currentFrame;
        currentFrame = GetTime();
        deltaTime = (currentFrame - lastFrame) * 100;

        switch(currScreen){
            case LOGO:
                framesCounter++;

                //if(framesCounter > FRAME_RATE * 2)
                    currScreen = TITLE;

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
                    ShowTitleGui(&currScreen);
                    break;

                case GAMEPLAY:
                    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, PURPLE);

                    DrawRectangle(pongPaddle.pos.x, pongPaddle.pos.y, pongPaddle.width, pongPaddle.height, pongPaddle.color);
                    DrawCircleV(pongBall.pos, pongBall.radius, pongBall.color);
                    sprintf(windowTitle, "Pong\tFPS: %i", GetFPS());
                    SetWindowTitle(windowTitle);

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