/*
 * ContactListener.h
 *
 *  Created on: 02.04.2017
 *      Author: johnny
 */

#ifndef INCLUDE_CONTACTLISTENER_H_
#define INCLUDE_CONTACTLISTENER_H_
#include <box2d/box2d.h>


namespace Johnny
{	
	/*! \brief A class which listens to collisions by Box2D
	 *
	 */
	class ContactListener : public b2ContactListener
	{
	public:
		ContactListener();
		virtual ~ContactListener();

		/*! \brief Gets called when two b2Bodis begin colliding
		 *  \param c The b2Contact of the event
		 */
		virtual void BeginContact(b2Contact* c) override;
		/*! \brief Gets called when two b2Bodis end colliding
		 *  \param c The b2Contact of the event
		 */
		virtual void EndContact(b2Contact* c) override;

		/*! \brief Gets called when two b2Bodis are colliding
		 *  \param c The b2Contact of the event
		 *	\param m The b2Manifold of the event
		 */
		virtual void PreSolve(b2Contact* c,const b2Manifold* m) override;
		/*! \brief Gets called when two b2Bodis are colliding (after preSolve)
		 *  \param c The b2Contact of the event
		 *	\param i The b2ContactImpulse of the event
		 */
		virtual void PostSolve(b2Contact* c,const b2ContactImpulse* i) override;

	};
}


#endif /* INCLUDE_CONTACTLISTENER_H_ */
