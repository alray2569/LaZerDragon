// LaZerDragon
// Gareth Solbeck
// IMGD 3000

// Laser game object

// Engine includes
#include "Color.h"
#include "EventOut.h"
#include "GraphicsManager.h"
#include "WorldManager.h"

// Game includes
#include "Laser.h"


Laser::Laser() {
  setType("Laser");
  setSolidness(df::SOFT);

  setColor( laser::Color(df::WHITE) );
  setDirection(laser::RIGHT);

  registerInterest( df::OUT_EVENT );
}

Laser::Laser(laser::Color color, laser::Direction direction) {
  setType("Laser");
  setSolidness(df::SOFT);

  setDirection(direction);
  setColor(color);

  registerInterest( df::OUT_EVENT );
}

void Laser::draw() {
  df::GraphicsManager::getInstance().drawCh(getPosition(), draw_char,
      color.getColor());
}

int Laser::eventHandler(const df::Event *evt) {
  if (evt->getType() == df::OUT_EVENT) {
    df::WorldManager::getInstance().markForDelete(this);
    return 1;
  }
  return 0;
}

void Laser::setColor(laser::Color color) {
  if (color.getColor() == df::BLACK) {
    df::WorldManager::getInstance().markForDelete(this);
  } else {
    this->color = color;
  }
}

void Laser::setDirection(laser::Direction direction) {
  this->direction = direction;
  switch (direction) {
    case laser::RIGHT:
      draw_char = HORIZ_LASER_CHAR;
      setXVelocity(1);
      setYVelocity(0);
      break;
    case laser::DOWN:
      draw_char = VERT_LASER_CHAR;
      setXVelocity(0);
      setYVelocity(1);
      break;
    case laser::LEFT:
      draw_char = HORIZ_LASER_CHAR;
      setXVelocity(-1);
      setYVelocity(0);
      break;
    case laser::UP:
      draw_char = VERT_LASER_CHAR;
      setXVelocity(0);
      setYVelocity(-1);
      break;
  }
}

laser::Color Laser::getColor() const {
  return color;
}
laser::Direction Laser::getDirection() const {
  return direction;
}
