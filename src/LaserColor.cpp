// LaZerDragon
// Andrew Ray
// IMGD 3000

// Color for lasers. Allows color combination

// Game includes
#include "LaserColor.h"


namespace laser {

Color::Color() {
  setColor(df::WHITE);
}

Color::Color(df::Color color) {
  setColor(color);
}

void Color::setColor(df::Color color) {
  this->color = color;
}

df::Color Color::getColor() {
  return color;
}

};
