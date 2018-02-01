#include <vector>
#include <SDL.h>
#include "ioMod.h"
#include "renderContext.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include "twowayMultisprite.h"
#include "player.h"
#include "HUD.h"
#include "collisionStrategy.h"
#include "multisprite.h"
#include <sstream>

class Engine {
public:
  Engine ();
  ~Engine ();
  Engine (const Engine &) = delete;
  Engine& operator=(const Engine&) = delete;

  void InitMonsters();
  bool play();
  void switchSprite();

private:
  const RenderContext* rc;
  const IOmod& io;
  Clock& clock;

  SDL_Renderer * const renderer;
  World night;
  World mountains;
  World castle;
  World road;
  Player* player;
  MultiSprite goal;
  //World ground;
  Viewport& viewport;

  std::vector<Drawable *> sprites;
  std::vector<Drawable *> remote_sprites;

  std::vector<CollisionStrategy*> strategies;
  int currentStrategy;
  bool player_collision;
  bool enemy_collision;

  HUD* hud;
  PoolHUD poolhud;
  GameoverHUD* overhud;

  SDLSound sound;

  int currentSprite;

  bool makeVideo;
  bool final;

  void finalWave();

  void draw() const;
  void checkForCollisions();
  void update(Uint32);

  void printScales() const;
};
