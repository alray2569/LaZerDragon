// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Puzzle component (e.g: emitter, block, mirror)

#ifndef COMPONENT_H
#define COMPONENT_H

// Game includes
#include "Direction.h"
#include "Laser.h"


class Component : public df::Object {
private:
  Direction direction;

  virtual void laserHit( Laser* );

public:
  Component();

  virtual int eventHandler( const df::Event* );

  Direction getDirection() const;
  void setDirection( Direction );
  void rotate( bool ccw=false );
};

#endif
