// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

#include <EventStep.h>
#include <GraphicsManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>

#include "Lens.h"
#include "ldutil.h"


Lens::Lens( Direction dir /* = RIGHT */ ) {
  DF_LOG("BEGIN MAIN Color: %d", this->color.getColor());
  setDirection( dir );
  this->color = laser::BLACK;

  this->setType( LENS );
  df::Sprite *temp_sprite =
    df::ResourceManager::getInstance().getSprite( LENS );
  if (!temp_sprite) {
    DF_LOG("Emitter::Emitter(): Warning! Sprite '%s' not found", LENS);
  } else {
    this->setSprite(temp_sprite, false);
  }
  registerInterest(df::STEP_EVENT);
  DF_LOG("END MAIN Color: %d", this->color.getColor());
}

void Lens::laserHit( Laser* laser ) {
  DF_LOG("BEGIN HIT Color: %d", this->color.getColor());
  this->color += laser->getColor();
  df::WorldManager::getInstance().markForDelete(laser);
  DF_LOG("END HIT Color: %d", this->color.getColor());
}

int Lens::eventHandler( const df::Event* evt ) {
  // Reset the output color on step
  if (evt->getType() == df::STEP_EVENT) {
    DF_LOG("BEGIN EVENT Color: %d", this->color.getColor());
    if (this->color != laser::BLACK) {
      Laser* laser = new Laser(this->color, getDirection());
      laser->setPosition(getPosition());
      this->color = laser::BLACK;
    }
    DF_LOG("END EVENT Color: %d", this->color.getColor());
    return 1;
  }
  return Component::eventHandler(evt);
}

void Lens::draw() {
  DF_LOG("BEGIN DRAW Color: %d", this->color.getColor());
  Object::draw();
  df::GraphicsManager::getInstance().drawCh(getPosition(), 'O',
      this->color.getColor());
  DF_LOG("END DRAW Color: %d", this->color.getColor());
}