#include <GL/glew.h>
#include "ModelDemo.h"
#include "tigl.h"
#include "imgui.h"
#include "Texture.h"
using tigl::Vertex;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "ObjModel.h"

ModelDemo modelDemo;

ModelDemo::ModelDemo() : Demo("2.1 Model"), cam(50.0f)
{
}

void ModelDemo::init()
{
	model = new ObjModel("models/car/honda_jazz.obj");
}

void ModelDemo::draw()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(cam.getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(false);
	tigl::shader->enableLighting(lightingEnabled);
	tigl::shader->enableColorMult(false);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightAmbient(0, lightAmbient);
	tigl::shader->setLightDiffuse(0, lightDiffuse);
	tigl::shader->setLightSpecular(0, lightSpecular);
	tigl::shader->setShinyness(shinyness);
	tigl::shader->enableFog(false);

	glEnable(GL_DEPTH_TEST);

	model->draw();

	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Model Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::Checkbox("Lighting", &lightingEnabled);

		ImGui::ColorEdit3("Ambient", glm::value_ptr(lightAmbient));
		ImGui::ColorEdit3("Diffuse", glm::value_ptr(lightDiffuse));
		ImGui::ColorEdit3("Specular", glm::value_ptr(lightSpecular));
		ImGui::SliderFloat("Shinyness", &shinyness, 0, 100);




	}
	ImGui::End();

}

void ModelDemo::update(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) && !ImGui::GetIO().WantCaptureMouse)
	{
		double dx = mouseX - lastX;
		double dy = mouseY - lastY;

		cam.angleX += (float)dy;
		cam.angleZ += (float)dx;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) && !ImGui::GetIO().WantCaptureMouse)
	{
		double dx = mouseX - lastX;
		double dy = mouseY - lastY;

		cam.distance += dy;

	}

	lastX = mouseX;
	lastY = mouseY;
}
