#ifndef LEVEL_H
#define LEVEL_H

#include <Object.h>
#include <ObjectList.h>
#include "Component.h"

class Level: public df::Object {
private:
	df::ObjectList components;
	int levelnum;
	int receivers;
	int active;
	bool isLevelOver;

public:
	Level( int levelnum );

	int addComponent( Component* );
	df::ObjectList getComponents( void ) const;
	
	int getLevelNum( void ) const;

	void setLevelOver( void );

	int eventHandler( const df::Event* );

	bool getLevelOver( void ) const;
};

#endif
