// LaZerDragon
// char *args[]
// Andrew Ray, Gareth Solbeck
// IMGD 3000

// Utilities and Constants

#ifndef LZCONSTANTS
#define LZCONSTANTS
#include <LogManager.h>
#include <Position.h>

#define GRID_SIZE 3
#define GRID_HEIGHT 7
#define GRID_WIDTH 26
#define MARGIN_LEFT 1
#define MARGIN_RIGHT 1
#define MARGIN_TOP 0
#define MARGIN_BOTTOM 3


#define DF_LOG df::LogManager::getInstance( ).writeLog

// Convert grid position to world position
df::Position gridToPos( df::Position );
// Convert world position to grid position
df::Position posToGrid( df::Position );

// Return the position at the center of the grid square
df::Position snapPosToGrid( df::Position );

#endif
