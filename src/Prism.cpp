#include "Prism.h"
#include <ResourceManager.h>
#include "LaserColor.h"
#include "Direction.h"
#include <EventStep.h>
#include <WorldManager.h>

Prism::Prism( void ) {
	this->setType( PRISM );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "prism" ), false );
	this->registerInterest( df::STEP_EVENT );

  numL = 0;
  in = NULL;
}

void Prism::laserHit( Laser *laserptr ) {
	this->numL++;

	if ( this->numL == 1 ) {
		this->in = laserptr;
	}
	else if ( this->numL == 2 ) {
    df::WorldManager::getInstance().markForDelete(this->in);
    df::WorldManager::getInstance().markForDelete(laserptr);
		this->in = NULL;
	} else if ( this->numL > 2) {
    df::WorldManager::getInstance().markForDelete(laserptr);
  }
}

int Prism::eventHandler( const df::Event *evt ) {
	if ( evt->getType( ) == df::STEP_EVENT ) {
		if ( this->in ) {
      df::WorldManager::getInstance().markForDelete(this->in);
			Laser *left = new Laser( this->in->getColor( ) * laser::RED, rotateDirection( this->in->getDirection( ), 3 ) );
			Laser *midd = new Laser( this->in->getColor( ) * laser::GREEN, rotateDirection( this->in->getDirection( ), 0 ) );
			Laser *rght = new Laser( this->in->getColor( ) * laser::BLUE, rotateDirection( this->in->getDirection( ), 1 ) );
			df::Position pos = this->getPosition( );
			left->setPosition( pos );
			midd->setPosition( pos );
			rght->setPosition( pos );
		}
		this->numL = 0;
		this->in = NULL;
		return 1;
	}
	return Component::eventHandler( evt );
}