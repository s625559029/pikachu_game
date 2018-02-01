#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <random>
#include <iomanip>
#include "sprite.h"
#include "gamedata.h"
#include "engine.h"
#include "frameGenerator.h"
#include "smartSprite.h"

Engine::~Engine() {
    delete player;
    delete overhud;
    for(auto i = sprites.begin(); i != sprites.end(); i++)
    {
        delete *i;
    }
    for(auto i = remote_sprites.begin(); i != remote_sprites.end(); i++)
    {
        delete *i;
    }
    for(auto i = strategies.begin(); i != strategies.end(); i++)
    {
        delete *i;
    }
}

Engine::Engine() :
        rc( RenderContext::getInstance() ),
        io( IOmod::getInstance() ),
        clock( Clock::getInstance() ),
        renderer( rc->getRenderer() ),
        night("night", Gamedata::getInstance().getXmlInt("night/factor")),
        mountains("mountains", Gamedata::getInstance().getXmlInt("mountains/factor")),
        castle("castle", Gamedata::getInstance().getXmlInt("castle/factor") ),
        road("road", Gamedata::getInstance().getXmlInt("road/factor")),
        player(new Player("Pikachu")),
        goal(MultiSprite("Ash")),
        viewport( Viewport::getInstance() ),
        sprites(),
        remote_sprites(),
        strategies(),
        currentStrategy(1),
        player_collision(false),
        enemy_collision(false),
        hud(HUD::getInstace()),
        poolhud(*player),
        overhud(new GameoverHUD()),
        sound(),
        currentSprite(0),
        makeVideo( false ),
        final(false)
{
    for(int i = 0; i < 9; i++) {
        Drawable *bat(new MultiSprite("Bat"));
        bat->setX(drand48()*1500);
        bat->setY(drand48()*500);
        bat->setVelocity(Vector2f(bat->getVelocity().magnitude() * drand48(), bat->getVelocity().magnitude() * drand48()));
        bat->setScale(0.3);
        remote_sprites.push_back(bat);
    }

    InitMonsters();

    Viewport::getInstance().setObjectToTrack(player);

    strategies.push_back( new RectangularCollisionStrategy );
    strategies.push_back( new PerPixelCollisionStrategy );
    strategies.push_back( new MidPointCollisionStrategy );

    std::cout << "Loading complete" << std::endl;
}

