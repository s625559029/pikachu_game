//
// Created by ysun3 on 10/30/17.
//

#ifndef INC_3_PLAYER_H
#define INC_3_PLAYER_H

#include "twowayMultisprite.h"
#include "bullet.h"
#include "sound.h"
#include <list>

class Player : public TwoWayMultiSprite
{
public:
    Player(const std::string&);
    Player(const Player&);

    Player& operator=(const Player&);

    void up();
    void down();
    void left();
    void right();
    void jump();
    void damp();

    void collided();
    void missed();

    int getLives() const;
    int getInvincibleTime() const;
    bool getGodMode() const;
    bool getWin() const;
    void setWin(bool tmp);

    virtual void update(Uint32 ticks);
    virtual void draw() const;
    void shoot(SDLSound& sound);
    void toggleGodMode();

    unsigned long getBulletsCount() const { return bullets.size(); }
    unsigned long getFreeBulletsCount() const { return  free_bullets.size(); }

    std::list<Bullet> bullets;
    std::list<Bullet> free_bullets;

protected:
    void advanceFrame(Uint32 ticks);

private:
    float maxSpeed;
    float acceleration;
    float damping;

    std::string bulletName;
    float minSpeed;
    float bulletInterval;
    float shootingTimeSinceLastFrame;

    int lives;
    int invincibleTime;

    bool jumping;
    bool godMode;
    bool win;
};

#endif //INC_3_PLAYER_H
