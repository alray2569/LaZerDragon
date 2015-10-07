#include "EventReceiverActive.h"

EventReceiverActive::EventReceiverActive( Receiver *receiverptr ) {
	this->setType( RECEIVER_ACTIVE_EVENT );
	this->receiver = receiverptr;
}

Receiver *EventReceiverActive::getReceiver( void ) const {
	return this->receiver;
}