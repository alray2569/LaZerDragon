#include "Level.h"
#include <WorldManager.h>
#include <EventStep.h>
#include <Position.h>
#include <GameManager.h>
#include "EventReceiverActive.h"
#include "ldutil.h"

Level::Level( int levelnum ) {
	this->levelnum = levelnum;
	this->components = df::ObjectList( );
	this->setSolidness( df::SPECTRAL );
	this->receivers = 0;
	this->active = 0;
	this->registerInterest( df::STEP_EVENT );
	this->registerInterest( RECEIVER_ACTIVE_EVENT );
	this->isLevelOver = false;
	setLevelString("");
}

int Level::addComponent( Component *comp ) {
	df::ObjectListIterator oli( &this->components );

	for ( oli.first( ); !oli.isDone( ); oli.next( ) ) {
		df::Position pos = comp->getPosition( );
		if ( oli.currentObject( )->getPosition( ) == pos ) {
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

	this->isLevelOver = true;

	df::GameManager::getInstance( ).setGameOver( true );
}

int Level::eventHandler( const df::Event *evt ) {
	if ( evt->getType( ) == RECEIVER_ACTIVE_EVENT ) {
		this->active++;

		if ( this->active == this->receivers ) {
			this->setLevelOver( );
		}

		return 1;
	}
	else if ( evt->getType( ) == df::STEP_EVENT ) {
		this->active = 0;
		return 1;
	}
	return 0;
}

bool Level::getLevelOver( void ) const {
	return this->isLevelOver;
}

void Level::setLevelString( std::string level_string ) {
  this->level_string = level_string;
}
std::string Level::getLevelString( void ) const {
  return this->level_string;
}

void Level::start() {
  for (int y = 0; y < GRID_HEIGHT; y++) {
    for (int x = 0; x < GRID_WIDTH; x++) {
      char c = level_string[x + y * GRID_WIDTH];
      Component* component = getComponent(c);
      if (component) {
        component->setGridPosition( df::Position(x, y));
        this->addComponent(component);
      }
    }
  }
}
