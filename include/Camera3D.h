#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include "../include/Actor.h"
#include "../include/Matrix4.h"
#include "../include/Transform3D.h"
#include "Vector3.h"

namespace Johnny
{
	/* \brief The camera for all 3D objects
	 *        It transforms all 3D objects with m_affectedByCamera = true
	 *
	 */
	class Camera3D : public Actor, public TransformableObject3D
	{
	public:
		Camera3D();
		~Camera3D();

		/* \return A 4x4 matrix to transform a 3D object from world space to view space
		 *
		 */
		Matrix4f getViewMatrix() const;
		/* \return The direction in which the camera is looking
		 *
		 */
		const Vector3f& getLookDirection() const { return m_lookDirection; }

		/* \brief Sets the look direction
		 * \param look The direction to set the look direction to
		 */
		void setLookDirection(const Vector3f& look) { m_lookDirection = look; }
		/* \brief Sets the look direction
		 * \param x The x value of the vector to set the look direction to
		 * \param y The y value of the vector to set the look direction to
		 * \param z The z value of the vector to set the look direction to
		 */
		void setLookDirection(GLfloat x, GLfloat y, GLfloat z) { m_lookDirection = Vector3f(x, y, z); }
		/* \brief Sets the rotation of the camera
		 *
		 *
		 * It is overridong the method from TransformableObject3D
		 * \param v The vector which contains the x,y and z with which to rotate the camera (in degrees)
		 */
		void setRotation(const Vector3f& v) override { setRotation(v.x, v.y, v.z); }
		/* \brief Sets the rotation of the camera
		 *
		 *
		 * It is overriding the method from TransformableObject3D
		 * \param x The value with which to rotate the camera around the x-Axis (in degrees)
		 * \param y The value with which to rotate the camera around the y-Axis (in degrees)
		 * \param z The value with which to rotate the camera around the z-Axis (in degrees)
		 */
		void setRotation(GLfloat x, GLfloat y, GLfloat z) override;

		/* \brief Adds a vector to the position of the camera
		 * 
		 *
		 * It is overridong the method from TransformableObject3D
		 * \param pos The vector which should be added to the position of the camera
		 */
		void addPosition(const Vector3f& pos) override { addPosition(pos, false); }
		/* \brief Adds a vector to the position of the camera
		 * 
		 *
		 * It is overriding the method from TransformableObject3D
		 * \param x The x value of the vector to add to the position of the camera
		 * \param y The y value of the vector to add to the position of the camera
		 * \param z The z value of the vector to add to the position of the camera
		 */
		void addPosition(GLfloat x, GLfloat y, GLfloat z) override { addPosition(Vector3f(x, y, z)); }
		/* \brief Adds a vector to the position of the camera
		 * \param pos The vector to add to the position of the camera
		 * \param relative Defines wether the addition should be relative to the rotation
		 */
		void addPosition(const Vector3f& pos, bool relative);
		/* \brief Adds a vector to the position of the camera
		 * \param x The x value of the vector to add to the position of the camera
		 * \param y The y value of the vector to add to the position of the camera
		 */
		void addPosition(GLfloat x, GLfloat y, GLfloat z, bool);

		/* \brief The update method
		 *        It is needed for Actor
		 *
		 */
		bool update() override { return true; }
	private:
		Vector3f m_lookDirection; //!< The direction in which the camera is looking
		Vector3f m_up;			  //!< The vector which is pointing upwards from the camera

	};
}



#endif
