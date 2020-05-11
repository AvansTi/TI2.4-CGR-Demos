#define _USE_MATH_DEFINES
#include <cmath>

#include "Util.h"
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


std::vector<Vertex> Util::buildCube(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color)
{
	std::vector<Vertex> verts;
	//bottom
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, -1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, -1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, -1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, -1, 0)));

	//top
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, 1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 1, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 1, 0)));

	//left
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(1, 0, 0)));

	//right
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(-1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(-1, 0, 0)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(-1, 0, 0)));

	//back
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, -s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, -1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, -s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, -1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, -s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, -1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, -s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, -1)));

	//front
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, -s.y, s.z), color, glm::vec2(0, 0), glm::vec3(0, 0, 1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(-s.x, s.y, s.z), color, glm::vec2(1, 0), glm::vec3(0, 0, 1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, s.y, s.z), color, glm::vec2(1, 1), glm::vec3(0, 0, 1)));
	verts.push_back(Vertex::PCTN(p + glm::vec3(s.x, -s.y, s.z), color, glm::vec2(0, 1), glm::vec3(0, 0, 1)));
	return verts;
}


std::vector<Vertex> Util::buildSphere(const glm::vec3& p, const glm::vec3& s, const glm::vec4& color)
{
	std::vector<Vertex> verts;
	int stacks = 64;
	int slices = 64;


	float thetaInc = (float)M_PI / stacks;
	float phiInc = (float)(2 * M_PI / slices);

	for (float theta = -(float)M_PI_2; theta < (float)M_PI_2; theta += thetaInc)
	{
		for (float phi = 0; phi < (float)(2 * M_PI); phi += phiInc)
		{
			glm::vec3 v1(glm::cos(theta) * glm::cos(phi), glm::cos(theta) * glm::sin(phi), glm::sin(theta));
			glm::vec3 v2(glm::cos(theta + thetaInc) * glm::cos(phi + phiInc), glm::cos(theta + thetaInc) * glm::sin(phi + phiInc), glm::sin(theta + thetaInc));
			glm::vec3 v3(glm::cos(theta + thetaInc) * glm::cos(phi), glm::cos(theta + thetaInc) * glm::sin(phi), glm::sin(theta + thetaInc));
			glm::vec3 v4(glm::cos(theta) * glm::cos(phi + phiInc), glm::cos(theta) * glm::sin(phi + phiInc), glm::sin(theta));

			verts.push_back(Vertex::PCN(p + v1 * s, color, v1));
			verts.push_back(Vertex::PCN(p + v3 * s, color, v3));
			verts.push_back(Vertex::PCN(p + v2 * s, color, v2));
			verts.push_back(Vertex::PCN(p + v4 * s, color, v4));
		}
	}
	return verts;
}


std::vector<Vertex> Util::buildDemoBlockScene(int count)
{
	std::vector<Vertex> verts;
	for (int x = -count; x <= count; x += 2)
	{
		for (int y = -count; y <= count; y += 2)
		{

			auto cube = Util::buildCube(glm::vec3(x, 0, y), glm::vec3(0.5, 0.5, 0.5), glm::vec4(1, 1, 1, 1));
			verts.insert(verts.end(), cube.begin(), cube.end());
		}
	}
	return verts;
}


void Util::drawAxis()
{

	tigl::shader->enableLighting(false);
	tigl::begin(GL_LINES);
	tigl::shader->setModelMatrix(glm::mat4(1.0f));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 0, 0), glm::vec4(1, 0, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(100, 0, 0), glm::vec4(1, 0, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 0, 0), glm::vec4(0, 1, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 100, 0), glm::vec4(0, 1, 0, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 0, 0), glm::vec4(0, 0, 1, 1)));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 0, 100), glm::vec4(0, 0, 1, 1)));

	tigl::end();
}



glm::mat4 OrbitCam::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::translate(ret, glm::vec3(0, 0, -distance));
	ret = glm::rotate(ret, glm::radians(angleX), glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, glm::radians(angleZ), glm::vec3(0, 1, 0));
	return ret;
}


glm::mat4 FpsCam::getMatrix()
{
	glm::mat4 ret(1.0f);
	ret = glm::rotate(ret, rotation.x, glm::vec3(1, 0, 0));
	ret = glm::rotate(ret, rotation.y, glm::vec3(0, 1, 0));
	ret = glm::translate(ret, position);
	return ret;
}

void FpsCam::move(float angle, float fac)
{
	position.x += (float)cos(rotation.y + glm::radians(angle)) * fac;
	position.z += (float)sin(rotation.y + glm::radians(angle)) * fac;
}


void FpsCam::update(GLFWwindow* window)
{
	static int lastButton = glfwGetKey(window, GLFW_KEY_SPACE);
	if (lastButton == GLFW_RELEASE && lastButton != glfwGetKey(window, GLFW_KEY_SPACE))
	{
		enabled = !enabled;
		if(enabled)
		{ 
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
		else
		{
			if (glfwRawMouseMotionSupported())
				glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		}
	}
	lastButton = glfwGetKey(window, GLFW_KEY_SPACE);

	if (enabled)
	{
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		static double lastX = x;
		static double lastY = y;

		rotation.x -= (float)(lastY - y) / 100.0f;
		rotation.y -= (float)(lastX - x) / 100.0f;

		lastX = x;
		lastY = y;


		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			move(0, 0.05f);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			move(180, 0.05f);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			move(90, 0.05f);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			move(-90, 0.05f);



	}
}