void Engine::InitMonsters()
{
    //Init monsters
    Drawable* Haunter(new SmartTwoWaySprite("Haunter"));
    Haunter->setX(2600);
    Drawable* Haunter_1(new SmartTwoWaySprite("Haunter"));
    Haunter_1->setX(3800);
    Drawable* Haunter_2(new SmartTwoWaySprite("Haunter"));
    Haunter_2->setX(3800);
    Haunter_2->setY(220);
    Drawable* Haunter_3(new SmartTwoWaySprite("Haunter"));
    Haunter_3->setX(3800);
    Haunter_3->setY(500);
    Drawable* Haunter_4(new SmartTwoWaySprite("Haunter"));
    Haunter_4->setX(4500);
    Drawable* Haunter_5(new SmartTwoWaySprite("Haunter"));
    Haunter_5->setX(4500);
    Haunter_4->setY(450);
    Drawable* Haunter_6(new SmartTwoWaySprite("Haunter"));
    Haunter_6->setX(5000);
    Haunter_6->setY(10);
    Drawable* Haunter_7(new SmartTwoWaySprite("Haunter"));
    Haunter_7->setX(5000);
    Haunter_7->setY(500);
    Drawable* Haunter_8(new SmartTwoWaySprite("Haunter"));
    Haunter_8->setX(5100);
    Haunter_8->setY(100);
    Drawable* Haunter_9(new SmartTwoWaySprite("Haunter"));
    Haunter_9->setX(5100);
    Haunter_9->setY(400);
    Drawable* Haunter_10(new SmartTwoWaySprite("Haunter"));
    Haunter_10->setX(6200);
    Haunter_10->setY(10);
    Drawable* Haunter_11(new SmartTwoWaySprite("Haunter"));
    Haunter_11->setX(6300);
    Haunter_11->setY(210);
    Drawable* Haunter_12(new SmartTwoWaySprite("Haunter"));
    Haunter_12->setX(6200);
    Haunter_12->setY(420);
    Drawable* Haunter_13(new SmartTwoWaySprite("Haunter"));
    Haunter_13->setX(7800);
    Haunter_13->setY(20);
    Drawable* Haunter_14(new SmartTwoWaySprite("Haunter"));
    Haunter_14->setX(7800);
    Haunter_14->setY(500);

    Drawable* Gastly(new TwoWayMultiSprite("Gastly"));
    Gastly->setX(3200);
    Drawable* Gastly_1(new TwoWayMultiSprite("Gastly"));
    Gastly_1->setX(3300);
    Drawable* Gastly_2(new TwoWayMultiSprite("Gastly"));
    Gastly_2->setX(3400);
    Drawable* Gastly_3(new TwoWayMultiSprite("Gastly"));
    Gastly_3->setX(4500);
    Drawable* Gastly_4(new TwoWayMultiSprite("Gastly"));
    Gastly_4->setX(4600);
    Drawable* Gastly_5(new TwoWayMultiSprite("Gastly"));
    Gastly_5->setX(4700);
    Drawable* Gastly_6(new TwoWayMultiSprite("Gastly"));
    Gastly_6->setX(5000);
    Drawable* Gastly_7(new TwoWayMultiSprite("Gastly"));
    Gastly_7->setX(5100);
    Drawable* Gastly_8(new TwoWayMultiSprite("Gastly"));
    Gastly_8->setX(5200);
    Drawable* Gastly_9(new TwoWayMultiSprite("Gastly"));
    Gastly_9->setX(5300);
    Drawable* Gastly_10(new TwoWayMultiSprite("Gastly"));
    Gastly_10->setX(6600);
    Drawable* Gastly_11(new TwoWayMultiSprite("Gastly"));
    Gastly_11->setX(6700);
    Drawable* Gastly_12(new TwoWayMultiSprite("Gastly"));
    Gastly_12->setX(6800);
    Drawable* Gastly_13(new TwoWayMultiSprite("Gastly"));
    Gastly_13->setX(7850);
    Drawable* Gastly_14(new TwoWayMultiSprite("Gastly"));
    Gastly_14->setX(7900);
    Drawable* Gastly_15(new TwoWayMultiSprite("Gastly"));
    Gastly_15->setX(7950);

    //Set Gengars
    Drawable* Gengar(new TwoWayMultiSprite("Gengar"));
    Gengar->setX(1500);
    Drawable* Gengar_1(new TwoWayMultiSprite("Gengar"));
    Gengar_1->setX(2000);
    Drawable* Gengar_2(new TwoWayMultiSprite("Gengar"));
    Gengar_2->setX(2100);
    Drawable* Gengar_3(new TwoWayMultiSprite("Gengar"));
    Gengar_3->setX(2200);
    Drawable* Gengar_4(new TwoWayMultiSprite("Gengar"));
    Gengar_4->setX(2500);
    Drawable* Gengar_5(new TwoWayMultiSprite("Gengar"));
    Gengar_5->setX(2600);
    Drawable* Gengar_6(new TwoWayMultiSprite("Gengar"));
    Gengar_6->setX(2700);
    Drawable* Gengar_7(new TwoWayMultiSprite("Gengar"));
    Gengar_7->setX(4600);
    Drawable* Gengar_8(new TwoWayMultiSprite("Gengar"));
    Gengar_8->setX(4650);
    Drawable* Gengar_9(new TwoWayMultiSprite("Gengar"));
    Gengar_9->setX(4700);
    Drawable* Gengar_10(new TwoWayMultiSprite("Gengar"));
    Gengar_10->setX(6650);
    Drawable* Gengar_11(new TwoWayMultiSprite("Gengar"));
    Gengar_11->setX(6750);
    Drawable* Gengar_12(new TwoWayMultiSprite("Gengar"));
    Gengar_12->setX(6850);
    Drawable* Gengar_13(new TwoWayMultiSprite("Gengar"));
    Gengar_13->setX(7500);
    Drawable* Gengar_14(new TwoWayMultiSprite("Gengar"));
    Gengar_14->setX(7600);
    Drawable* Gengar_15(new TwoWayMultiSprite("Gengar"));
    Gengar_15->setX(7700);

    Drawable* Trap(new Sprite("Trap"));
    Trap->setX(600);
    Drawable* Trap_1(new Sprite("Trap"));
    Trap_1->setX(2800);
    Drawable* Trap_2(new Sprite("Trap"));
    Trap_2->setX(4100);
    Drawable* Trap_3(new Sprite("Trap"));
    Trap_3->setX(5800);
    Drawable* Trap_4(new Sprite("Trap"));
    Trap_4->setX(6050);
    Drawable* Trap_5(new Sprite("Trap"));
    Trap_5->setX(6300);
    Drawable* Trap_6(new Sprite("Trap"));
    Trap_6->setX(6550);
    Drawable* Trap_7(new Sprite("Trap"));
    Trap_7->setX(7100);
    Drawable* Trap_8(new Sprite("Trap"));
    Trap_8->setX(7300);

    sprites.push_back(Haunter);
    sprites.push_back(Haunter_1);
    sprites.push_back(Haunter_2);
    sprites.push_back(Haunter_3);
    sprites.push_back(Haunter_4);
    sprites.push_back(Haunter_5);
    sprites.push_back(Haunter_6);
    sprites.push_back(Haunter_7);
    sprites.push_back(Haunter_8);
    sprites.push_back(Haunter_9);
    sprites.push_back(Haunter_10);
    sprites.push_back(Haunter_11);
    sprites.push_back(Haunter_12);
    sprites.push_back(Haunter_13);
    sprites.push_back(Haunter_14);

    sprites.push_back(Gastly);
    sprites.push_back(Gastly_1);
    sprites.push_back(Gastly_2);
    sprites.push_back(Gastly_3);
    sprites.push_back(Gastly_4);
    sprites.push_back(Gastly_5);
    sprites.push_back(Gastly_6);
    sprites.push_back(Gastly_7);
    sprites.push_back(Gastly_8);
    sprites.push_back(Gastly_9);
    sprites.push_back(Gastly_10);
    sprites.push_back(Gastly_11);
    sprites.push_back(Gastly_12);
    sprites.push_back(Gastly_13);
    sprites.push_back(Gastly_14);
    sprites.push_back(Gastly_15);

    sprites.push_back(Gengar);
    sprites.push_back(Gengar_1);
    sprites.push_back(Gengar_2);
    sprites.push_back(Gengar_3);
    sprites.push_back(Gengar_4);
    sprites.push_back(Gengar_5);
    sprites.push_back(Gengar_6);
    sprites.push_back(Gengar_7);
    sprites.push_back(Gengar_8);
    sprites.push_back(Gengar_9);
    sprites.push_back(Gengar_10);
    sprites.push_back(Gengar_11);
    sprites.push_back(Gengar_12);
    sprites.push_back(Gengar_13);
    sprites.push_back(Gengar_14);
    sprites.push_back(Gengar_15);

    sprites.push_back(Trap);
    sprites.push_back(Trap_1);
    sprites.push_back(Trap_2);
    sprites.push_back(Trap_3);
    sprites.push_back(Trap_4);
    sprites.push_back(Trap_5);
    sprites.push_back(Trap_6);
    sprites.push_back(Trap_7);
    sprites.push_back(Trap_8);
}

