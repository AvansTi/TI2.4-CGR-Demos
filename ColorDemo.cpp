#include <GL/glew.h>
#include "ColorDemo.h"
#include "tigl.h"
#include "imgui.h"
using tigl::Vertex;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ColorDemo colorDemo;

ColorDemo::ColorDemo() : Demo("1.4 Color")
{

}

void ColorDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float ratio = viewport[3] / (float)viewport[2];

	glm::mat4 projection = glm::ortho(-2.0f, 2.0f, -2 * ratio, 2 * ratio, -10.0f, 10.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(glm::mat4(1));
	tigl::shader->setModelMatrix(glm::mat4(1));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(false);
	tigl::shader->enableFog(false);

	glDisable(GL_DEPTH_TEST);

	tigl::begin(GL_TRIANGLES);
	tigl::addVertex(Vertex::PC(glm::vec3(-1, -0.5f, 0), c1));
	tigl::addVertex(Vertex::PC(glm::vec3(1, -0.5f, 0), c2));
	tigl::addVertex(Vertex::PC(glm::vec3(0, 0.5f, 0), c3));
	tigl::end();


	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Color Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::Text("Colors");
		ImGui::BeginGroup();
		ImGui::ColorEdit3("Color 1", glm::value_ptr(c1));
		ImGui::ColorEdit3("Color 2", glm::value_ptr(c2));
		ImGui::ColorEdit3("Color 3", glm::value_ptr(c3));
		ImGui::EndGroup();


	}
	ImGui::End();

}

void ColorDemo::update(GLFWwindow* window)
{
}
