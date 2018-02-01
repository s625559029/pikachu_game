//
// Created by ysun3 on 11/9/17.
//

#ifndef INC_3_PERPIXELCOLLISION_H
#define INC_3_PERPIXELCOLLISION_H

#include <cmath>
#include "drawable.h"

class CollisionStrategy {
public:
    virtual bool execute(const Drawable&, const Drawable&) const = 0;
    virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
    RectangularCollisionStrategy() {}
    virtual bool execute(const Drawable&, const Drawable&) const;
};

class MidPointCollisionStrategy : public CollisionStrategy {
public:
    MidPointCollisionStrategy() {}
    virtual bool execute(const Drawable&, const Drawable&) const;
    float distance(float, float, float, float) const;
};

class PerPixelCollisionStrategy : public CollisionStrategy {
public:
    PerPixelCollisionStrategy() {}
    virtual bool execute(const Drawable&, const Drawable&) const;
private:
    bool isVisible(Uint32, SDL_Surface*) const;
};



#endif //INC_3_PERPIXELCOLLISION_H
