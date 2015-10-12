#ifndef RECEIVER_H
#define RECEIVER_H
#include "Component.h"
#include "LaserColor.h"

enum ReceiverState {
  INACTIVE,
  ACTIVE,
  STOPPING
};

class Receiver: public Component {
private:
	laser::Color color;
	ReceiverState state;

	void laserHit( Laser* );

public:
	Receiver( laser::Color = laser::WHITE );
	Receiver( df::Color );
	~Receiver();

  void setState( ReceiverState );
  ReceiverState getState( void ) const;

	int eventHandler( const df::Event* );
  virtual void draw( void );
};

#endif
