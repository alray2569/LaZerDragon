#include "EventReceiverActive.h"

EventReceiverActive::EventReceiverActive( Receiver *receiverptr, int lvlnum ) {
	this->setType( RECEIVER_ACTIVE_EVENT );
	this->receiver = receiverptr;
	this->lvlnum = lvlnum;
}

Receiver *EventReceiverActive::getReceiver( void ) const {
	return this->receiver;
}

int EventReceiverActive::getLvlNum( void ) const {
	return this->lvlnum;
}