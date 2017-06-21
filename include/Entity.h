#pragma once
#include "Actor.h"
#include <string>

class Model;
class Shader;
class Mesh;

class Entity :
	public SDL::Actor
{
public:
	Entity(const std::string&);
	Entity(Mesh*);
	Entity(Model*);
	~Entity();

	bool init() override;
	bool update() override;
	bool render() override;
	void quit() override;

	void setModel(Model* m) { m_model = m; }

	Model* getModel() { return m_model; }
private:
	std::string m_fileName = "";
	Model* m_model = nullptr;
};

