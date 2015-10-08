// LaZerDragon
// char *args[]
// Andrew Ray, Gareth Solbeck
// IMGD 3000

// Main game file

// Engine includes
#include "GameManager.h"
#include "GraphicsManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes
#include "Block.h"
#include "ComponentCount.h"
#include "Emitter.h"
#include "Level.h"
#include "Receiver.h"
#include "ldutil.h"

#define DEBUG true


// Function prototypes
void loadResources( void );

int main() {
  df::GameManager &game_manager = df::GameManager::getInstance();
  df::LogManager &log_manager = df::LogManager::getInstance();

  if (game_manager.startUp()) {
    log_manager.writeLog("Error starting game manager!");
    game_manager.shutDown();
    return 1; // Error
  }
  log_manager.setFlush(DEBUG);
  df::GraphicsManager::getInstance().getWindow()->setMouseCursorVisible(true);

  loadResources();

  df::splash();

  Level* level = new Level(1);
  ComponentCount* mirror_count = new ComponentCount("mirror", 6);
  mirror_count->setLocation(df::BOTTOM_CENTER);

  std::string lvl_str = "BBBBBBBBBBBBBBBBBBBBBBBBBB"
                        "B     B                  B"
                        "E     B           B      B"
                        "B     B    BBBBRBBB      B"
                        "B                 B      B"
                        "e                 B      B"
                        "BBBBBBBBBBBBBBBBBBBBBrBBBB";
  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      char c = lvl_str[x + y * GRID_WIDTH];
      Component* component;
      switch (c) {
        case 'B':
          component = new Block();
          break;
        case 'E':
          component = new Emitter( laser::Color(df::RED), RIGHT );
          break;
        case 'e':
          component = new Emitter( laser::Color(df::GREEN), RIGHT );
          break;
        case 'R':
          component = new Receiver( laser::Color(df::RED) );
          break;
        case 'r':
          component = new Receiver( laser::Color(df::GREEN) );
          break;
        default:
          continue; //skip to the next iteration
      }
      component->setGridPosition( df::Position(x, y));
      level->addComponent(component);
    }
  }

  game_manager.run();

  game_manager.shutDown();
  return 0;
}

void loadResources() {
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  resource_manager.loadSprite("sprites/block.spr", "block");
  resource_manager.loadSprite("sprites/mirror.spr", "mirror");
  resource_manager.loadSprite( "sprites/emitter.spr", "emitter" );
  resource_manager.loadSprite("sprites/receiver.spr", "receiver");
}
