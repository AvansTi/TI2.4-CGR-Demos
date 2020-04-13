#pragma once
#include "Demo.h"

#include "tigl.h"
#include "Util.h"
using tigl::Vertex;


class DepthDemo : public Demo
{
	std::vector<Vertex> verts;
	bool depthEnabled = false;

	OrbitCam cam;

	double lastX, lastY;

public:
	DepthDemo();

	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;
};

