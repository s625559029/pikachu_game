//
// Created by ysun3 on 11/10/17.
//

#ifndef INC_3_SMARTSPRITE_H
#define INC_3_SMARTSPRITE_H

#include "twowayMultisprite.h"

class SmartTwoWaySprite : public TwoWayMultiSprite
{
public:
    SmartTwoWaySprite(const std::string&);
    SmartTwoWaySprite(const SmartTwoWaySprite&);

    virtual void update(Uint32 ticks);
    void setPlayerPos(const Vector2f& p) { playerPos = p; }

private:
    Vector2f playerPos;
};

#endif //INC_3_SMARTSPRITE_H
