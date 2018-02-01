//
// Created by ysun3 on 10/30/17.
//

#include "player.h"
#include "gamedata.h"
#include "ioMod.h"
#include "explodingSprite.h"

Player::Player(const std::string& name) : TwoWayMultiSprite(name),
                                          bullets(),
                                          maxSpeed(Gamedata::getInstance().getXmlFloat("playerMaxSpeed")),
                                          acceleration(Gamedata::getInstance().getXmlFloat("playerAcceleration")),
                                          damping(Gamedata::getInstance().getXmlFloat("playerDamping")),
                                          bulletName( Gamedata::getInstance().getXmlStr(name+"/bullet") ),
                                          minSpeed( Gamedata::getInstance().getXmlInt(bulletName+"/speedX") ),
                                          bulletInterval(Gamedata::getInstance().getXmlInt(bulletName+"/interval")),
                                          shootingTimeSinceLastFrame(0),
                                          lives(3),
                                          invincibleTime(0),
                                          jumping(false),
                                          godMode(false),
                                          win(false)
{}

Player::Player(const Player& player) : TwoWayMultiSprite(player),
                                       bullets(player.bullets),
                                       maxSpeed(player.maxSpeed),
                                       acceleration(player.acceleration),
                                       damping(player.damping),
                                       bulletName( Gamedata::getInstance().getXmlStr(player.bulletName) ),
                                       minSpeed(player.minSpeed),
                                       bulletInterval(player.bulletInterval),
                                       shootingTimeSinceLastFrame(player.timeSinceLastFrame),
                                       lives(player.lives),
                                       invincibleTime(player.invincibleTime),
                                       jumping(player.jumping),
                                       godMode(player.godMode),
                                       win(player.win)
{}

void Player::advanceFrame(Uint32 ticks) {
    timeSinceLastFrame += ticks;
    if (timeSinceLastFrame > frameInterval) {
        currentFrame = (currentFrame+1) % numberOfFrames;
        timeSinceLastFrame = 0;
    }
}

Player& Player::operator=(const Player& player)
{
    TwoWayMultiSprite::operator=(player);
    this->maxSpeed = player.maxSpeed;
    this->acceleration = player.acceleration;
    this->damping = player.damping;
    return *this;
}

void Player::left() {
    if(lives > 0) setVelocityX(-acceleration/1.5);
}

void Player::right() {
    if(lives > 0) setVelocityX(acceleration/1.5);
}

void Player::up() {
    if(lives > 0) setVelocityY(-acceleration/1.5);
}

void Player::down() {
    if(lives > 0) setVelocityY(acceleration/1.5);
}

void Player::jump() {
    if(!jumping && lives > 0) { setVelocityY((-acceleration)); jumping = true; }
}

void Player::damp() {
    float magnitude = getVelocity().magnitude();
    if(magnitude > maxSpeed) {
        //don't let player accelerate past max speed
        setVelocity(getVelocity().normalize() * maxSpeed);
    }
    else {
        if(magnitude > .01) {
            setVelocityX(getVelocityX() * damping);
        }
        else {
            setVelocityX(getVelocityX() * 0);
        }
    }
    if(jumping)
    {
        setVelocityY(getVelocityY() + acceleration / 30);
        if(getVelocityY() >= acceleration)
        {
            setVelocityY(0);
            jumping = false;
        }
    }
}

void Player::collided()
{
    if(lives > 0 && !explosion) lives--;
}

int Player::getLives() const
{
    return lives;
}

int Player::getInvincibleTime() const
{
    return invincibleTime;
}

bool Player::getGodMode() const
{
    return godMode;
}

bool Player::getWin() const
{
    return win;
}

void Player::setWin(bool tmp)
{
    win = tmp;
}

void Player::shoot(SDLSound& sound) {
    if(lives > 0 && !explosion) {
        if (shootingTimeSinceLastFrame < bulletInterval) return;
        sound[0];
        float deltaX = getScaledWidth();
        float deltaY = getScaledHeight() / 2;
        if (free_bullets.empty()) {
            Bullet bullet(bulletName);
            if (getVelocityX() >= 0) {
                bullet.setPosition(getPosition() + Vector2f(deltaX, deltaY));
                bullet.setVelocity(Vector2f(1, 0) * minSpeed);
            } else {
                bullet.setPosition(getPosition() + Vector2f(-deltaX, deltaY));
                bullet.setVelocity(Vector2f(-1, 0) * minSpeed);
            }

            bullets.push_back(bullet);
        } else {
            Bullet bullet = free_bullets.front();
            free_bullets.pop_front();
            bullet.reset();
            if (images == imagesRight) {
                bullet.setPosition(getPosition() + Vector2f(deltaX, deltaY));
                bullet.setVelocity(Vector2f(1, 0) * minSpeed);
            } else {
                bullet.setPosition(getPosition() + Vector2f(-deltaX, deltaY));
                bullet.setVelocity(Vector2f(-1, 0) * minSpeed);
            }

            bullets.push_back(bullet);
        }
        // I need to add some minSpeed to velocity:
        shootingTimeSinceLastFrame = 0;
    }
}

void Player::toggleGodMode()
{
    godMode = !godMode;
}

void Player::draw() const {
    if ( explosion ) explosion->draw();
    else if(lives > 0) TwoWayMultiSprite::draw();
    for ( const Bullet& bullet : bullets ) {
        bullet.draw();
    }
}

void Player::update(Uint32 ticks) {
    //Update invincible time
    if(invincibleTime > 0) {invincibleTime--;}

    //Update bullets
    for(auto iter = bullets.begin(); iter != bullets.end();)
    {
        if(iter -> goneTooFar())
        {
            free_bullets.push_back(*iter);
            iter = bullets.erase(iter);
        }
        else
        {
            iter -> update(ticks);
            ++iter;
        }
    }

    if ( explosion ) {
        explosion->update(ticks);
        if ( explosion->chunkCount() == 0 ) {
            delete explosion;
            explosion = NULL;
            invincibleTime = 150;
        }
        return;
    }

    shootingTimeSinceLastFrame += ticks;
    if(lives > 0) {
        if (getVelocityX() > 0) {
            images = imagesRight;
        } else if (getVelocityX() < 0) {
            images = imagesLeft;
        }

        damp();
        Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
        setPosition(getPosition() + incr);

        //Avoid the player goes outside the world
        if (getY() < 0) {
            setY(0);
        }
        if (getY() > worldHeight - getScaledHeight()) {
            setY(worldHeight - getScaledHeight());
        }
        if (getX() < 0) {
            setX(0);
        }
        if (getX() > worldWidth - getScaledWidth()) {
            setX(worldWidth - getScaledWidth());
        }
    }
    advanceFrame(ticks);
}