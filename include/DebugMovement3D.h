#pragma once
#include "../include/Actor.h"

namespace Johnny
{

	class DebugMovement3D : public Actor
	{
	public:
		DebugMovement3D(float moveSpeed = 12.0f, float lookSpeed = 1.0f);
		~DebugMovement3D();

		bool init() override;
		bool update() override;
	private:
		float m_moveSpeed = 10.0f;
		float m_lookSpeed = 0.7f;
	};
}