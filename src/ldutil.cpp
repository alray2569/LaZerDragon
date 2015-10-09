// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Utilities and Constants

#include "ldutil.h"
#include <algorithm>

// Convert grid position to world position
df::Position gridToPos( df::Position pos ) {
  // Bound input values to grid
  int temp_x = std::max(0, std::min(GRID_WIDTH, pos.getX()));
  int temp_y = std::max(0, std::min(GRID_HEIGHT, pos.getY()));
  temp_x = MARGIN_LEFT + temp_x * GRID_SIZE + GRID_SIZE / 2;
  temp_y = MARGIN_TOP + temp_y * GRID_SIZE + GRID_SIZE / 2;
  return df::Position(temp_x, temp_y);
}

// Convert world position to grid position
// Bound positions outside the grid to the nearest
//  grid position
df::Position posToGrid( df::Position pos ) {
  int temp_x = (pos.getX() - MARGIN_LEFT) / GRID_SIZE;
  int temp_y = (pos.getY() - MARGIN_TOP) / GRID_SIZE;
  // Bound output values to grid
  temp_x = std::max(0, std::min(GRID_WIDTH, temp_x));
  temp_y = std::max(0, std::min(GRID_HEIGHT, temp_y));
  return df::Position(temp_x, temp_y);
}

df::Position snapPosToGrid( df::Position pos ) {
  return gridToPos(posToGrid(pos));
}
