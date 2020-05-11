#pragma once

#include <vector>
#include "tigl.h"

using tigl::Vertex;
struct GLFWwindow;

class Util
{
public:
	static std::vector<Vertex> buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4 &color);
	static std::vector<Vertex> buildSphere(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color);

	static std::vector<Vertex> buildDemoBlockScene(int count = 50);

	static void drawAxis();

};



class OrbitCam
{
public:
	OrbitCam(float distance) : distance(distance) {}

	glm::mat4 getMatrix();

	float distance = 5;
	float angleX = 0;
	float angleZ = 0;
};


class FpsCam
{
public:
	glm::mat4 getMatrix();
	void update(GLFWwindow*);

private:
	glm::vec3 position = glm::vec3(0, 0, 0);
	glm::vec2 rotation = glm::vec2(0, 0);

	void move(float angle, float fac);
	bool enabled = false;
};


