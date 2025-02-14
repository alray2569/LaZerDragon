// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Puzzle component (e.g: emitter, block, mirror)

// Engine includes
#include <EventCollision.h>

// Game includes
#include "Component.h"
#include "ldutil.h"

Component::Component() {
  setAltitude(3);
  setSpriteSlowdown(0);
  setTransparency(' ');

  setDirection(RIGHT);
}

// Handle collision events and pass lasers to laserHit()
int Component::eventHandler(const df::Event *evt) {
  if (evt->getType() == df::COLLISION_EVENT) {
    const df::EventCollision *coll =
        static_cast<const df::EventCollision*>( evt );

    if (coll->getObject1()->getType() == "Laser") {
      laserHit( static_cast< Laser* >( coll->getObject1() ) );
    } else if (coll->getObject2()->getType() == "Laser") {
      laserHit( static_cast< Laser* >( coll->getObject2() ) );
    }

    return 1;
  }

  return 0;
}

// To be overriden by subclasses
void Component::laserHit( Laser* ) {}

void Component::setDirection( Direction direction ) {
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

Direction Component::getDirection() const {
  return direction;
}

void Component::rotate( bool ccw ) {
  if (ccw) {
    setDirection(rotateDirection(getDirection(), 3));
  } else {
    setDirection(rotateDirection(getDirection(), 1));
  }
}

df::Position Component::getGridPosition() const {
  return posToGrid(getPosition());
}

void Component::setGridPosition( df::Position pos ) {
  setPosition(gridToPos(pos));
}
