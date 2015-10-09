#ifndef RECEIVER_H
#define RECEIVER_H
#include "Component.h"
#include "LaserColor.h"

class Receiver: public Component {
private:
	laser::Color color;

	void laserHit( Laser* );

public:
	Receiver( laser::Color = laser::WHITE );
	Receiver( df::Color );

	int eventHandler( const df::Event* );
  virtual void draw( void );
};

#endif
