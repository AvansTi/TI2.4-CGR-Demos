#pragma once

#include <vector>
#include "tigl.h"

using tigl::Vertex;

class Util
{
public:
	static std::vector<Vertex> buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4 &color);
	static std::vector<Vertex> buildSphere(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color);

	static std::vector<Vertex> buildDemoBlockScene();

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
