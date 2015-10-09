#ifndef PRISM_H
#define PRISM_H "Supercalifragilisticexpialidocious"

#include <string>
#include "Component.h"

const std::string PRISM = "prism";

class Prism: public Component {
private:
	void laserHit( Laser* );
	int numL;
	Laser *in;
public:
	Prism( void );
	int eventHandler( const df::Event* );
};

#endif