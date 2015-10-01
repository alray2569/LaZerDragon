// LaZerDragon
// Andrew Ray
// IMGD 3000

// Laser direction

#ifndef LASERDIRECTION_H
#define LASERDIRECTION_H


namespace laser {

enum Direction {
  RIGHT = 0,
  DOWN,
  LEFT,
  UP
};

// Rotates direction [dir] clockwise [turns] * 90 degrees
Direction rotateDirection(Direction dir, int turns);

} // end namespace laser

#endif
