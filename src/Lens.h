// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

#ifndef LENS_H
#define LENS_H

#include "LaserColor.h"
#include "Component.h"

#define LENS "lens"


class Lens : public Component {
 private:
  laser::Color color;
  void laserHit( Laser* );

public:
  Lens( Direction dir=RIGHT );

  int eventHandler( const df::Event* );
  void draw( void );
};

#endif
