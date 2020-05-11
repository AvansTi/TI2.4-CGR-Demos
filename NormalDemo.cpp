#include "NormalDemo.h"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"
#include <GLFW/glfw3.h>

NormalDemo normalDemo;

NormalDemo::NormalDemo() : Demo("Normal"), cam(4)
{
	cube = Util::buildDemoBlockScene(5);//Util::buildCube(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec4(1, 1, 1, 1));
	cam.angleX = 1;
	cam.angleZ = 2;
}

void NormalDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), viewport[2] / (float)viewport[3], 0.1f, 200.0f));
	tigl::shader->setViewMatrix(cam.getMatrix());
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(true);
	tigl::shader->enableTexture(false);
	tigl::shader->setLightCount(1);
	tigl::shader->setLightDirectional(0, directional);
	tigl::shader->setLightPosition(0, lightPosition);
	tigl::shader->setLightAmbient(0, glm::vec3(0.1f, 0.1f, 0.15f));
	tigl::shader->setLightDiffuse(0, glm::vec3(0.8f, 0.8f, 0.8f));
	tigl::shader->setLightSpecular(0, glm::vec3(0, 0, 0));
	tigl::shader->setShinyness(32.0f);
	tigl::shader->setFogLinear(0, 50);
	tigl::shader->enableColorMult(false);
	glEnable(GL_DEPTH_TEST);

	std::vector<Vertex> verts = cube;

	for (auto& v : verts)
	{
		glm::vec3 normal = v.normal;
		int count = 1;
		for (auto& vv : cube)
		{
			if (vv != v && v.position == vv.position)
			{
				normal += vv.normal;
				count++;
			}
		}

		normal /= count;
		normal = glm::normalize(normal);
		v.normal = glm::mix(v.normal, normal, smoothing);
	}


	tigl::drawVertices(GL_QUADS, verts);

	tigl::shader->enableLighting(false);
	tigl::shader->enableColorMult(true);
	tigl::shader->setColorMult(glm::vec4(1, 0, 0, 1));
	glLineWidth(4);
	tigl::begin(GL_LINES);
	if (perFace)
	{
		for (int i = 0; i < verts.size(); i += 4)
		{
			glm::vec3 center(0, 0, 0);
			for (int ii = i; ii < i + 4; ii++)
				center += 0.25f * verts[ii].position;

			tigl::addVertex(Vertex::P(center));
			tigl::addVertex(Vertex::P(center + 0.25f * verts[i].normal));
		}
	}
	else
	{
		for (int i = 0; i < verts.size(); i ++)
		{
			tigl::addVertex(Vertex::P(verts[i].position));
			tigl::addVertex(Vertex::P(verts[i].position + 0.25f * verts[i].normal));
		}
	}
	tigl::end();
	glLineWidth(1);




	tigl::shader->enableLighting(false);
	tigl::drawVertices(GL_QUADS, Util::buildCube(lightPosition, glm::vec3(0.25f), glm::vec4(1,1,0,1)));


	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Normal Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::BeginGroup();
		ImGui::Checkbox("Per Face", &perFace);
		ImGui::SliderFloat("Smoothing", &smoothing, 0, 1);

		ImGui::Checkbox("Directional Light", &directional);
		ImGui::PushItemWidth(100);
		ImGui::SliderFloat("##light_x", &lightPosition.x, -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##light_y", &lightPosition.y, -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##light_z", &lightPosition.z, -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::Text("Light position");
		ImGui::PopItemWidth();

		ImGui::SliderFloat("Camera Distance", &cam.distance, 0, 100);
		ImGui::EndGroup();

		ImGui::End();

	}

}

void NormalDemo::update(GLFWwindow* window)
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
