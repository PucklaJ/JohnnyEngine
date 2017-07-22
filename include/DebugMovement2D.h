#pragma once
#include "Actor.h"

namespace Johnny
{
	class DebugMovement2D : public Actor
	{
	public:
		DebugMovement2D(float moveSpeed = 100.0f, float zoomSpeed = 0.4f, float rotateSpeed = 10.0f);
		~DebugMovement2D();

		bool update() override;

	private:
		float m_moveSpeed = 100.0f;
		float m_zoomSpeed = 0.4f;
		float m_rotateSpeed = 10.0f;
	};
}