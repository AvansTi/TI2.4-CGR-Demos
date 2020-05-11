#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <list>

#include "tigl.h"
using tigl::Vertex;
class Demo;

class DemoApp
{
public:
	DemoApp();
	void run();
private:
	GLFWwindow* window;
	void init();
	void update();
	void draw();


	Demo* activeDemo;
	std::list<Demo*> demos;

};

