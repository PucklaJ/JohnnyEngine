#pragma once
#include "Actor.h"
class DebugMovement :
	public SDL::Actor
{
public:
	DebugMovement(float moveSpeed = 12.0f,float lookSpeed = 1.0f);
	~DebugMovement();

	bool init() override;
	bool update() override;
private:
	float m_moveSpeed = 10.0f;
	float m_lookSpeed = 0.7f;
};

