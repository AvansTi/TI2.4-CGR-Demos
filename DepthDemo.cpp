#include "DepthDemo.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "Util.h"
#include <GLFW/glfw3.h>


DepthDemo::DepthDemo() : cam(20)
{
	verts = Util::buildDemoBlockScene();

}

void DepthDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), viewport[2] / (float)viewport[3], 0.1f, 200.0f));
	tigl::shader->setViewMatrix(cam.getMatrix());
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

	if(depthEnabled)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);


	tigl::drawVertices(GL_QUADS, verts);



	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Depth Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::BeginGroup();
		ImGui::Checkbox("Depth enabled", &depthEnabled);
		ImGui::SliderFloat("Camera Distance", &cam.distance, 0, 100);
		ImGui::EndGroup();

		ImGui::End();

	}

}

void DepthDemo::update(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) && !ImGui::GetIO().WantCaptureMouse)
	{
		double dx = mouseX - lastX;
		double dy = mouseY - lastY;

		cam.angleX += dy;
		cam.angleZ += dx;
	}


	lastX = mouseX;
	lastY = mouseY;
}
