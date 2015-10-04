#include "Mirror.h"
#include "ldutil.h"
#include <ResourceManager.h>

Mirror::Mirror( void ) /* on the wall */ {
	this->setType( MIRROR );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( MIRROR ), true );
}

/* private */ void Mirror::laserHit( Laser *laserptr ) {
	
}

/* private */ bool Mirror::checkDnRt( void ) const {
	return this->getDirection( ) == Direction::DOWN || this->getDirection( ) == Direction::UP;
}

/* private */ bool Mirror::checkUpRt( void ) const {
	return !this->checkDnRt( );
}

/* private */ void Mirror::rotateLaser( Laser *laserptr ) const {
	Direction ldir = laserptr->getDirection( );
	
	switch ( ldir ) {
	case UP:
		if ( this->checkUpRt( ) ) laserptr->setDirection( RIGHT );
		else laserptr->setDirection( LEFT );
		break;
	case DOWN:
		if ( this->checkUpRt( ) ) laserptr->setDirection( LEFT );
		else laserptr->setDirection( RIGHT );
		break;
	case LEFT:
		if ( this->checkUpRt( ) ) laserptr->setDirection( DOWN );
		else laserptr->setDirection( UP );
		break;
	case RIGHT:
		if ( this->checkUpRt( ) ) laserptr->setDirection( UP );
		else laserptr->setDirection( DOWN );
		break;
	default:
		DF_LOG( "Error!" );
	}
}