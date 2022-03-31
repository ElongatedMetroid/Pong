#include <ball.h>

int GetRandomDirection(int wall, ball *pongBall){
    int i = rand() % 3; // generate random number from 0 to 2

    switch(wall){
        case RIGHT: // bouncing off right wall
            if(pongBall->direction == RIGHT){ // if we were moving right before
                switch(i){
                    case 0:
                        return LEFT | UP;
                    case 1:
                        return LEFT | DOWN;
                    case 2:
                        return LEFT;
                }
            }
            else if(pongBall->direction == (UP | RIGHT))
                return LEFT | UP;
            else if(pongBall->direction == (DOWN | RIGHT))
                return LEFT | DOWN;
            else
                return LEFT;
        case LEFT:
            if(pongBall->direction == LEFT){ // if we were moving right before
                switch(i){
                    case 0:
                        return RIGHT | UP;
                    case 1:
                        return RIGHT | DOWN;
                    case 2:
                        return RIGHT;
                }
            }
            else if(pongBall->direction == (UP | LEFT))
                return RIGHT | UP;
            else if(pongBall->direction == (DOWN | LEFT))
                return RIGHT | DOWN;
            else
                return RIGHT;  
        case UP:
            if(pongBall->direction == UP){
                switch(i){
                    case 0:
                        return DOWN | LEFT;
                    case 1:
                        return DOWN | RIGHT;
                    default:
                        return DOWN | LEFT;
                }
            }
            else if(pongBall->direction == (UP | RIGHT))
                return DOWN | RIGHT;
            else if(pongBall->direction == (UP | LEFT))
                return DOWN | LEFT;
            else
                return DOWN;
        case DOWN:
            if(pongBall->direction == DOWN){
                case 0:
                    return UP | LEFT;
                case 1:
                    return UP | RIGHT;
                default:
                    return UP | LEFT;
            }
            else if(pongBall->direction == (DOWN | RIGHT))
                return UP | RIGHT;
            else if(pongBall->direction == (DOWN | LEFT))
                return UP | LEFT;
            else
                return UP;
    }

    return 0;
}

void UpdateBallPos(ball *pongBall){
    pongBall->deltaSpeed = pongBall->speed * deltaTime;
    //ball movement
    if(!(pongBall->pos.x < (SCREEN_WIDTH - pongBall->radius + 1)))     //right 
        pongBall->direction = GetRandomDirection(RIGHT, pongBall);
    if(!(pongBall->pos.x > (0 + pongBall->radius - 1)))                //left
        pongBall->direction = GetRandomDirection(LEFT, pongBall);
                
    if(!(pongBall->pos.y < (SCREEN_HEIGHT - pongBall->radius + 1)))    // top
        pongBall->direction = GetRandomDirection(UP, pongBall);
    if(!(pongBall->pos.y > (0 + pongBall->radius - 1)))                //bottom
        pongBall->direction = GetRandomDirection(DOWN, pongBall);

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