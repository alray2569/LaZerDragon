#include "Receiver.h"
#include "EventReceiverActive.h"
#include <WorldManager.h>
#include <EventStep.h>
#include <GraphicsManager.h>
#include <ResourceManager.h>
#include "LevelManager.h"

Receiver::Receiver( laser::Color color /* = laser::WHITE */ ) {
	this->color = color;
	this->registerInterest( df::STEP_EVENT );
	this->setType( "Receiver" );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "receiver" ),
			false);
	this->state = INACTIVE;
}

Receiver::Receiver( df::Color color ) {
	this->color = laser::Color( color );
	this->registerInterest( df::STEP_EVENT );
	this->setType( "Receiver" );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "receiver" ),
			false);
	this->state = INACTIVE;
}

Receiver::~Receiver() {
  df::ResourceManager::getInstance().getSound(color.getColorName())->stop();
}

void Receiver::setState( ReceiverState state ) {
  if (this->state == state) {
    return;
  } else if (state == INACTIVE) {
    df::ResourceManager::getInstance().getSound(color.getColorName())->stop();
  } else if (this->state == INACTIVE) {
    df::ResourceManager::getInstance().getSound(color.getColorName())->play(true);
  }
  this->state = state;
}
ReceiverState Receiver::getState( void ) const {
  return this->state;
};

void Receiver::laserHit( Laser *laserPtr ) {
  if (laserPtr->getColor() == this->color) {
    this->setState(ACTIVE);
    df::Event evt = EventReceiverActive( this, LevelManager::getInstance( ).getActiveLevel( )->getLevelNum( ) );
    df::WorldManager::getInstance( ).onEvent( &evt );
  }
  df::WorldManager::getInstance( ).markForDelete( laserPtr );
}

int Receiver::eventHandler( const df::Event *event ) {
	if ( event->getType( ) == df::STEP_EVENT ) {
    if (this->getState() == ACTIVE) {
      this->setState(STOPPING);
    } else if (this->getState() == STOPPING) {
      this->setState(INACTIVE);
    }
		return 1;
	}
	return Component::eventHandler( event );
}

void Receiver::draw( void ) {
  Object::draw();
  df::GraphicsManager::getInstance().drawCh(getPosition(), 'O',
      this->color.getColor());
}
