#pragma once
#include "Demo.h"

#include "tigl.h"
#include "Util.h"
using tigl::Vertex;


class HeightMapDemo : public Demo
{
	std::vector<Vertex> verts;
	tigl::VBO* vbo;

	OrbitCam cam;

	double lastX, lastY;

	bool useVbo = true;

public:
	HeightMapDemo();

	virtual void init() override;
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;
};

