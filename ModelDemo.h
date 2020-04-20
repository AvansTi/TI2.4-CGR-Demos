#pragma once

#include <GL/glew.h>
#include "Demo.h"
#include <glm/glm.hpp>
#include "Util.h"
class ObjModel;

class ModelDemo : public Demo
{
	ObjModel* model;
	OrbitCam cam;
	double lastX, lastY;
public:
	ModelDemo();
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;


};

