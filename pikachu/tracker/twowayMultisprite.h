//
// Created by ysun3 on 10/18/17.
//

#ifndef INC_3_TWOWAYMULTISPRITE_H
#define INC_3_TWOWAYMULTISPRITE_H

#include <string>
#include <vector>
#include <cmath>
#include "drawable.h"

class ExplodingSprite;

class TwoWayMultiSprite : public Drawable {
public:
    TwoWayMultiSprite(const std::string&);
    TwoWayMultiSprite(const TwoWayMultiSprite&);
    ~TwoWayMultiSprite();

    virtual void draw() const;
    virtual void update(Uint32 ticks);

    virtual const Image* getImage() const {
        return images[currentFrame];
    }
    int getScaledWidth()  const {
        return getScale()*images[currentFrame]->getWidth();
    }
    int getScaledHeight()  const {
        return getScale()*images[currentFrame]->getHeight();
    }
    virtual const SDL_Surface* getSurface() const {
        return images[currentFrame]->getSurface();
    }
    void setImagesLeft()
    {
        images = imagesLeft;
    }
    void setImagesRight()
    {
        images = imagesRight;
    }

    virtual void explode();

    bool getEndExplosion() { return endExpolsion; }

    ExplodingSprite* explosion;

protected:
    std::vector<Image *> imagesLeft;
    std::vector<Image *> imagesRight;
    std::vector<Image *> images;

    unsigned currentFrame;
    unsigned numberOfFrames;
    unsigned frameInterval;
    float timeSinceLastFrame;
    int worldWidth;
    int worldHeight;

    bool endExpolsion;

    void advanceFrame(Uint32 ticks);
    TwoWayMultiSprite& operator=(const TwoWayMultiSprite&);
};

#endif //INC_3_TWOWAYMULTISPRITE_H