void Engine::draw() const {
    night.draw();
    mountains.draw();

    for(auto i = remote_sprites.begin(); i < remote_sprites.end(); i++)
    {
        (*i)->draw();
    }

    castle.draw();
    road.draw();

    for(auto i = sprites.begin(); i < sprites.end(); i++)
    {
        (*i)->draw();
    }

    goal.draw();
    if(player->getInvincibleTime()%2 != 1) player -> draw();

    std::stringstream ss;
    int fps = clock.getFps();
    ss << fps;
    string sFps = ss.str();
    IOmod::getInstance().writeText("Name: Yu Sun", 30, 400);
    IOmod::getInstance().writeText("Lives: " + std::to_string(player -> getLives()), 30, 300);

    hud->ShowHUD(clock.getSeconds());
    if(player->getLives() <= 0)
    {
        std::string str("Ash died.");
        overhud->setContent(str);
        overhud->ShowLose();
    }
    else if(player->getWin())
    {
        std::string str("Ash survived.");
        overhud->setContent(str);
        overhud->ShowWin();
    }
    poolhud.ShowHUD();
    viewport.draw();
    SDL_RenderPresent(renderer);
}

void Engine::checkForCollisions() {
    if(!player->getWin()) {
        player_collision = false;
        for (std::vector<Drawable *>::iterator d = sprites.begin(); d != sprites.end(); d++) {
            enemy_collision = false;
            TwoWayMultiSprite *twoWay = dynamic_cast<TwoWayMultiSprite *>(*d);
            if (twoWay) {
                if (!(twoWay)->explosion) {
                    if (!player->getGodMode() && !player->explosion) {
                        if (player->getInvincibleTime() <= 0) {
                            if (strategies[currentStrategy]->execute(*player, **d)) {
                                player_collision = true;
                                SmartTwoWaySprite *smart = dynamic_cast<SmartTwoWaySprite *>(*d);
                                if (smart) enemy_collision = true;
                            }
                        }
                    }
                    for (Bullet &b : player->bullets) {
                        if (strategies[currentStrategy]->execute(**d, b)) {
                            b.collide();
                            enemy_collision = true;
                        }
                    }
                }
                if (enemy_collision) { sound[2]; (twoWay)->explode(); }
            } else {
                if (!player->getGodMode() && !player->explosion) {
                    if (player->getInvincibleTime() <= 0) {
                        if (strategies[currentStrategy]->execute(*player, **d)) {
                            player_collision = true;
                        }
                    }
                }
            }
        }
        if (player_collision && player->getLives() > 0) {
            sound[1];
            player->collided();
            player->explode();
        }
        if(strategies[currentStrategy]->execute(*player, goal)) player->setWin(true);
    }
}

