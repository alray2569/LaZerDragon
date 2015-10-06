#include "Emitter.h"
#include <EventStep.h>
#include <WorldManager.h>

void laserHit( Laser *laserptr ) {
	df::WorldManager::getInstance( ).markForDelete( laserptr );
}

Emitter::Emitter( void ) {
	this->color = laser::Color( );
	this->registerInterest( df::STEP_EVENT );
}

Emitter::Emitter( Direction dir ) {
	this->color = laser::Color( );
	this->setDirection( dir );
	this->registerInterest( df::STEP_EVENT );
}

Emitter::Emitter( laser::Color color ) {
	this->color = color;
	this->registerInterest( df::STEP_EVENT );
}

Emitter::Emitter( laser::Color color, Direction dir ) {
	this->color = color;
	this->setDirection( dir );
	this->registerInterest( df::STEP_EVENT );
}

Emitter::Emitter( df::Color color ) {
	this->color = laser::Color( color );
	this->registerInterest( df::STEP_EVENT );
}

Emitter::Emitter( df::Color color, Direction dir ) {
	this->color = laser::Color( color );
	this->setDirection( dir );
	this->registerInterest( df::STEP_EVENT );
}

laser::Color Emitter::getColor( void ) const {
	return this->color;
}

void Emitter::setColor( laser::Color ncolor ) {
	this->color = ncolor;
}

void Emitter::setColor( df::Color ncolor ) {
	this->color = laser::Color( ncolor );
}

int Emitter::eventHandler( df::Event *event ) {
	if ( event->getType( ) == df::STEP_EVENT ) {
		df::Position pos = this->getPosition( );
		switch ( this->getDirection( ) ) {
		case UP:
			pos.setY( pos.getY( ) + 1 );
			break;
		case DOWN:
			pos.setY( pos.getY( ) - 1 );
			break;
		case LEFT:
			pos.setX( pos.getX( ) - 1 );
			break;
		case RIGHT:
			pos.setX( pos.getX( ) + 1 );
			break;
		default:
			break;
		}

		new Laser( this->getColor( ), this->getDirection( ) )->setPosition( pos );
		return 1;
	}
	return Component::eventHandler( event );
}