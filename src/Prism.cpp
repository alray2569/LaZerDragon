#include "Prism.h"
#include <ResourceManager.h>
#include "LaserColor.h"
#include "Direction.h"
#include <EventStep.h>

Prism::Prism( void ) {
	this->setType( PRISM );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "prism" ), false      );
	this->registerInterest( df::STEP_EVENT );
}

void Prism::laserHit( Laser *laserptr ) {
	this->numL++;

	if ( this->numL == 1 ) {
		this->in = laserptr;
	}
	else if ( this->numL == 2 ) {
		this->in = NULL;
	}
}

int Prism::eventHandler( const df::Event *evt ) {
	if ( evt->getType( ) == df::STEP_EVENT ) {
		if ( this->in ) {
			Laser *left = new Laser( this->in->getColor( ) * laser::RED, rotateDirection( this->in->getDirection( ), 1 ) );
			Laser *midd = new Laser( this->in->getColor( ) * laser::GREEN, rotateDirection( this->in->getDirection( ), 2 ) );
			Laser *rght = new Laser( this->in->getColor( ) * laser::BLUE, rotateDirection( this->in->getDirection( ), 3 ) );
			df::Position lpos = this->getPosition( );
			df::Position mpos = this->getPosition( );
			df::Position rpos = this->getPosition( );
		}
		this->numL = 0;
		this->in = NULL;
		return 1;
	}
	return Component::eventHandler( evt );
}