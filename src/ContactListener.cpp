/*
 * ContactListener.cpp
 *
 *  Created on: 02.04.2017
 *      Author: johnny
 */
#include "../include/ContactListener.h"
#include "../include/PhysicsSprite2D.h"
#include <iostream>
//#define DEBUG_OUTPUT

namespace Johnny
{
	ContactListener::ContactListener()
	{

	}
	ContactListener::~ContactListener()
	{

	}

	void ContactListener::BeginContact(b2Contact* contact)
	{
#ifdef DEBUG_OUTPUT
		std::cout << "BeginContact" << std::endl;
#endif

		b2Fixture* f1 = contact->GetFixtureA();
		b2Fixture* f2 = contact->GetFixtureB();

		PhysicsSprite2D* spr1 = nullptr;
		PhysicsSprite2D* spr2 = nullptr;

#ifdef DEBUG_OUTPUT
		std::cout << "Casting userdatas" << std::endl;
#endif

		spr1 = static_cast<PhysicsSprite2D*>(f1->GetBody()->GetUserData());
		spr2 = static_cast<PhysicsSprite2D*>(f2->GetBody()->GetUserData());

#ifdef DEBUG_OUTPUT
		std::cout << "Casted userdatas" << std::endl;
#endif

		if(spr1)
		{
#ifdef DEBUG_OUTPUT
		std::cout << "BeginContact Spr1" << std::endl;
#endif
			spr1->BeginContact(contact,f1,f2,spr2);
#ifdef DEBUG_OUTPUT
		std::cout << "BeginContact Spr1 end" << std::endl;
#endif
		}
		if(spr2)
		{
#ifdef DEBUG_OUTPUT
		std::cout << "BeginContact Spr2" << std::endl;
#endif
			spr2->BeginContact(contact,f2,f1,spr1);
#ifdef DEBUG_OUTPUT
		std::cout << "BeginContact Spr2 end" << std::endl;
#endif
		}
#ifdef DEBUG_OUTPUT
		std::cout << "BeginContact End" << std::endl;
#endif
	}
	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* f1 = contact->GetFixtureA();
		b2Fixture* f2 = contact->GetFixtureB();

		PhysicsSprite2D* spr1 = nullptr;
		PhysicsSprite2D* spr2 = nullptr;

		spr1 = static_cast<PhysicsSprite2D*>(f1->GetBody()->GetUserData());
		spr2 = static_cast<PhysicsSprite2D*>(f2->GetBody()->GetUserData());

		if(spr1)
		{
			spr1->EndContact(contact,f1,f2,spr2);
		}
		if(spr2)
		{
			spr2->EndContact(contact,f2,f1,spr1);
		}
	}

	void ContactListener::PreSolve(b2Contact* contact,const b2Manifold* oldManifold)
	{
		b2Fixture* f1 = contact->GetFixtureA();
		b2Fixture* f2 = contact->GetFixtureB();

		PhysicsSprite2D* spr1 = nullptr;
		PhysicsSprite2D* spr2 = nullptr;

		spr1 = static_cast<PhysicsSprite2D*>(f1->GetBody()->GetUserData());
		spr2 = static_cast<PhysicsSprite2D*>(f2->GetBody()->GetUserData());

		if(spr1)
		{
			spr1->PreSolve(contact,f1,f2,oldManifold,spr2);
		}
		if(spr2)
		{
			spr2->PreSolve(contact,f2,f1,oldManifold,spr1);
		}
	}
	void ContactListener::PostSolve(b2Contact* contact,const b2ContactImpulse* impulse)
	{
		b2Fixture* f1 = contact->GetFixtureA();
		b2Fixture* f2 = contact->GetFixtureB();

		PhysicsSprite2D* spr1 = nullptr;
		PhysicsSprite2D* spr2 = nullptr;

		spr1 = static_cast<PhysicsSprite2D*>(f1->GetBody()->GetUserData());
		spr2 = static_cast<PhysicsSprite2D*>(f2->GetBody()->GetUserData());

		if(spr1)
		{
			spr1->PostSolve(contact,f1,f2,impulse,spr2);
		}
		if(spr2)
		{
			spr2->PostSolve(contact,f2,f1,impulse,spr1);
		}
	}
}


