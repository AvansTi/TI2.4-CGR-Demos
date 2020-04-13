#pragma once

#include "Demo.h"
#include <glm/glm.hpp>
#include "tigl.h"
using tigl::Vertex;

class MVPDemo : public Demo
{
public:
	MVPDemo();
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;

	std::vector<Vertex> verts;

	float fov;
	float ratio;
	float near;
	float far;

	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	glm::mat4 model;
};

