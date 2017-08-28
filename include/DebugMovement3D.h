#pragma once
#include "../include/Actor.h"

namespace Johnny
{

	/* \brief A class which adds a small 3D DebugCameraMovement to the application
	 *        like camera moving and rotating
	 */
	class DebugMovement3D : public Actor
	{
	public:
		/* \brief Creates a new DebugMovement3D
		 * \param moveSpeed The speed with which the camera moves
		 * \param lookSpeed The speed with which the camera rotates
		 */
		DebugMovement3D(float moveSpeed = 12.0f, float lookSpeed = 1.0f);
		~DebugMovement3D();

		/* \brief The init method
		 *
		 *
		 * It is overriding the method from Actor
		 */
		bool init() override;
		/* \brief The update method
		 * 
		 *
		 * It is overriding the method from Actor
		 */
		bool update() override;
	private:
		float m_moveSpeed = 10.0f; //!< The speed with which the camera moves
		float m_lookSpeed = 0.7f; //!< The speed with which the camera rotates
	};
}