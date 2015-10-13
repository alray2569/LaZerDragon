// LaZerDragon
// char *args[]
// Andrew Ray, Gareth Solbeck
// IMGD 3000

// Main game file

#include <sstream>

// Engine includes
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes
#include "Block.h"
#include "ComponentCount.h"
#include "Emitter.h"
#include "Lens.h"
#include "Level.h"
#include "LevelManager.h"
#include "Prism.h"
#include "Receiver.h"
#include "ldutil.h"
#include "TitleScreen.h"

#define DEBUG true


// Function prototypes
int loadResources( void );

int main() {
  df::GameManager &game_manager = df::GameManager::getInstance();
  df::LogManager &log_manager = df::LogManager::getInstance();
  LevelManager &level_manager = LevelManager::getInstance();

  if (game_manager.startUp()) {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 1; // Error
  }
  level_manager.startUp();

  log_manager.setFlush(DEBUG);
  df::GraphicsManager::getInstance().getWindow()->setMouseCursorVisible(true);

  if (loadResources()) {
    level_manager.shutDown();
    game_manager.shutDown();
    return 1;
  }

  if (!DEBUG) {
    df::splash();
  }

  new TitleScreen;

  df::Music* bkgd_music = df::ResourceManager::getInstance().getMusic("music");
  bkgd_music->play();
  game_manager.run();
  bkgd_music->stop();

  level_manager.shutDown();
  game_manager.shutDown();
  return 0;
}

int loadResources() {
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  LevelManager &level_manager = LevelManager::getInstance();
  resource_manager.loadSprite( "sprites/title.spr", "titlescreen" );
  resource_manager.loadSprite("sprites/block.spr", "block");
  resource_manager.loadSprite("sprites/mirror.spr", "mirror");
  resource_manager.loadSprite( "sprites/emitter.spr", "emitter" );
  resource_manager.loadSprite("sprites/receiver.spr", "receiver");
  resource_manager.loadSprite("sprites/lens.spr", "lens");
  resource_manager.loadSprite("sprites/prism.spr", "prism");

  resource_manager.loadSound( "sounds/blue.ogg", "blue");
  resource_manager.loadSound( "sounds/click.ogg", "click");
  resource_manager.loadSound( "sounds/cyan.ogg", "cyan");
  resource_manager.loadMusic( "sounds/disaffected_piano.ogg", "music");
  resource_manager.loadSound( "sounds/green.ogg", "green");
  resource_manager.loadSound( "sounds/magenta.ogg", "magenta");
  resource_manager.loadSound( "sounds/red.ogg", "red");
  resource_manager.loadSound( "sounds/white.ogg", "white");
  resource_manager.loadSound( "sounds/woosh.ogg", "woosh");
  resource_manager.loadSound( "sounds/yellow.ogg", "yellow");
  resource_manager.loadSound( "sounds/tada.ogg", "tada" );

  DF_LOG("loadResources(): The game will try to load levels until a level "
      "fails to load");
  bool success = true;
  for (int i = 0; success; i++) {
    std::ostringstream oss;
    oss << "levels/level" << i << ".lvl";
    success = !level_manager.loadLevel(oss.str() , i);
  }

  return 0;
}
