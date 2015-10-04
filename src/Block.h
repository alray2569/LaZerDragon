// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Block component (destroys lasers)

#ifndef BLOCK_H
#define BLOCK_H

// Game includes
#include "Component.h"

#define BLOCK "block"

class Block : public Component {
private:
  void laserHit( Laser* );

public:
  Block();
};

#endif
