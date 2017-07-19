#pragma once
#include <glm/glm.hpp>

namespace Johnny
{
	class Camera3D;

	class Transform3D
	{
	public:
		static glm::mat4 getProjectionMatrix();

		Transform3D();
		~Transform3D();

		const glm::vec3& getTranslation() const { return m_translation; }
		void setTranslation(const glm::vec3&);
		void setTranslation(float, float, float);

		const glm::vec3& getRotation() const { return m_rotation; }
		void setRotation(const glm::vec3&);
		void setRotation(float, float, float);

		const glm::vec3& getScale() const { return m_scale; }
		void setScale(const glm::vec3&);
		void setScale(float, float, float);

		glm::mat4 getTransformation() const;

		glm::mat4 getProjectedTransformation(Camera3D* cam = nullptr) const;

		static void setProjection(float, float, float, float, float);
		static float getNearPlane() { return zNear; }
		static float getFarPlane() { return zFar; }
		static float getFOV() { return fov; }

	private:
		static float zNear;
		static float zFar;
		static float width;
		static float height;
		static float fov;

		glm::vec3 m_translation;
		glm::vec3 m_rotation;
		glm::vec3 m_scale;
	};
}
