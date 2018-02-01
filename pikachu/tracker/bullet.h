//
// Created by ysun3 on 11/24/17.
//

#ifndef INC_3_BULLET_H
#define INC_3_BULLET_H

#include <iostream>
#include "sprite.h"
#include "gamedata.h"

class Bullet : public Sprite {
public:
    explicit Bullet(const string& name) :
            Sprite(name),
            distance(0),
            maxDistance(Gamedata::getInstance().getXmlInt(name+"/distance")),
            tooFar(false)
    { }
    virtual void update(Uint32 ticks);
    bool goneTooFar() const { return tooFar; }
    void reset() {
        tooFar = false;
        distance = 0;
    }
    void collide() {tooFar = true;}

private:
    float distance;
    float maxDistance;
    bool tooFar;
};

#endif //INC_3_BULLET_H
