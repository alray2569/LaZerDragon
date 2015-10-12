#ifndef LEVEL_H
#define LEVEL_H

#include <map>
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
  std::string level_string;
  std::string title;
  // counts is an map of component types to their counts
  std::map<std::string, int> counts;

public:
	Level( int levelnum );

	int addComponent( Component* );
	df::ObjectList getComponents( void ) const;

	int getLevelNum( void ) const;

	void setLevelOver( void );

	int eventHandler( const df::Event* );

	bool getLevelOver( void ) const;

  void setLevelString( std::string );
  std::string getLevelString( void ) const;

  void start( void );

  void setTitle( std::string );
  std::string getTitle( void ) const;

  void setCount( std::string, int );
  int getCount( std::string );

  void draw( void );
};

#endif
