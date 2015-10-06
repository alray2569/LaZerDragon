#pragma once
#include "Component.h"
#include "LaserColor.h"

class Emitter: public Component {
private:
	laser::Color color;

	void laserHit( Laser* );

public:
	Emitter( void );
	Emitter( Direction );
	Emitter( df::Color );
	Emitter( df::Color, Direction );
	Emitter( laser::Color );
	Emitter( laser::Color, Direction );

	laser::Color getColor( void ) const;
	void setColor( laser::Color );
	void setColor( df::Color );

	int eventHandler( df::Event* );
};

