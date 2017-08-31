/*
 * ContactListener.h
 *
 *  Created on: 02.04.2017
 *      Author: johnny
 */

#ifndef INCLUDE_CONTACTLISTENER_H_
#define INCLUDE_CONTACTLISTENER_H_
#include <Box2D/Box2D.h>


namespace Johnny
{
	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		virtual ~ContactListener();

		virtual void BeginContact(b2Contact*) override;
		virtual void EndContact(b2Contact*) override;

		virtual void PreSolve(b2Contact*,const b2Manifold*) override;
		virtual void PostSolve(b2Contact*,const b2ContactImpulse*) override;

	};
}


#endif /* INCLUDE_CONTACTLISTENER_H_ */
