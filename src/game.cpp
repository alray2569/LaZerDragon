// LaZerDragon
// char *args[]
// Andrew Ray, Gareth Solbeck
// IMGD 3000

// Main game file

// Engine includes
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes
#include "Block.h"
#include "Laser.h"
#include "Mirror.h"

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

  loadResources();

  df::splash();

  Laser *laser1 = new Laser( laser::Color(df::RED), RIGHT );
  laser1->setPosition( df::Position(1, 10) );

  Mirror *mirror1 = new Mirror();
  mirror1->setPosition( df::Position(60, 10) );
  mirror1->setDirection( UP );

  Mirror *mirror2 = new Mirror();
  mirror2->setPosition( df::Position(60, 20) );

  Block *block1 = new Block();
  block1->setPosition( df::Position(30, 20) );

  game_manager.run();

  game_manager.shutDown();
  return 0;
}

void loadResources() {
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  resource_manager.loadSprite("sprites/block.spr", "block");
  resource_manager.loadSprite("sprites/mirror.spr", "mirror");
  resource_manager.loadSprite( "sprites/emitter.spr", "emitter" );
}