void Engine::finalWave()
{
    Drawable* Haunter_13(new SmartTwoWaySprite("Haunter"));
    Haunter_13->setX(6800);
    Haunter_13->setY(20);
    Drawable* Haunter_14(new SmartTwoWaySprite("Haunter"));
    Haunter_14->setX(6800);
    Haunter_14->setY(500);

    sprites.push_back(Haunter_13);
    sprites.push_back(Haunter_14);

    final = true;
}

void Engine::update(Uint32 ticks) {
    checkForCollisions();

    player -> update(ticks);

    if(player->getX() > 7150 && !final)
    {
        finalWave();
    }

    for(auto i = sprites.begin(); i < sprites.end();)
    {
        TwoWayMultiSprite* twoWay = dynamic_cast<TwoWayMultiSprite *>(*i);
        if(twoWay) {
            if (twoWay->getEndExplosion()) {
                delete *i;
                i = sprites.erase(i);
            } else {
                if ((*i)->getX() - player->getX() <= 800) {
                    SmartTwoWaySprite *smart = dynamic_cast<SmartTwoWaySprite *>(*i);
                    if (smart) {
                        smart->setPlayerPos(player->getPosition());
                        smart->update(ticks);
                    } else {
                        (*i)->update(ticks);
                    }
                }
                i++;
            }
        }
        else
        {
            Sprite* sprite = dynamic_cast<Sprite *>(*i);
            if(sprite) sprite ->update(ticks);
            i++;
        }
    }

    for(auto i = remote_sprites.begin(); i < remote_sprites.end(); i++)
    {
        (*i)->update(ticks);
    }

    goal.update(ticks);
    night.update();
    mountains.update();
    castle.update();
    road.update();
    viewport.update(); // always update viewport last
}

void Engine::switchSprite(){
    ++currentSprite;
    currentSprite = currentSprite % 2;
    if ( currentSprite ) {
        Viewport::getInstance().setObjectToTrack(sprites[0]);
    }
    else {
        Viewport::getInstance().setObjectToTrack(sprites[1]);
    }
}

bool Engine::play() {
    SDL_Event event;
    const Uint8* keystate;
    bool done = false;
    Uint32 ticks = clock.getElapsedTicks();
    FrameGenerator frameGen;

    while ( !done ) {
        // The next loop polls for events, guarding against key bounce:
        while ( SDL_PollEvent(&event) ) {
            keystate = SDL_GetKeyboardState(NULL);
            if (event.type ==  SDL_QUIT) { done = true; break; }
            if(event.type == SDL_KEYDOWN) {
                if (keystate[SDL_SCANCODE_ESCAPE] || keystate[SDL_SCANCODE_Q]) {
                    done = true;
                    break;
                }
                if ( keystate[SDL_SCANCODE_P] ) {
                    if ( clock.isPaused() ) clock.unpause();
                    else clock.pause();
                }
                if ( keystate[SDL_SCANCODE_R] ) {
                    clock.unpause();
                    return true;
                }
                if (keystate[SDL_SCANCODE_F4] && !makeVideo) {
                    std::cout << "Initiating frame capture" << std::endl;
                    makeVideo = true;
                }
                else if (keystate[SDL_SCANCODE_F4] && makeVideo) {
                    std::cout << "Terminating frame capture" << std::endl;
                    makeVideo = false;
                }
            }
        }

        // In this section of the event loop we allow key bounce:
        ticks = clock.getElapsedTicks();
        if ( ticks > 0 ) {
            clock.incrFrame();
            if (keystate[SDL_SCANCODE_A]) {
                player->left();
            }
            if (keystate[SDL_SCANCODE_D]) {
                player->right();
            }
            if (keystate[SDL_SCANCODE_J]) {
                player->shoot(sound);
            }
            if ( keystate[SDL_SCANCODE_SPACE] ) {
                player -> jump();
            }
            if ( keystate[SDL_SCANCODE_G] ) {
                player -> toggleGodMode();
            }
            if (keystate[SDL_SCANCODE_F1]) {
                hud->ResetLife(clock.getSeconds());
            }
            draw();
            update(ticks);
            if ( makeVideo ) {
                frameGen.makeFrame();
            }
        }
    }

    return false;
}
