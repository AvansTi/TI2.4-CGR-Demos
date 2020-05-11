#pragma once

#include <string>
#include <list>
struct GLFWwindow;


class Demo
{
public:
	std::string name;
	Demo(const std::string& name);

	virtual void init() {};
	virtual void draw() = 0;
	virtual void update(GLFWwindow* window) = 0;

	static std::list<Demo*> &getDemos();
};

