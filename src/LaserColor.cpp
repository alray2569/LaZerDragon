// LaZerDragon
// char *args[]
// Andrew Ray
// IMGD 3000

// Color for lasers. Allows color combination

// Game includes
#include "LaserColor.h"
#include "ldutil.h"


const uint8_t RMASK = 4;
const uint8_t GMASK = 2;
const uint8_t BMASK = 1;
const uint8_t CMASK = 7;

/* private */ laser::Color::Color( uint8_t cdata ) {
	this->color = cdata;
}

laser::Color::Color( void ) {
	*this = laser::WHITE;
}

laser::Color::Color( bool red, bool green, bool blue ) {
	this->color =
		red ? RMASK : 0 +
		green ? GMASK : 0 +
		blue ? BMASK : 0;
}

laser::Color::Color( enum df::Color dfcolor ) {
	this->setColor( dfcolor );
}

void laser::Color::setRed( bool red /* = true */ ) {
	if ( red ) {
		this->color |= RMASK;
	}
	else {
		this->color &= ~RMASK;
	}
}

void laser::Color::setGreen( bool green /* = true */ ) {
	if ( green ) {
		this->color |= GMASK;
	}
	else {
		this->color &= ~GMASK;
	}
}

void laser::Color::setBlue( bool blue /* = true */ ) {
	if ( blue ) {
		this->color |= BMASK;
	}
	else {
		this->color &= ~GMASK;
	}
}

bool laser::Color::getRed( void ) const {
	return !!(this->color & RMASK);
}

bool laser::Color::getGreen( void ) const {
	return !!( this->color & GMASK );
}

bool laser::Color::getBlue( void ) const {
	return !!( this->color & BMASK );
}

laser::Color laser::Color::operator+( const laser::Color &other ) const {
	return laser::Color( this->color | other.color );
}

laser::Color laser::Color::operator-( const laser::Color &other ) const {
	return laser::Color( this->color &~ other.color );
}

laser::Color laser::Color::operator*( const laser::Color &other ) const {
	return laser::Color( this->color & other.color );
}

laser::Color laser::Color::operator+=( const laser::Color &other ) {
	this->color |= other.color;
	return *this;
}

laser::Color laser::Color::operator-=( const laser::Color &other ) {
	this->color &= ~other.color;

	return *this;
}

laser::Color laser::Color::operator*=( const laser::Color &other ) {
	this->color &= other.color;
	return *this;
}

int laser::Color::operator==( const laser::Color &other ) const {
	return ( this->color & CMASK ) == ( other.color & CMASK );
}

int laser::Color::operator!=( const laser::Color &other ) const {
	return !( *this == other );
}

void laser::Color::setColor( enum df::Color dfcolor ) {
	switch ( dfcolor ) {
	case df::Color::BLACK:
		this->color = laser::BLACK.color;
		break;
	case df::Color::RED:
		this->color = laser::RED.color;
		break;
	case df::Color::YELLOW:
		this->color = laser::YELLOW.color;
		break;
	case df::Color::GREEN:
		this->color = laser::GREEN.color;
		break;
	case df::Color::CYAN:
		this->color = laser::CYAN.color;
		break;
	case df::Color::BLUE:
		this->color = laser::BLUE.color;
		break;
	case df::Color::MAGENTA:
		this->color = laser::MAGENTA.color;
		break;
	case df::Color::WHITE:
		this->color = laser::WHITE.color;
		break;
	default:
		DF_LOG( "laser::Color::setColor(): A problem has occurred. The given color does not correspond to a laser::Color." );
		break;
	}
}

enum df::Color laser::Color::getColor( void ) const {
	if ( *this == laser::BLACK ) return df::Color::BLACK;
	if ( *this == laser::RED ) return df::Color::RED;
	if ( *this == laser::YELLOW ) return df::Color::YELLOW;
	if ( *this == laser::GREEN ) return df::Color::GREEN;
	if ( *this == laser::BLUE ) return df::Color::BLUE;
	if ( *this == laser::MAGENTA ) return df::Color::MAGENTA;
	if ( *this == laser::CYAN ) return df::Color::CYAN;
	if ( *this == laser::WHITE ) return df::Color::WHITE;
	DF_LOG( "laser::Color::getColor(): A problem has occurred. This laser's color does not correspond to a df::Color." );
	return df::COLOR_DEFAULT;
}