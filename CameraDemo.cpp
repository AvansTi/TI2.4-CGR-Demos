#include "CameraDemo.h"
#include "Util.h"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"

CameraDemo cameraDemo;

CameraDemo::CameraDemo() : Demo("1.3 Camera")
{
	verts = Util::buildDemoBlockScene();
}

void CameraDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 100.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(camera.getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(true);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::vec3(10, 10, 10));
	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
	tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
	tigl::shader->setShinyness(32.0f);
	tigl::shader->setFogLinear(0, 50);
	tigl::shader->enableColorMult(false);
	tigl::shader->enableFog(true);

	glEnable(GL_DEPTH_TEST);

	tigl::drawVertices(GL_QUADS, verts);





}

void CameraDemo::update(GLFWwindow* window)
{
	camera.update(window);
}
