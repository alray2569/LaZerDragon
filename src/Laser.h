// LaZerDragon
// Gareth Solbeck
// IMGD 3000

// Laser game object

#ifndef LASER_H
#define LASER_H

// Engine includes
#include "Object.h"

// Game includes
#include "LaserColor.h"
#include "LaserDirection.h"


#define VERT_LASER_CHAR '|'
#define HORIZ_LASER_CHAR '-'

class Laser : public df::Object {
 private:
  char draw_char;
  laser::Color color;
  laser::Direction direction;

 public:
  Laser( void );
  Laser( laser::Color, laser::Direction );

  void draw( void );
  virtual int eventHandler(const df::Event *evt);

  void setColor( laser::Color );
  void setDirection( laser::Direction );
  laser::Color getColor( void ) const;
  laser::Direction getDirection( void ) const;
};

#endif
