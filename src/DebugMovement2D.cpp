#include "../include/DebugMovement2D.h"
#include "../include/MainClass.h"
#include "../include/Camera2D.h"
#include "../include/InputManager.h"
#include "../include/Timer.h"

namespace Johnny
{
	DebugMovement2D::DebugMovement2D(float moveSpeed, float zoomSpeed, float rotateSpeed) :
		m_moveSpeed(moveSpeed),
		m_zoomSpeed(zoomSpeed),
		m_rotateSpeed(rotateSpeed)
	{
        m_castsShadows3D = false;
	}

	DebugMovement2D::~DebugMovement2D()
	{

	}

	bool DebugMovement2D::update()
	{
		if (m_mainClass->getInputManager()->isPressed(Keys::W))
		{
			m_mainClass->getCamera2D()->addPosition(0.0f, m_moveSpeed * m_mainClass->getTimer()->getDeltaTimeInSeconds(), true);
		}
		else if (m_mainClass->getInputManager()->isPressed(Keys::S))
		{
			m_mainClass->getCamera2D()->addPosition(0.0f, -m_moveSpeed * m_mainClass->getTimer()->getDeltaTimeInSeconds(), true);
		}
		else if (m_mainClass->getInputManager()->isPressed(Keys::A))
		{
			m_mainClass->getCamera2D()->addPosition(-m_moveSpeed * m_mainClass->getTimer()->getDeltaTimeInSeconds(),0.0f, true);
		}
		else if (m_mainClass->getInputManager()->isPressed(Keys::D))
		{
			m_mainClass->getCamera2D()->addPosition(m_moveSpeed * m_mainClass->getTimer()->getDeltaTimeInSeconds(),0.0f, true);
		}

		if (m_mainClass->getInputManager()->isPressed(Keys::J))
		{
			m_mainClass->getCamera2D()->addRotation(-m_rotateSpeed * m_mainClass->getTimer()->getDeltaTimeInSeconds());
		}
		else if (m_mainClass->getInputManager()->isPressed(Keys::K))
		{
			m_mainClass->getCamera2D()->addRotation(m_rotateSpeed * m_mainClass->getTimer()->getDeltaTimeInSeconds());
		}

		m_mainClass->getCamera2D()->addZoom((float)m_mainClass->getInputManager()->getMouse().wheel_y*m_zoomSpeed*m_mainClass->getTimer()->getDeltaTimeInSeconds());

		return true;
	}
}