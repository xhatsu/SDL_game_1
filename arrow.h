#pragma once
#include<cmath>
#include"entity.h"
extern SDL_Texture* boxTexture;
class arrow : public entity
{
public:
    int des_x, des_y;
    double Col_x=ObjCol.x, Col_y=ObjCol.y;
    double angle;
    double speed;
    // Calculate the direction vector
    int dx = des_x;
    int dy = des_y;
    arrow(int x, int y, int type,int state, int des_x, int des_y, double speed,double angle) : entity(x, y, type, state,speed), des_x(des_x), des_y(des_y), speed(speed), angle(angle) {
        object_texture_rect.x = 0;
        object_texture_rect.y = 0;
        object_texture_rect.w = 15;
        object_texture_rect.h = 1;
        objectRenderCordinate.w = object_texture_rect.w;
        objectRenderCordinate.h = object_texture_rect.h;
        
        setObjRenderCordinate();
    }

    void moveToDestination() {
        
        
        //Normalize direction vector
        double magnitude = sqrt(dx * dx + dy * dy);
        double dir_x = dx / magnitude;
        double dir_y = dy / magnitude;

        //Update position
        Col_x += dir_x * speed;
        Col_y += dir_y * speed;
        ObjCol.x = int(Col_x);
        ObjCol.y = int(Col_y);
        //
    }
    void updateArrow() {
        setObjRenderCordinate();
        moveToDestination();
        //SDL_RenderDrawLineF(renderer, 640, 360, des_x+640, des_y+360);
        SDL_RenderCopyEx(renderer, boxTexture, &object_texture_rect, &objectRenderCordinate, angle, NULL, SDL_FLIP_NONE);
    }
};

