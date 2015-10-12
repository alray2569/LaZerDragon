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
}

void Lens::laserHit( Laser* laser ) {
  this->color += laser->getColor();
  df::WorldManager::getInstance().markForDelete(laser);
}

int Lens::eventHandler( const df::Event* evt ) {
  // Reset the output color on step
  if (evt->getType() == df::STEP_EVENT) {
    if (this->color != laser::BLACK) {
      Laser* laser = new Laser(this->color, getDirection());
      laser->setPosition(getPosition());
      this->color = laser::BLACK;
    }
    return 1;
  }
  return Component::eventHandler(evt);
}

void Lens::draw() {
  Object::draw();
  df::GraphicsManager::getInstance().drawCh(getPosition(), 'O',
      this->color.getColor());
}