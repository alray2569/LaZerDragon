// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Utilities and Constants

#include "ldutil.h"
#include <algorithm>
#include "Component.h"
#include "Emitter.h"
#include "Block.h"
#include "Receiver.h"

// Convert grid position to world position
df::Position gridToPos( df::Position pos ) {
  // Bound input values to grid
  int temp_x = std::max(0, std::min(GRID_WIDTH - 1, pos.getX()));
  int temp_y = std::max(0, std::min(GRID_HEIGHT - 1, pos.getY()));
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
  temp_x = std::max(0, std::min(GRID_WIDTH - 1, temp_x));
  temp_y = std::max(0, std::min(GRID_HEIGHT - 1, temp_y));
  return df::Position(temp_x, temp_y);
}

df::Position snapPosToGrid( df::Position pos ) {
  return gridToPos(posToGrid(pos));
}

Component *getComponent( char c ) {
	switch ( c ) {
	case 'A':
		return new Emitter( laser::RED, Direction::UP );
	case 'B':
		return new Block( );
	case 'C':
		return new Emitter( laser::RED, Direction::DOWN );
	case 'D':
		return new Emitter( laser::RED, Direction::LEFT );
	case 'E':
		return new Emitter( laser::RED, Direction::RIGHT );
	case 'F':
		return new Emitter( laser::BLUE, Direction::UP );
	case 'G':
		return new Emitter( laser::BLUE, Direction::DOWN );
	case 'H':
		return new Emitter( laser::BLUE, Direction::LEFT );
	case 'I':
		return new Emitter( laser::BLUE, Direction::RIGHT );
	case 'J':
		return new Emitter( laser::GREEN, Direction::UP );
	case 'K':
		return new Emitter( laser::GREEN, Direction::DOWN );
	case 'L':
		return new Emitter( laser::GREEN, Direction::LEFT );
	case 'M':
		return new Emitter( laser::GREEN, Direction::RIGHT );
	case 'N':
		return new Emitter( laser::MAGENTA, Direction::UP );
	case 'O':
		return new Emitter( laser::MAGENTA, Direction::DOWN );
	case 'P':
		return new Emitter( laser::MAGENTA, Direction::LEFT );
	case 'Q':
		return new Emitter( laser::MAGENTA, Direction::RIGHT );
	case 'R':
		return new Emitter( laser::CYAN, Direction::UP );
	case 'S':
		return new Emitter( laser::CYAN, Direction::DOWN );
	case 'T':
		return new Emitter( laser::CYAN, Direction::LEFT );
	case 'U':
		return new Emitter( laser::CYAN, Direction::RIGHT );
	case 'V':
		return new Emitter( laser::YELLOW, Direction::UP );
	case 'W':
		return new Emitter( laser::YELLOW, Direction::DOWN );
	case 'X':
		return new Emitter( laser::YELLOW, Direction::LEFT );
	case 'Y':
		return new Emitter( laser::YELLOW, Direction::RIGHT );
	case 'Z':
		return new Emitter( laser::WHITE, Direction::UP );
	case 'a':
		return new Receiver( laser::RED );
	case 'z':
		return new Receiver( laser::WHITE );
	case 'f':
		return new Receiver( laser::BLUE );
	case 'j':
		return new Receiver( laser::GREEN );
	case 'n':
		return new Receiver( laser::MAGENTA );
	case 'r':
		return new Receiver( laser::CYAN );
	case 'v':
		return new Receiver( laser::YELLOW );
	case 'w':
		return new Emitter( laser::WHITE, Direction::DOWN );
	case 'x':
		return new Emitter( laser::WHITE, Direction::LEFT );
	case 'y':
		return new Emitter( laser::WHITE, Direction::RIGHT );
	case ' ':
		return NULL;
	default:
		DF_LOG( "Warning from ldutil::getComponent(): %c is not a valid character!", c );
		return NULL;
	}
}