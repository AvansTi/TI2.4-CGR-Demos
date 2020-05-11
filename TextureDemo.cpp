#include <GL/glew.h>
#include "TextureDemo.h"
#include "tigl.h"
#include "imgui.h"
#include "Texture.h"
using tigl::Vertex;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TextureDemo textureDemo;

TextureDemo::TextureDemo() : Demo("Texture")
{
}

void TextureDemo::init()
{
	texture = new Texture("demo.png");
}

void TextureDemo::draw()
{
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);


	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float ratio = viewport[3] / (float)viewport[2];

	glm::mat4 projection = glm::ortho(-3.0f, 3.0f, -1 * ratio, 5 * ratio, -10.0f, 10.0f);

	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(glm::mat4(1));
	tigl::shader->setModelMatrix(glm::mat4(1));

	tigl::shader->enableColor(true);
	tigl::shader->enableLighting(false);
	tigl::shader->enableFog(false);

	glDisable(GL_DEPTH_TEST);
	tigl::shader->enableTexture(true);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, repeatMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, repeatMode);
	texture->bind();

	tigl::begin(GL_QUADS);
	tigl::addVertex(Vertex::PTC(p1, t1, c1));
	tigl::addVertex(Vertex::PTC(p2, t2, c2));
	tigl::addVertex(Vertex::PTC(p3, t3, c3));
	tigl::addVertex(Vertex::PTC(p4, t4, c4));
	tigl::end();
	tigl::shader->enableTexture(false);

	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("Texture Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::PushItemWidth(200);
		ImGui::Text("Texture Coordinats");
		ImGui::BeginGroup();
		ImGui::SliderFloat("##t1x", &t1.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##t1y", &t1.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("T1");

		ImGui::SliderFloat("##t2x", &t2.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##t2y", &t2.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("T2");

		ImGui::SliderFloat("##t3x", &t3.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##t3y", &t3.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("T3");

		ImGui::SliderFloat("##t4x", &t4.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##t4y", &t4.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("T4");

		ImGui::EndGroup();

		ImGui::Spacing();
		bool open = ImGui::BeginCombo("Repeat Mode", repeatMode == GL_REPEAT ? "GL_REPEAT" : (repeatMode == GL_MIRRORED_REPEAT ? "GL_MIRRORED_REPEAT" : "GL_CLAMP"), false);
		if (open)
		{
			bool selected = repeatMode == GL_REPEAT;
			if (ImGui::Selectable("GL_REPEAT", selected))
				repeatMode = GL_REPEAT;
			if (selected)
				ImGui::SetItemDefaultFocus();
				
			selected = repeatMode == GL_MIRRORED_REPEAT;
			if (ImGui::Selectable("GL_MIRRORED_REPEAT", selected))
				repeatMode = GL_MIRRORED_REPEAT;
			if (selected)
				ImGui::SetItemDefaultFocus();


			selected = repeatMode == GL_CLAMP;
			if (ImGui::Selectable("GL_CLAMP", selected))
				repeatMode = GL_CLAMP;
			if (selected)
				ImGui::SetItemDefaultFocus();
			ImGui::EndCombo();
		}



		ImGui::Spacing();

		ImGui::Text("Vertex Coordinats");
		ImGui::BeginGroup();
		ImGui::SliderFloat("##p1x", &p1.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##p1y", &p1.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("P1");

		ImGui::SliderFloat("##p2x", &p2.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##p2y", &p2.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("P2");

		ImGui::SliderFloat("##p3x", &p3.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##p3y", &p3.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("P3");

		ImGui::SliderFloat("##p4x", &p4.x, -5, 5);
		ImGui::SameLine();
		ImGui::SliderFloat("##p4y", &p4.y, -5, 5);
		ImGui::SameLine();
		ImGui::Text("P4");
		ImGui::EndGroup();

		ImGui::PopItemWidth();

		ImGui::Text("Colors");
		ImGui::BeginGroup();
		ImGui::ColorEdit3("Color 1", glm::value_ptr(c1));
		ImGui::ColorEdit3("Color 2", glm::value_ptr(c2));
		ImGui::ColorEdit3("Color 3", glm::value_ptr(c3));
		ImGui::ColorEdit3("Color 4", glm::value_ptr(c4));
		ImGui::EndGroup();

	}
	ImGui::End();

}

void TextureDemo::update(GLFWwindow* window)
{
}
