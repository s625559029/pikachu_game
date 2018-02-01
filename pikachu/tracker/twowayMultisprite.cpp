//
// Created by ysun3 on 10/18/17.
//

#include "twowayMultisprite.h"
#include "gamedata.h"
#include "renderContext.h"
#include "explodingSprite.h"

void TwoWayMultiSprite::advanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}

TwoWayMultiSprite::TwoWayMultiSprite( const std::string& name) :
        Drawable(name,
                 Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"),
                          Gamedata::getInstance().getXmlInt(name+"/startLoc/y")),
                 Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                          Gamedata::getInstance().getXmlInt(name+"/speedY"))
        ),
        explosion(nullptr),
        imagesLeft(ImageFactory::getInstance().getImages(name+"Left")),
        imagesRight(ImageFactory::getInstance().getImages(name)),
        images( imagesRight ),
        currentFrame(0),
        numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
        frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval")),
        timeSinceLastFrame( 0 ),
        worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
        worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
        endExpolsion(false)
{ }

TwoWayMultiSprite::TwoWayMultiSprite(const TwoWayMultiSprite& s) :
        Drawable(s),
        explosion(s.explosion),
        imagesLeft(s.imagesLeft),
        imagesRight(s.imagesRight),
        images(s.images),
        currentFrame(s.currentFrame),
        numberOfFrames( s.numberOfFrames ),
        frameInterval( s.frameInterval ),
        timeSinceLastFrame( s.timeSinceLastFrame ),
        worldWidth( s.worldWidth ),
        worldHeight( s.worldHeight ),
        endExpolsion( s.endExpolsion )
{ }

TwoWayMultiSprite::~TwoWayMultiSprite()
{
    if ( explosion ) delete explosion;
}

TwoWayMultiSprite& TwoWayMultiSprite::operator=(const TwoWayMultiSprite& s) {
    Drawable::operator=(s);
    explosion = s.explosion;
    imagesLeft = s.imagesLeft;
    imagesRight = s.imagesRight;
    images = (s.images);
    currentFrame = (s.currentFrame);
    numberOfFrames = ( s.numberOfFrames );
    frameInterval = ( s.frameInterval );
    timeSinceLastFrame = ( s.timeSinceLastFrame );
    worldWidth = ( s.worldWidth );
    worldHeight = ( s.worldHeight );
    endExpolsion = s.endExpolsion;
    return *this;
}

void TwoWayMultiSprite::draw() const {
    if ( explosion ) explosion->draw();
    else images[currentFrame]->draw(getX(), getY(), getScale());
}

void TwoWayMultiSprite::update(Uint32 ticks) {
    if ( explosion ) {
        explosion->update(ticks);
        if( explosion->chunkCount() < 3) {
            endExpolsion = true;
        }
        if ( explosion->chunkCount() == 0 ) {
            delete explosion;
            explosion = NULL;
        }
        return;
    }

    endExpolsion = false;
    advanceFrame(ticks);

    Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
    setPosition(getPosition() + incr);

    if ( getY() < 0) {
        setVelocityY( fabs( getVelocityY() ) );
    }
    if ( getY() > worldHeight-getScaledHeight()) {
        setVelocityY( -fabs( getVelocityY() ) );
    }

    if ( getX() < 0) {
        setVelocityX( fabs( getVelocityX() ) );
    }
    if ( getX() > worldWidth-getScaledWidth()) {
        setVelocityX( -fabs( getVelocityX() ) );
    }


    if(getVelocityX() > 0)
    {
        images = imagesRight;
    }
    else if(getVelocityX() < 0)
    {
        images = imagesLeft;
    }
}

void TwoWayMultiSprite::explode() {
    if ( !explosion ) explosion = new ExplodingSprite(*this);
}
