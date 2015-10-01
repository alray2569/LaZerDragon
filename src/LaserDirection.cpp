// LaZerDragon
// Andrew Ray
// IMGD 3000

// Laser direction

// Game includes
#include "LaserDirection.h"


namespace laser {

// Rotates direction [dir] clockwise [turns] * 90 degrees
Direction rotateDirection(Direction dir, int turns) {
  return static_cast<Direction>( (dir + turns) % 4);
}

} // end namespace laser
