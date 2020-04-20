#pragma once

#include <GL/glew.h>
#include "Demo.h"
#include <glm/glm.hpp>

class Texture;

class TextureDemo : public Demo
{
	//TODO: just make a vector of 4 verts
	glm::vec4 c1 = glm::vec4(1, 1, 1, 1);
	glm::vec4 c2 = glm::vec4(1, 1, 1, 1);
	glm::vec4 c3 = glm::vec4(1, 1, 1, 1);
	glm::vec4 c4 = glm::vec4(1, 1, 1, 1);

	glm::vec2 t1 = glm::vec2(0, 0);
	glm::vec2 t2 = glm::vec2(1, 0);
	glm::vec2 t3 = glm::vec2(1, 1);
	glm::vec2 t4 = glm::vec2(0, 1);

	glm::vec3 p1 = glm::vec3(0, 0, 0);
	glm::vec3 p2 = glm::vec3(1, 0, 0);
	glm::vec3 p3 = glm::vec3(1, 1, 0);
	glm::vec3 p4 = glm::vec3(0, 1, 0);
	Texture* texture;

	GLuint repeatMode = GL_REPEAT;

public:
	TextureDemo();
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;


};

