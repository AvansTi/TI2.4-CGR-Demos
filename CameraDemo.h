#pragma once

#include "Demo.h"
#include <glm/glm.hpp>
#include "tigl.h"
#include "Util.h"
using tigl::Vertex;

class CameraDemo : public Demo
{
public:
	CameraDemo();
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;

	std::vector<Vertex> verts;

	FpsCam camera;

};

