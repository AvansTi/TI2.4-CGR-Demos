#pragma once

#include "Demo.h"

#include "tigl.h"
#include "Util.h"
using tigl::Vertex;

class ProjectionDemo : public Demo
{
public:
	ProjectionDemo();
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;
private:
	OrbitCam cam1;
	OrbitCam cam2;

	std::vector<Vertex> verts;

	void drawScene();

	bool perspective = true;

	float fov = 70;
	float aspect = 1;
	float near = 0.1f;
	float far = 100;

	float lr = 5;
	float ud = 5;

	
	int dragScreen = 0;



	double lastX = 0, lastY = 0;
};

