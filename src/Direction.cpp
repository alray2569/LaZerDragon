// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Laser direction

// Game includes
#include "Direction.h"


// Rotates direction [dir] clockwise [turns] * 90 degrees
Direction rotateDirection(Direction dir, unsigned int turns) {
  return static_cast<Direction>((dir + turns) % 4);
}
