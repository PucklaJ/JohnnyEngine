#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace Johnny
{
	class Camera3D;

	/*! \brief A class which generates a 3D transformation matrix
	 *
	 */
	class Transform3D
	{
	public:
		/*! \return A perspective projection matrix
		 *
		 */
		static Matrix4f getProjectionMatrix();

		Transform3D();
		~Transform3D();

		/*! \return The translation of the Transform3D
		 *
		 */
		const Vector3f& getTranslation() const { return m_translation; }
		/*! \brief Sets the translation of the Transform3D
		 *  \param v The translation to set
		 */
		void setTranslation(const Vector3f& v);
		/*! \brief Sets the translation of the Transform3D
		 *  \param x The x value of the translation vector to set
		 *  \param y The y value of the translation vector to set
		 *  \param z The z value of the translation vector to set
		 */
		void setTranslation(GLfloat x, GLfloat y, GLfloat z);

		/*! \return The rotation vector of the Transform3D with the rotations on the x-, y- and z-Axis in degrees
		 *
		 */
		const Vector3f& getRotation() const { return m_rotation; }
		/*! \brief Sets the rotation of the Transform3D
		 *  \param v The rotation vector to set with the rotation on the x-,y- and z-Axis in degrees
		 */
		void setRotation(const Vector3f& v);
		/*! \brief Sets the rotation of the Transform3D
		 *  \param x The rotation on the x-Axis
		 *  \param y The rotation on the y-Axis
		 *  \param z The rotation on the z-Axis
		 */
		void setRotation(GLfloat x, GLfloat y, GLfloat z);

		/*! \return The scale of the Transform3D in the x-,y- and z-Axis
		 *
		 */
		const Vector3f& getScale() const { return m_scale; }
		/*! \brief Sets the scale of the Transform3D
		 *  \param v The scale vector to set
		 */
		void setScale(const Vector3f& v);
		/*! \brief Sets the scale of the Transform3D
		 *  \param x The scale in the x-Axis
		 *  \param y The scale in the y-Axis
		 *  \param z The scale in the z-Axis
		 */
		void setScale(GLfloat x, GLfloat y, GLfloat z);

		/*! \return A modelworld transformation matrix
		 *
		 */
		Matrix4f getTransformation() const;

		/*! \param cam The Camera3D to use for the view
		 *  \return A modelworldviewprojection transformation matrix
		 */
		Matrix4f getProjectedTransformation(const Camera3D* cam = nullptr) const;

		/*! \brief Sets the values needed for the perspective projection
		 *  \param fov The field of view of the perspective projection
		 *  \param width The width of the viewport
		 *  \param height The height of the viewport
		 *  \param zNear The near plane for the perspective projection
		 *  \param zFar The far plane of the 
		 */
		static void setProjection(GLfloat fov, GLfloat width, GLfloat height, GLfloat zNear, GLfloat zFar);
		/*! \return The near plane of the perspective projection 
		 *
		 */
		static GLfloat getNearPlane() { return zNear; }
		/*! \return The far plane of the perspective projection
		 *
		 */
		static GLfloat getFarPlane() { return zFar; }
		/*! \return The field of view of the perspective projection
		 *
		 */
		static GLfloat getFOV() { return fov; }

	private:
		static GLfloat zNear;   //!< The near plane of the perspective projection
		static GLfloat zFar;    //!< The far plane of the prespective projection
		static GLfloat width;   //!< The width of the viewport for the perspective projection
		static GLfloat height;  //!< The height of the viewport for the perspective projection
		static GLfloat fov;     //!< The field of the view of the perspective projection

		Vector3f m_translation; //!< The translation of the Transform3D
		Vector3f m_rotation;    //!< The rotation on the x-,y- and z-Axis in degrees
		Vector3f m_scale;		//!< The scale of the Transform3D
	};

	/*! \brief A class which represents a object with a Transform3D
	 *
	 */
	class TransformableObject3D
	{
	public:
		TransformableObject3D();
		virtual ~TransformableObject3D();

		/*! \return The position of the object
		 *
		 */
		virtual const Vector3f& getPosition() const { return m_transform.getTranslation(); }
		/*! \return The rotation of the object on the x-,y- and z-Axis
		 *
		 */
		virtual const Vector3f& getRotation() const { return m_transform.getRotation(); }
		/*! \return The scale of the object
		 *
		 */
		virtual const Vector3f& getScale() const { return m_transform.getScale(); }
		
		/*! \brief Sets the position of the object
		 *  \param pos The position to set
		 */
		virtual void setPosition(const Vector3f& pos) { m_transform.setTranslation(pos); }
		/*! \brief Sets the position of the object
		 *  \param x The x position of the object
		 *  \param y The y position of the object
		 *  \param z The z poisition of the object
		 */
		virtual void setPosition(GLfloat x, GLfloat y, GLfloat z) { m_transform.setTranslation(x, y, z); }
		/*! \brief Sets the rotation of the object
		 *  \param rot The rotation of the object on the x-,y- and z-Axis
		 */
		virtual void setRotation(const Vector3f& rot) { m_transform.setRotation(rot); }
		/*! \brief Sets the rotation of the object
		 *  \param x The rotation on the x-Axis
		 *  \param y The rotation on the y-Axis
		 *  \param z The rotation on the z-Axis
		 */
		virtual void setRotation(GLfloat x, GLfloat y, GLfloat z);
		
		/*! \brief Adds a vector to the position
		 *  \param pos The vector to add
		 */
		virtual void addPosition(const Vector3f& pos);
		/*! \brief Adds a vector to the position
		 *  \param x The x value of the vector to add
		 *  \param y The y value of the vector to add
		 *  \param z The z value of the vector to add
		 */
		virtual void addPosition(GLfloat x, GLfloat y, GLfloat z);
		/*! \brief Adds a rotation to the object
		 *  \param v THe rotation vector to add
		 */
		virtual void addRotation(const Vector3f& v) { addRotation(v.x, v.y, v.z); }
		/*! \brief Adds a rotation to the object
		 *  \param x The rotation on the x-Axis to add
		 *  \param y The rotation on the y-Axis to add
		 *  \param z The rotation on the z-Axis to add
		 */
		virtual void addRotation(GLfloat x, GLfloat y, GLfloat z) { setRotation(m_transform.getRotation().x + x, m_transform.getRotation().y + y, m_transform.getRotation().z + z); }

		/*! \return A modelworld transformation matrix
		 *
		 */
		Matrix4f getTransformation() const;
		/*! \param cam The Camera3D to use for the view
		 *  \return A modelworldviewprojection matrix
		 */
		Matrix4f getProjectedTransformation(const Camera3D* cam = nullptr) const;

		/*! \return The Transform3D of the object
		 *
		 */
		Transform3D& getTransform() { return m_transform; }

	protected:
		Transform3D m_transform; //!< The Transform3D of the object
	};
}
