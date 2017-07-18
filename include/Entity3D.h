#pragma once
#include "Actor.h"
#include <string>

namespace Johnny
{
	class Model3D;
	class Shader;
	class Mesh3D;

	class Entity3D : public Actor
	{
	public:
		Entity3D(const std::string&);
		Entity3D(Mesh3D*);
		Entity3D(Model3D*);
		~Entity3D();

		bool init() override;
		bool update() override;
		bool render() override;
		void quit() override;

		void setModel(Model3D* m) { m_model = m; }

		Model3D* getModel() { return m_model; }
	private:
		Transform3D m_transform;
		std::string m_fileName = "";
		Model3D* m_model = nullptr;
	};
}

