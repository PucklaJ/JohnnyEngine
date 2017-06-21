#include "DebugMovement.h"
#include "MainClass.h"
#include "Camera.h"

DebugMovement::DebugMovement(float moveSpeed, float lookSpeed) : SDL::Actor("DebugMovement"),
	m_moveSpeed(moveSpeed),
	m_lookSpeed(lookSpeed)
{
}

DebugMovement::~DebugMovement()
{
}

bool DebugMovement::init()
{
	SDL_SetRelativeMouseMode(SDL_TRUE);

	return true;
}

bool DebugMovement::update()
{
	if (m_mainClass->getInputManager()->isPressed(SDLK_LSHIFT))
		m_moveSpeed *= 5.0f;

	if (m_mainClass->getInputManager()->isPressed(SDLK_w))
	{
		m_mainClass->getCamera()->addPosition(0.0, 0.0, -m_moveSpeed*m_mainClass->getDeltaTimeInSeconds(), true);
	}
	if (m_mainClass->getInputManager()->isPressed(SDLK_s))
	{
		m_mainClass->getCamera()->addPosition(0.0, 0.0, m_moveSpeed*m_mainClass->getDeltaTimeInSeconds(), true);
	}
	if (m_mainClass->getInputManager()->isPressed(SDLK_a))
	{
		m_mainClass->getCamera()->addPosition(-m_moveSpeed*m_mainClass->getDeltaTimeInSeconds(), 0.0, 0.0, true);
	}
	if (m_mainClass->getInputManager()->isPressed(SDLK_d))
	{
		m_mainClass->getCamera()->addPosition(m_moveSpeed*m_mainClass->getDeltaTimeInSeconds(), 0.0, 0.0, true);
	}
	if (m_mainClass->getInputManager()->isPressed(SDLK_k))
	{
		m_mainClass->getCamera()->addPosition(0.0, -m_moveSpeed*m_mainClass->getDeltaTimeInSeconds(), 0.0, false);
	}
	if (m_mainClass->getInputManager()->isPressed(SDLK_i))
	{
		m_mainClass->getCamera()->addPosition(0.0, m_moveSpeed*m_mainClass->getDeltaTimeInSeconds(), 0.0, false);
	}

	if (m_mainClass->getInputManager()->isPressed(SDLK_LSHIFT))
		m_moveSpeed /= 5.0f;


	if (m_mainClass->getInputManager()->justPressed(SDLK_ESCAPE))
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}

	if (SDL_GetRelativeMouseMode())
	{
		m_mainClass->getCamera()->addRotation(-m_lookSpeed * (float)m_mainClass->getInputManager()->getMouse().yrel, -m_lookSpeed * (float)m_mainClass->getInputManager()->getMouse().xrel, m_lookSpeed * (float)m_mainClass->getInputManager()->getMouse().wheel_y*10.0f*m_mainClass->getDeltaTimeInSeconds());
	}
	else if(m_mainClass->getInputManager()->justPressed(SDL_BUTTON_LEFT))
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	return true;
}
