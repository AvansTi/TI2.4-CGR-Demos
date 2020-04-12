#pragma once

struct GLFWwindow;

class Demo
{
public:
	virtual void draw() = 0;
	virtual void update(GLFWwindow* window) = 0;
};

