#pragma once

#include "Demo.h"
#include <glm/glm.hpp>
#include "Util.h"
#include "tigl.h"
using tigl::Vertex;

class NormalDemo : public Demo
{
	OrbitCam cam;
	double lastX, lastY;
	std::vector<Vertex> cube;

	bool perFace = true;
	float smoothing = false;
	


	glm::vec3 lightPosition = glm::vec3(2.0f, 2.0f, 2.0f);
	bool directional = false;
public:
	NormalDemo();
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;

};