#pragma once
#include "Demo.h"

#include "tigl.h"
#include "Util.h"
using tigl::Vertex;


class FogDemo : public Demo
{
	std::vector<Vertex> verts;

	OrbitCam cam;

	double lastX, lastY;

	float near = 0.01f;
	float far = 100;

	glm::vec3 fogColor = glm::vec3(1,1,1);
	GLuint fogType = GL_LINEAR;
	float linNear = 5;
	float linFar = 50;

	float expDensity = 1;

public:
	FogDemo();

	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;
};

