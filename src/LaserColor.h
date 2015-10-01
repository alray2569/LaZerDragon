// LaZerDragon
// Andrew Ray
// IMGD 3000

// Color for lasers. Allows color combination

#ifndef LASERCOLOR_H
#define LASERCOLOR_H

// Engine includes
#include "Color.h"


namespace laser {

class Color {
 private:
  df::Color color;

 public:
   Color();
   Color( df::Color );

   void setColor( df::Color );
   df::Color getColor();
};

}

#endif
