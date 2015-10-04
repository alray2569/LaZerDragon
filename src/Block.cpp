// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Block component (destroys lasers)

// Engine includes
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

// Game includes
#include "Block.h"


Block::Block() {
  setType(BLOCK);
  df::ResourceManager &resource_manager = df::ResourceManager::getInstance();
  df::Sprite *temp_sprite = resource_manager.getSprite("block");
  if (!temp_sprite) {
    df::LogManager::getInstance().writeLog(
        "Block::Block(): Warning! Sprite '%s' not found", "block");
  } else {
    setSprite(temp_sprite);
  }
}

void Block::laserHit(Laser* laser) {
  df::WorldManager::getInstance().markForDelete(laser);
}
