#include "Level.h"
#include <WorldManager.h>
#include <EventStep.h>
#include <EventView.h>
#include <Position.h>
#include <GameManager.h>
#include <GraphicsManager.h>
#include <ResourceManager.h>
#include "EventReceiverActive.h"
#include "ldutil.h"
#include "LevelManager.h"

Level::Level( int levelnum ) {
	this->levelnum = levelnum;
	this->components = df::ObjectList( );
	this->setAltitude(4);
	this->setSolidness( df::SPECTRAL );
	this->receivers = 0;
	this->active = 0;
	this->registerInterest( df::STEP_EVENT );
	this->registerInterest( RECEIVER_ACTIVE_EVENT );
	this->isLevelOver = false;
	this->setActive( false );
	setLevelString("");
	setTitle("");
	setCount("mirror", 0);
	setCount("lens", 0);
	setCount("prism", 0);
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

int Level::removeComponent( Component *comp ) {
	return this->components.remove( comp );
}

df::ObjectList Level::getComponents( void ) const {
	return df::ObjectList( this->components );
}

int Level::getLevelNum( void ) const {
	return this->levelnum;
}

void Level::setLevelOver( void ) {
	df::WorldManager &world_manager = df::WorldManager::getInstance();

	// Play TaDa
	df::ResourceManager::getInstance( ).getSound( "tada" )->play( false );

	// Remove components
	df::ObjectListIterator oli( &this->components );
	for ( oli.first( ); !oli.isDone( ); oli.next( ) ) {
		world_manager.markForDelete( oli.currentObject( ) );
	}

	// Remove lasers
	df::ObjectList lasers = world_manager.getSceneGraph().visibleObjects(2);
	df::ObjectListIterator laser_iter( &lasers );
	for ( laser_iter.first(); !laser_iter.isDone(); laser_iter.next() ) {
		world_manager.markForDelete( laser_iter.currentObject() );
	}

	this->isLevelOver = true;
	this->setActive( false );

	if (LevelManager::getInstance( ).startLevel( -1 )) {
		df::GameManager::getInstance( ).setGameOver();
	}
}

int Level::eventHandler( const df::Event *evt ) {
	if ( evt->getType( ) == RECEIVER_ACTIVE_EVENT && static_cast <const EventReceiverActive*> ( evt )->getLvlNum( ) == this->getLevelNum( ) ) {
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
  df::WorldManager &world_manager = df::WorldManager::getInstance();
  df::EventView mirrorEvt("mirror", counts["mirror"], false);
  world_manager.onEvent(&mirrorEvt);
  df::EventView lensEvt("lens", counts["lens"], false);
  world_manager.onEvent(&lensEvt);
  df::EventView prismEvt("prism", counts["prism"], false);
  world_manager.onEvent(&prismEvt);

  this->setActive( true );
}

void Level::setTitle( std::string title ) {
  this->title = title;
}
std::string Level::getTitle( void ) const {
  return this->title;
}

void Level::setCount(std::string type, int count) {
  this->counts[type] = count;
}
int Level::getCount(std::string type) {
  return counts[type];
}

void Level::draw( void ) {
  df::GraphicsManager::getInstance().drawString( gridToPos(df::Position(0,0)),
      title, df::LEFT_JUSTIFIED, df::CYAN);
}
