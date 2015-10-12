// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Level manager

#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <Manager.h>

#include "Level.h"

const int MAX_LEVEL = 100;

class LevelManager : public df::Manager {
private:
  LevelManager( void );                   // No construction
  LevelManager( LevelManager const& );    // No copying
  void operator=( LevelManager const& );  // No assignment

  Level* level_arr[MAX_LEVEL];
  int active_level;

public:
  static LevelManager& getInstance( void );

  int startUp( void );
  void shutDown( void );

  int loadLevel( std::string filename, int level_num );
  int unloadLevel( int level_num );
  // Start a level. If level_num is -1, start (active_level + 1)
  int startLevel( int level_num );
  Level* getActiveLevel() const;
};

#endif
