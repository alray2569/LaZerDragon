#include "Receiver.h"
#include "EventReceiverActive.h"
#include <WorldManager.h>
#include <EventStep.h>
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
	df::WorldManager::getInstance( ).markForDelete( laserPtr );

	df::Event evt = EventReceiverActive( this );
	df::WorldManager::getInstance( ).onEvent( &evt );
}

int Receiver::eventHandler( const df::Event *event ) {
	if ( event->getType( ) == df::STEP_EVENT ) {
		return 1;
	}
	return Component::eventHandler( event );
}