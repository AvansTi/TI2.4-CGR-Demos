#include "FogDemo.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tigl.h"
#include "Util.h"
#include <GLFW/glfw3.h>

FogDemo fogDemo;

FogDemo::FogDemo() : Demo("Fog"), cam(20)
{
	verts = Util::buildDemoBlockScene();

}

void FogDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), viewport[2] / (float)viewport[3], near, far));
	tigl::shader->setViewMatrix(cam.getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(true);
	tigl::shader->enableColorMult(false);
	tigl::shader->enableTexture(false);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, true);
	tigl::shader->setLightPosition(0, glm::vec3(10, 10, 10));
	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
	tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
	tigl::shader->setShinyness(32.0f);
	if (fogType == GL_LINEAR)
		tigl::shader->setFogLinear(linNear, linFar);
	else if (fogType == GL_EXP)
		tigl::shader->setFogExp(expDensity);
	else if (fogType == GL_EXP2)
		tigl::shader->setFogExp2(expDensity);
	tigl::shader->enableColorMult(false);
	tigl::shader->enableFog(true);
	tigl::shader->setFogColor(fogColor);

	glEnable(GL_DEPTH_TEST);


	tigl::drawVertices(GL_QUADS, verts);



	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Fog Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::BeginGroup();
		ImGui::SliderFloat("Camera Distance", &cam.distance, 0, 100);
		ImGui::Spacing();

		ImGui::Text("Perspective near/far");
		ImGui::SliderFloat("Near", &near, 0, 100);
		ImGui::SliderFloat("Far", &far, 0, 100);

		ImGui::Spacing();

		bool open = ImGui::BeginCombo("Fog Type", fogType == GL_LINEAR ? "GL_LINEAR" : (fogType == GL_EXP ? "GL_EXP" : "GL_EXP2"), false);
		if (open)
		{
			bool selected = fogType == GL_LINEAR;
			if (ImGui::Selectable("GL_LINEAR", selected))
				fogType = GL_LINEAR;
			if (selected)
				ImGui::SetItemDefaultFocus();

			selected = fogType == GL_EXP;
			if (ImGui::Selectable("GL_EXP", selected))
				fogType = GL_EXP;
			if (selected)
				ImGui::SetItemDefaultFocus();


			selected = fogType == GL_EXP2;
			if (ImGui::Selectable("GL_EXP2", selected))
				fogType = GL_EXP2;
			if (selected)
				ImGui::SetItemDefaultFocus();
			ImGui::EndCombo();
		}

		if (fogType == GL_LINEAR)
		{
			ImGui::SliderFloat("Near##fog", &linNear, 0, 100);
			ImGui::SliderFloat("Far##fog", &linFar, 0, 100);
		}
		else
		{
			ImGui::SliderFloat("Density", &expDensity, 0, 2);
		}

		ImGui::ColorEdit3("Fog Color", glm::value_ptr(fogColor));



		ImGui::EndGroup();

		ImGui::End();

	}

}

void FogDemo::update(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) && !ImGui::GetIO().WantCaptureMouse)
	{
		float dx = (float)(mouseX - lastX);
		float dy = (float)(mouseY - lastY);

		cam.angleX += dy;
		cam.angleZ += dx;
	}


	lastX = mouseX;
	lastY = mouseY;
}
