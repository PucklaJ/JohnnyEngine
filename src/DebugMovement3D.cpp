#include "../include/DebugMovement3D.h"
#include "../include/MainClass.h"
#include "../include/Camera3D.h"
#include "../include/Timer.h"
#include "../include/InputManager.h"

namespace Johnny
{
	DebugMovement3D::DebugMovement3D(float moveSpeed, float lookSpeed) : Actor("DebugMovement"),
		m_moveSpeed(moveSpeed),
		m_lookSpeed(lookSpeed)
	{
        m_castsShadows3D = false;
	}

	DebugMovement3D::~DebugMovement3D()
	{
	}

	bool DebugMovement3D::init()
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);

		return true;
	}

	bool DebugMovement3D::update()
	{
		if (m_mainClass->getInputManager()->isPressed(Keys::LSHIFT))
			m_moveSpeed *= 5.0f;
        else if(m_mainClass->getInputManager()->isPressed(Keys::LCTRL))
            m_moveSpeed /= 5.0f;

		if (m_mainClass->getInputManager()->isPressed(Keys::W))
		{
			m_mainClass->getCamera3D()->addPosition(0.0, 0.0, -m_moveSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds(), true);
		}
		if (m_mainClass->getInputManager()->isPressed(Keys::S))
		{
			m_mainClass->getCamera3D()->addPosition(0.0, 0.0, m_moveSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds(), true);
		}
		if (m_mainClass->getInputManager()->isPressed(Keys::A))
		{
			m_mainClass->getCamera3D()->addPosition(-m_moveSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds(), 0.0, 0.0, true);
		}
		if (m_mainClass->getInputManager()->isPressed(Keys::D))
		{
			m_mainClass->getCamera3D()->addPosition(m_moveSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds(), 0.0, 0.0, true);
		}
		if (m_mainClass->getInputManager()->isPressed(Keys::K))
		{
			m_mainClass->getCamera3D()->addPosition(0.0, -m_moveSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds(), 0.0, false);
		}
		if (m_mainClass->getInputManager()->isPressed(Keys::I))
		{
			m_mainClass->getCamera3D()->addPosition(0.0, m_moveSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds(), 0.0, false);
		}

		if (m_mainClass->getInputManager()->isPressed(Keys::LSHIFT))
			m_moveSpeed /= 5.0f;
        else if(m_mainClass->getInputManager()->isPressed(Keys::LCTRL))
            m_moveSpeed *= 5.0f;


		if (m_mainClass->getInputManager()->justPressed(Keys::ESCAPE))
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}

		if (SDL_GetRelativeMouseMode())
		{
			GLfloat x = -m_lookSpeed * (float)m_mainClass->getInputManager()->getMouse().yrel;
			GLfloat y = -m_lookSpeed * (float)m_mainClass->getInputManager()->getMouse().xrel;
			GLfloat z = m_lookSpeed * (float)m_mainClass->getInputManager()->getMouse().wheel_y*10.0f*m_mainClass->getTimer()->getDeltaTimeInSeconds();

			m_mainClass->getCamera3D()->addRotation(x,y,z);
		}
		else if (m_mainClass->getInputManager()->justPressed(Keys::MS_LEFT))
		{
			SDL_SetRelativeMouseMode(SDL_TRUE);
		}

		return true;
	}

}