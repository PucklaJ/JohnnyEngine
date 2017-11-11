#ifndef JOHNNY_DEFINES_H
#define JOHNNY_DEFINES_H

#define JOHNNY_RES (m_mainClass->getResourceManger())
#define JOHNNY_NATIVE_RES (m_mainClass->getNativeRes())
#define JOHNNY_NATIVE_RES_WIDTH (JOHNNY_NATIVE_RES.width)
#define JOHNNY_NATIVE_RES_HEIGHT (JOHNNY_NATIVE_RES.height)
#define JOHNNY_SKY (m_mainClass->getSkybox())
#define JOHNNY_DT (m_mainClass->getTimer()->getDeltaTimeInSeconds())
#define JOHNNY_INPUT (m_mainClass->getInputManager())
#define JOHNNY_JOY (m_mainClass->getJoystickManager())
#define JOHNNY_JOY_LIS (m_mainClass->getJoystickManager()->getListener())

#endif
