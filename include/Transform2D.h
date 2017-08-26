#pragma once
#include "Vector2.h"
#include "Matrix3.h"
#include <GL/glew.h>
#include <vector>

namespace Johnny
{
	class Camera2D;

	class Transform2D
	{
	public:
		Transform2D();
		Transform2D(const Vector2f&, const GLfloat&, const Vector2f&);
		~Transform2D();

		const Vector2f& getTranslation() const { return m_translation; }
		const GLfloat& getRotation() const { return m_rotation; }
		const Vector2f& getScale() const { return m_scale; }

		void setTranslation(const Vector2f& translation) { m_translation = translation; }
		void setRotation(const GLfloat& rotation) { m_rotation = rotation; }
		void setScale(const Vector2f& scale) { m_scale = scale; }

		void setTranslation(const GLfloat& transX,const GLfloat& transY) { m_translation = Vector2f(transX,transY); }
		void setScale(const GLfloat& scaleX,const GLfloat& scaleY) { m_scale = Vector2f(scaleX,scaleY); }

		Matrix3f getTransformation() const;
		Matrix3f getProjectedTransformation(const Camera2D*) const;
	private:
		Vector2f m_translation;
		GLfloat m_rotation;
		Vector2f m_scale;
	};

	class TransformableObject2D
	{
	public:
		static const Vector2f& getCenter();
		static bool getYAxisFlipped();
		static bool getXAxisFlipped();
		static const Vector2f& getViewportSize();

		static void setCenter(const Vector2f&);
		static void setYAxisFlipped(bool);
		static void setXAxisFlipped(bool);
		static void setViewportSize(const Vector2f&);

		static Vector2f toCoords(const Vector2f&, const Vector2f& viewport = Vector2f(-1.0f,-1.0f));
		static Vector2f toCoords(const Vector2f&, bool,bool);
		static Vector2f fromCoords(const Vector2f&, const Vector2f& viewport = Vector2f(-1.0f,-1.0f));
		static Vector2f fromCoords(const Vector2f&, bool, bool);
        
        static bool centerSet;

		TransformableObject2D();
		virtual ~TransformableObject2D();

		virtual void setPosition(const Vector2f&);
		virtual void setPosition(const GLfloat&, const GLfloat&);
		virtual void setRotation(const GLfloat&);
		virtual void setScale(const Vector2f&);
		virtual void setScale(const GLfloat&, const GLfloat&);

		virtual void addPosition(const Vector2f&);
		virtual void addPosition(const GLfloat&, const GLfloat&);
		virtual void addRotation(const GLfloat& x) { setRotation(m_transform.getRotation() + x); }
		virtual void addScale(const Vector2f&);
		virtual void addScale(const GLfloat&, const GLfloat&);
		 
		virtual Vector2f getPosition() const;
		virtual const GLfloat& getRotation() const { return m_transform.getRotation(); }
		virtual const Vector2f& getScale() const { return m_transform.getScale(); }
		
		Transform2D& getTransform() { return m_transform; }

	protected:
		virtual void setSize(const Vector2f& v);
		virtual void setSize(GLfloat x, GLfloat y) { setSize(Vector2f(x, y)); }

		virtual const Vector2f& getSize() const { return m_size; }

		Transform2D m_transform;
		Vector2f m_size;
		bool m_affectedByCenter = true;
	private:
		static Vector2f center;
		static Vector2f viewportSize;
		static bool yAxisFlipped;
		static bool xAxisFlipped;
		static std::vector<TransformableObject2D*> objects;
	};
}