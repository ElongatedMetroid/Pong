#include <paddle.h>

void UpdatePaddlePos(paddle *pongPaddle, ball *pongBall){
    pongPaddle->deltaSpeed = pongPaddle->speed * deltaTime;
    // paddle collision
    if((pongBall->pos.x - (pongBall->radius + pongPaddle->width) - pongPaddle->pos.x) < 5.0           //x axis
        && pongBall->pos.y - pongPaddle->pos.y < 126 && pongBall->pos.y - pongPaddle->pos.y > 0){     //y axis
            pongBall->direction = GetRandomDirection(LEFT, pongBall);
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