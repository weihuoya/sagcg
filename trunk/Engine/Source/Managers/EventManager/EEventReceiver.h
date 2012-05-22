#ifndef EEventReceiver_H
#define EEventReceiver_H

#include <map>
#include <list>
#include "EEventReceiver.h"
#include "EEvent.h"

class EEvent;
class EventManager;

class EEventReceiver
{
	protected:
		EEventReceiver()	{};
	public:
		virtual			~EEventReceiver()	{};

	public:
		virtual void	onEvent ( const EEvent *ev, const EventManager *evMgr ) = 0;
};

#endif // EEventReceiver_H
