#include "TitleScreen.h"
#include <EventMouse.h>
#include <GameManager.h>
#include <ResourceManager.h>
#include <WorldManager.h>
#include "LevelManager.h"
#include "ComponentCount.h"

TitleScreen::TitleScreen( ) {
	this->setType( "titleScn" );
	this->registerInterest( df::MOUSE_EVENT );
	this->setSolidness( df::SPECTRAL );
	this->setSprite( df::ResourceManager::getInstance( ).getSprite( "titlescreen" ) );
	this->setSpriteSlowdown( 30 );
	df::WorldManager &wm = df::WorldManager::getInstance( );
	this->setPosition( df::Position( wm.getBoundary( ).getHorizontal( ) / 2, wm.getBoundary( ).getVertical( ) / 2 ) );
}

int TitleScreen::eventHandler( const df::Event *evt ) {
	if ( evt->getType( ) == df::MOUSE_EVENT ) {
		const df::EventMouse *mevt = static_cast <const df::EventMouse*> ( evt );
		if ( mevt->getMouseAction( ) == df::CLICKED ) {
			if ( mevt->getMouseButton( ) == df::Mouse::LEFT ) {
				// Here we can finish setting up the level.
				// Initialize the counters.
				ComponentCount* mirror_count = new ComponentCount( "mirror", 0 );
				ComponentCount* lens_count = new ComponentCount( "lens", 0 );
				ComponentCount* prism_count = new ComponentCount( "prism", 0 );
				mirror_count->setLocation( df::BOTTOM_LEFT );
				lens_count->setLocation( df::BOTTOM_CENTER );
				prism_count->setLocation( df::BOTTOM_RIGHT );
				mirror_count->setSelected( );

				// Start the first level
				LevelManager::getInstance( ).startLevel( 0 );

				// Play the click sound
				df::ResourceManager::getInstance().getSound("click")->play();

				// Delete this object
				df::WorldManager::getInstance( ).markForDelete( this );
				return 1;
			}
			else if ( mevt->getMouseButton( ) == df::Mouse::RIGHT ) {
				df::GameManager::getInstance( ).setGameOver( true );
				return 1;
			}
		}
	}
	return 0;
}