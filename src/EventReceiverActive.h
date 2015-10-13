#ifndef EVENT_RECEIVER_ACTIVE_H
#define EVENT_RECEIVER_ACTIVE_H

#include <string>
#include <Event.h>
#include "Receiver.h"


const std::string RECEIVER_ACTIVE_EVENT = "receiver_active";

class EventReceiverActive: public df::Event {
private:
	Receiver *receiver;
	int lvlnum;

public:
	EventReceiverActive( Receiver *receiver, int );

	Receiver *getReceiver( void ) const;
	int getLvlNum( void ) const;
};

#endif