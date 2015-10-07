#include "Level.h"
#include <WorldManager.h>
#include <EventStep.h>
#include "EventReceiverActive.h"

Level::Level( int levelnum ) {
	this->levelnum = levelnum;
	this->components = df::ObjectList( );
	this->setSolidness( df::SPECTRAL );
	this->receivers = 0;
	this->active = 0;
	this->registerInterest( df::STEP_EVENT );
	this->registerInterest( RECEIVER_ACTIVE_EVENT );
}

int Level::addComponent( Component *comp ) {
	df::ObjectListIterator oli( &this->components );

	for ( oli.first( ); !oli.isDone( ); oli.next( ) ) {
		if ( oli.currentObject( )->getPosition( ) == comp->getPosition( ) ) {
			return -1;
		}
	}

	if ( dynamic_cast <Receiver *> ( comp ) ) {
		this->receivers++;
	}

	return this->components.insert( comp );
}

df::ObjectList Level::getComponents( void ) const {
	return df::ObjectList( this->components );
}

int Level::getLevelNum( void ) const {
	return this->levelnum;
}

void Level::setLevelOver( void ) {
	df::ObjectListIterator oli( &this->components );

	for ( oli.first( ); !oli.isDone( ); oli.next( ) ) {
		df::WorldManager::getInstance( ).markForDelete( oli.currentObject( ) );
	}

	df::WorldManager::getInstance( ).markForDelete( this );
}

int Level::eventHandler( const df::Event *evt ) {
	if ( evt->getType( ) == RECEIVER_ACTIVE_EVENT ) {
		this->active++;
		return 1;
	}
	else if ( evt->getType( ) == df::STEP_EVENT ) {
		this->active = 0;
	}
}