// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Puzzle component (e.g: emitter, block, mirror)

// Engine includes
#include "Component.h"
#include "EventCollision.h"


Component::Component() {
  setSpriteSlowdown(0);

  setDirection(RIGHT);

  registerInterest(df::COLLISION_EVENT);
}

// Handle collision events and pass lasers to laserHit()
int Component::eventHandler(const df::Event *evt) {
  if (evt->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *coll =
        static_cast<const df::EventCollision*>( evt );

    if (coll->getObject1()->getType() == "Laser") {
      laserHit( static_cast< const Laser* >( coll->getObject1() ) );
    } else if (coll->getObject2()->getType() == "Laser") {
      laserHit( static_cast< const Laser* >( coll->getObject2() ) );
    }
    return 1;
  }

  return 0;
}

// To be overriden by subclasses
void Component::laserHit( const Laser* ) {}

void Component::setDirection( Direction ) {
  this->direction = direction;
  switch(direction) {
    case RIGHT:
      setSpriteIndex(0);
      break;
    case DOWN:
      setSpriteIndex(1);
      break;
    case LEFT:
      setSpriteIndex(2);
      break;
    case UP:
      setSpriteIndex(3);
      break;
  }
}

Direction Component::getDirection() {
  return direction;
}
