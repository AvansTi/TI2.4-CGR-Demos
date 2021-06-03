#include "HeightMapDemo.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "Util.h"
#include <GLFW/glfw3.h>
#define STB_PERLIN_IMPLEMENTATION
#include "stb_noise.h"

HeightMapDemo heightMapDemo;

HeightMapDemo::HeightMapDemo() : Demo("3.1 HeightMap"), cam(20)
{

}

void HeightMapDemo::init()
{
	std::vector<std::vector<float>> heights(1000, std::vector<float>(1000, 0));

	float sx = 2.0f / heights.size();
	float sy = 2.0f / heights[0].size();

	for (int x = 0; x < heights.size(); x++)
	{
		for (int y = 0; y < heights[x].size(); y++)
		{
			heights[x][y] = -50 + 100 * stb_perlin_turbulence_noise3(x * sx, y * sy, 0, 2.0f, 0.5f, 8, 256, 256, 256);
		}
	}
	std::vector<std::vector<glm::vec3>> faceNormals(999, std::vector<glm::vec3>(999, glm::vec3(0)));
	for (int x = 0; x < heights.size() - 1; x++)
	{
		for (int y = 0; y < heights[x].size() - 1; y++)
		{
			glm::vec3 p1(x, heights[x][y], y);
			glm::vec3 p2(x+1, heights[x+1][y], y);
			glm::vec3 p3(x, heights[x][y+1], y+1);
			faceNormals[x][y] = glm::normalize(glm::cross(p1-p2, p1-p3));
		}
	}
	std::vector<std::vector<glm::vec3>> normals(1000, std::vector<glm::vec3>(1000, glm::vec3(0)));
	for (int x = 0; x < heights.size()-1; x++)
	{
		for (int y = 0; y < heights[x].size()-1; y++)
		{
			glm::vec3 normal = faceNormals[x][y];
			if (x > 1)
			{
				normal += faceNormals[x - 1][y];
				if (y > 1)
					normal += faceNormals[x - 1][y - 1];
			}
			else if (y > 1)
				normal += faceNormals[x][y - 1];
			normals[x][y] = glm::normalize(normal);
		}
	}

	for (int x = 0; x < heights.size() - 1; x++)
	{
		for (int y = 0; y < heights[x].size() - 1; y++)
		{
			glm::vec4 color = glm::vec4((rand() / (float)RAND_MAX), (rand() / (float)RAND_MAX), (rand() / (float)RAND_MAX), 1.0f);
			verts.push_back(Vertex::PN(glm::vec3(x,		heights[x][y],			y), normals[x][y]));
			verts.push_back(Vertex::PN(glm::vec3(x + 1, heights[x + 1][y],		y), normals[x+1][y]));
			verts.push_back(Vertex::PN(glm::vec3(x + 1, heights[x + 1][y + 1],	y + 1), normals[x+1][y+1]));
			verts.push_back(Vertex::PN(glm::vec3(x,		heights[x][y + 1],		y + 1), normals[x][y+1]));
		}
	}


	vbo = tigl::createVbo(verts);
}

void HeightMapDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), viewport[2] / (float)viewport[3], 0.1f, 500.0f));
	tigl::shader->setViewMatrix(cam.getMatrix() * glm::translate(glm::mat4(1.0f), glm::vec3(-500,0,-500)));
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
	tigl::shader->setFogLinear(0, 500);
	tigl::shader->enableColorMult(false);
	
	tigl::shader->enableFog(true);

	glEnable(GL_DEPTH_TEST);
	if (useVbo)
		tigl::drawVertices(GL_QUADS, vbo);
	else
		tigl::drawVertices(GL_QUADS, verts);


	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Heightmap Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::BeginGroup();
		ImGui::SliderFloat("Camera Distance", &cam.distance, 0, 100);
		ImGui::SliderFloat("Autorotate", &autorotation, 0, 1);
		ImGui::Checkbox("Use VBO", &useVbo);
		ImGui::EndGroup();

		ImGui::End();

	}

}

void HeightMapDemo::update(GLFWwindow* window)
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
	else
	{
		cam.angleZ += autorotation;
	}


	lastX = mouseX;
	lastY = mouseY;
}
