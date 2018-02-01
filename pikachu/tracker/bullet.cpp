//
// Created by ysun3 on 11/24/17.
//

#include <iostream>
#include <cmath>
#include "bullet.h"

void Bullet::update(Uint32 ticks) {
    Vector2f pos = getPosition();
    Sprite::update(ticks);
    distance += ( hypot(getX()-pos[0], getY()-pos[1]) );
    if (distance > maxDistance) tooFar = true;
    if(getY() < 0 || getY() + getScaledHeight() > worldHeight) tooFar = true;
    if(getX() < 0 || getX() > worldWidth) tooFar = true;
}
