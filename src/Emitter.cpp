#include "Emitter.h"
#include "ldutil.h"

#include <EventStep.h>
#include <GraphicsManager.h>
#include <LogManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>

void Emitter::laserHit( Laser *laserptr ) {
	df::WorldManager::getInstance( ).markForDelete( laserptr );
}

Emitter::Emitter( void ) {
	this->constructorHelper( laser::Color( ) );
}

Emitter::Emitter( Direction dir ) {
	this->setDirection( dir );
	this->constructorHelper( laser::Color( ) );
}

Emitter::Emitter( laser::Color color ) {
	this->constructorHelper( color );
}

Emitter::Emitter( laser::Color color, Direction dir ) {
	this->setDirection( dir );
	this->constructorHelper( color );
}

Emitter::Emitter( df::Color color ) {
	this->constructorHelper( laser::Color( color ) );
}

Emitter::Emitter( df::Color color, Direction dir ) {
	this->setDirection( dir );
	this->constructorHelper( laser::Color( color ) );
}

void Emitter::constructorHelper( laser::Color color ) {
  this->color = color;
  this->registerInterest( df::STEP_EVENT );
  this->setType(EMITTER);
  df::Sprite *temp_sprite =
    df::ResourceManager::getInstance().getSprite(EMITTER);
  if (!temp_sprite) {
    DF_LOG("Emitter::Emitter(): Warning! Sprite '%s' not found", EMITTER);
  } else {
    this->setSprite(temp_sprite);
  }
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

int Emitter::eventHandler( const df::Event *event ) {
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
		Laser* laser = new Laser( this->getColor( ), this->getDirection( ) );
		laser->setPosition( pos );
		return 1;
	}
	return Component::eventHandler( event );
}

void Emitter::draw( void ) {
  Object::draw();
  df::GraphicsManager::getInstance().drawCh(getPosition(), 'O',
      this->color.getColor());
}
