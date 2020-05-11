#pragma once

#include "Demo.h"
#include <glm/glm.hpp>

class ColorDemo : public Demo
{
	glm::vec4 c1 = glm::vec4(1, 0, 0, 1);
	glm::vec4 c2 = glm::vec4(0, 1, 0, 1);
	glm::vec4 c3 = glm::vec4(0, 0, 1, 1);


public:
	ColorDemo();

	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;
};

