//
// Created by ysun3 on 11/10/17.
//

#include <cmath>
#include <random>
#include <functional>
#include "smartSprite.h"
#include "gamedata.h"
#include "renderContext.h"

float distance(float x1, float y1, float x2, float y2) {
    float x = x1-x2;
    float y = y1-y2;
    return hypot(x, y);
}

SmartTwoWaySprite::SmartTwoWaySprite(const std::string& name) :
        TwoWayMultiSprite(name),
        playerPos()
{
    setPosition(Vector2f(drand48() * 1800, drand48() * 600));
}


SmartTwoWaySprite::SmartTwoWaySprite(const SmartTwoWaySprite& s) :
        TwoWayMultiSprite(s),
        playerPos(s.playerPos)
{}

void SmartTwoWaySprite::update(Uint32 ticks) {
    TwoWayMultiSprite::update(ticks);
    float x = playerPos[0] - getX();
    float y = playerPos[1] - getY();
    Vector2f vel(x,y);
    setVelocity(vel.normalize() * getVelocity().magnitude());
}