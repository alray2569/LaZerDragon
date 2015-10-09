#include "Receiver.h"
#include "EventReceiverActive.h"
#include <WorldManager.h>
#include <EventStep.h>
#include <GraphicsManager.h>
#include <ResourceManager.h>

Receiver::Receiver( laser::Color color /* = laser::WHITE */ ) {
	this->color = color;
	this->registerInterest( df::STEP_EVENT );
	this->setType( "Receiver" );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "receiver" ) );
}

Receiver::Receiver( df::Color color ) {
	this->color = laser::Color( color );
	this->registerInterest( df::STEP_EVENT );
	this->setType( "Receiver" );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "receiver" ) );
}

void Receiver::laserHit( Laser *laserPtr ) {
  if (laserPtr->getColor() == this->color) {
    df::Event evt = EventReceiverActive( this );
    df::WorldManager::getInstance( ).onEvent( &evt );
  }
  df::WorldManager::getInstance( ).markForDelete( laserPtr );
}

int Receiver::eventHandler( const df::Event *event ) {
	if ( event->getType( ) == df::STEP_EVENT ) {
		return 1;
	}
	return Component::eventHandler( event );
}

void Receiver::draw( void ) {
  Object::draw();
  df::GraphicsManager::getInstance().drawCh(getPosition(), 'O',
      this->color.getColor());
}
