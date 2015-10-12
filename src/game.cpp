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


  ComponentCount* mirror_count = new ComponentCount("mirror", 0);
  ComponentCount* lens_count = new ComponentCount("lens", 0);
  ComponentCount* prism_count = new ComponentCount("prism", 0);
  mirror_count->setLocation(df::BOTTOM_LEFT);
  lens_count->setLocation(df::BOTTOM_CENTER);
  prism_count->setLocation(df::BOTTOM_RIGHT);
  mirror_count->setSelected();

  level_manager.startLevel(0);

  game_manager.run();

  level_manager.shutDown();
  game_manager.shutDown();
  return 0;
}

int loadResources() {
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  LevelManager &level_manager = LevelManager::getInstance();

  resource_manager.loadSprite("sprites/block.spr", "block");
  resource_manager.loadSprite("sprites/mirror.spr", "mirror");
  resource_manager.loadSprite( "sprites/emitter.spr", "emitter" );
  resource_manager.loadSprite("sprites/receiver.spr", "receiver");
  resource_manager.loadSprite("sprites/lens.spr", "lens");
  resource_manager.loadSprite("sprites/prism.spr", "prism");
  for (int i = 0; i < NUM_LEVELS; i++) {
    std::ostringstream oss;
    oss << "levels/level" << i << ".lvl";
    if (level_manager.loadLevel( oss.str() , i)) {
      return -1;
    }
  }

  return 0;
}
