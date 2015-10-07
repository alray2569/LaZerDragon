// LaZerDragon
// char *args[]
// Gareth Solbeck
// IMGD 3000

// Component count view object

#ifndef COMPONENTCOUNT_H
#define COMPONENTCOUNT_H

#include "ViewObject.h"


class ComponentCount : public df::ViewObject {
private:
  // Returns true if component was placed successfully
  virtual bool placeComponent( df::Position );

  // Disallow default constructor
  ComponentCount();

public:
  ComponentCount( std::string type, int initial_count=0 );

  virtual int eventHandler( const df::Event* );

  void setComponentType( std::string );
  std::string getComponentType( void );
};

#endif
