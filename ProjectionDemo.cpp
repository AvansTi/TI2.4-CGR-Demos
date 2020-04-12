#include <GL/glew.h>
#include "ProjectionDemo.h"
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "tigl.h"
#include "Util.h"
#include <GLFW/glfw3.h>

ProjectionDemo::ProjectionDemo() : cam1(25.0f), cam2(10.0f)
{
	for (int x = -50; x <= 50; x+=2)
	{
		for (int y = -50; y <= 50; y+=2)
		{

			auto cube = Util::buildCube(glm::vec3(x, 0, y), glm::vec3(0.5, 0.5, 0.5), glm::vec4(1, 1, 1, 1));
			verts.insert(verts.end(), cube.begin(), cube.end());
		}
	}

	cam1.angleX = 45;
	cam1.angleZ = 45;

	cam2.angleX = 45;
	cam2.angleZ = -45;

}


void ProjectionDemo::draw()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);

	
	glm::mat4 projection = glm::perspective(glm::radians(fov), aspect, near, far);
	if (!perspective)
		projection = glm::ortho(-lr , lr, -ud, ud, near, far);
	glm::mat4 view = cam2.getMatrix();


	glViewport(0, 0, viewport[2]/2, viewport[3]);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	tigl::shader->setProjectionMatrix(glm::perspective(glm::radians(70.0f), (viewport[2] / 2.0f) / viewport[3], 0.1f, 200.0f));
	tigl::shader->setViewMatrix(cam1.getMatrix());
	drawScene();

	glm::mat4 pv = glm::inverse(view) * glm::inverse(projection);

	tigl::shader->setColorMult(glm::vec4(0, 0, 0, 1));
	tigl::shader->enableLighting(false);
	tigl::shader->enableColorMult(true);
	tigl::shader->enableFog(false);

	auto calc = [&](const glm::vec4& p)
	{
		auto pp = pv * p;
		return glm::vec3(pp) / pp.w;
	};

	glLineWidth(10);
	tigl::begin(GL_LINES);
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1, -1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1, -1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1, -1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1,  1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1,  1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1,  1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1,  1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1, -1, -1, 1))));

	tigl::addVertex(Vertex::P(calc(glm::vec4( 1, -1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1, -1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1, -1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1,  1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1,  1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1,  1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1,  1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1, -1,  1, 1))));

	tigl::addVertex(Vertex::P(calc(glm::vec4( 1, -1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1, -1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1, -1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1, -1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1,  1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4(-1,  1,  1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1,  1, -1, 1))));
	tigl::addVertex(Vertex::P(calc(glm::vec4( 1,  1,  1, 1))));

	tigl::end();






	glViewport(viewport[2] / 2, 0, viewport[2] / 2, viewport[3]);
	glClearColor(1, 1, 1, 1);
	glClear(GL_DEPTH_BUFFER_BIT);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(view);
	drawScene();


	glViewport(0, 0, viewport[2], viewport[3]);

	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 400, 0));
		ImGui::SetNextWindowSize(ImVec2(400, 0));

		ImGui::Begin("Projection Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::Checkbox("Perspective", &perspective);
		if (perspective)
		{
			ImGui::Text("Perspective");
			ImGui::BeginGroup();
			ImGui::SliderFloat("Field of View", &fov, 0.0f, 180.0f);
			ImGui::SliderFloat("Aspect Ratio", &aspect, 0.0f, 2.0f);
			ImGui::SliderFloat("Near plane", &near, 0.0f, 100.0f);
			ImGui::SliderFloat("Far plane", &far, 0.0f, 100.0f);
			ImGui::EndGroup();
		}
		else
		{
			ImGui::Text("Ortho");
			ImGui::BeginGroup();
			ImGui::SliderFloat("Left/Right", &lr, 0.0f, 100.0f);
			ImGui::SliderFloat("Up/Down", &ud, 0.0f, 100.0f);
			ImGui::SliderFloat("Near plane", &near, 0.0f, 100.0f);
			ImGui::SliderFloat("Far plane", &far, 0.0f, 100.0f);
			ImGui::EndGroup();
		}

		ImGui::Text("Cameras");
		ImGui::BeginGroup();
		ImGui::SliderFloat("Camera 1 Distance", &cam1.distance, 0.0f, 100.0f);
		ImGui::SliderFloat("Camera 2 Distance", &cam2.distance, 0.0f, 100.0f);
		ImGui::EndGroup();



		ImGui::End();
	}
}

void ProjectionDemo::drawScene()
{

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
	tigl::shader->setModelMatrix(glm::mat4(1.0f));

	glEnable(GL_DEPTH_TEST);


	tigl::drawVertices(GL_QUADS, verts);
	glDisable(GL_DEPTH_TEST);
	Util::drawAxis();
}


void ProjectionDemo::update(GLFWwindow* window)
{
	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) && !ImGui::GetIO().WantCaptureMouse)
	{
		if (dragScreen == 0)
		{
			int x, y;
			glfwGetWindowSize(window, &x, &y);
			if (mouseX < x / 2)
				dragScreen = 1;
			else
				dragScreen = 2;
		}
		double dx = mouseX - lastX;
		double dy = mouseY - lastY;

		if (dragScreen == 1)
		{
			cam1.angleX += dy;
			cam1.angleZ += dx;
		}
		else
		{
			cam2.angleX += dy;
			cam2.angleZ += dx;
		}
	}
	else
		dragScreen = 0;


	lastX = mouseX;
	lastY = mouseY;
}
