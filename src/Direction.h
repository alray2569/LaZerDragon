// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Laser direction

#ifndef DIRECTION_H
#define DIRECTION_H


enum Direction {
  RIGHT = 0,
  DOWN,
  LEFT,
  UP
};

// Rotates direction [dir] clockwise [turns] * 90 degrees
Direction rotateDirection(Direction dir, unsigned int turns);

#endif
