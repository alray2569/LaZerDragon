// LaZerDragon
// char *args[]
// Andrew Ray
// IMGD 3000

// Color for lasers. Allows color combination

#ifndef LASERCOLOR_H
#define LASERCOLOR_H

// Engine includes
#include "Color.h"
#include <cstdint>


namespace laser {

class Color {
 private:
	 Color( uint8_t );

	 uint8_t color;

 public:
   Color( void );
   Color( df::Color );
   Color( bool, bool, bool );

   void setRed( bool = true );
   void setGreen( bool = true );
   void setBlue( bool = true );
   bool getRed( void ) const;
   bool getGreen( void ) const;
   bool getBlue( void ) const;

   void setColor( enum df::Color );
   enum df::Color getColor( void ) const;
   std::string getColorName( void ) const;

   laser::Color operator+( const laser::Color& ) const;
   laser::Color operator-( const laser::Color& ) const;
   laser::Color operator*( const laser::Color& ) const;
   laser::Color operator+=( const laser::Color& );
   laser::Color operator-=( const laser::Color& );
   laser::Color operator*=( const laser::Color& );
   laser::Color operator-( void ) const;
   laser::Color operator+( void ) const;

   int operator==( const laser::Color& ) const;
   int operator!=( const laser::Color& ) const;

};

const laser::Color WHITE = Color( true, true, true );
const laser::Color RED = Color( true, false, false );
const laser::Color YELLOW = Color( true, true, false );
const laser::Color GREEN = Color( false, true, false );
const laser::Color CYAN = Color( false, true, true );
const laser::Color BLUE = Color( false, false, true );
const laser::Color MAGENTA = Color( true, false, true );
const laser::Color BLACK = Color( false, false, false );

}

#endif
