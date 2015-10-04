#ifndef MIRROR_H
#define  MIRROR_H
#include "Component.h"

#define MIRROR "mirror"

class Mirror: public Component {
private:
	void laserHit( Laser* );
	bool checkUpRt( void ) const;
	bool checkDnRt( void ) const;
	void rotateLaser( Laser* ) const;

public:
	Mirror( void );
};

#endif
