#pragma once

#include "Demo.h"
#include <glm/glm.hpp>
#include "Util.h"
#include "tigl.h"
using tigl::Vertex;
#include "stb_truetype.h"

class FontDemo : public Demo
{
public:
	stbtt_bakedchar cdata[96];
	GLuint texId;

	std::string text = "Hello world";

	FontDemo();
	virtual void init() override;
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;

};