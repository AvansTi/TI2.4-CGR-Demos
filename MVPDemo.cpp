#include "MVPDemo.h"
#include "Util.h"
#include <glm/gtc/matrix_transform.hpp>
#include "imgui.h"

MVPDemo::MVPDemo()
{
	verts = Util::buildDemoBlockScene();

	ratio = 1;
	fov = 70;
	near = 0.01;
	far = 100;

	eye = glm::vec3(0, 5, 5);
	center = glm::vec3(0, 0, 0);
	up = glm::vec3(0, 1, 0);

	model = glm::mat4(1);
}

void MVPDemo::draw()
{
	glm::mat4 projection = glm::perspective(glm::radians(fov), ratio, near, far);
	glm::mat4 view = glm::lookAt(eye, center, up);
	
	tigl::shader->setProjectionMatrix(projection);
	tigl::shader->setViewMatrix(view);
	tigl::shader->setModelMatrix(model);

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



	{
		ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 500, 0));
		ImGui::SetNextWindowSize(ImVec2(500, 0));

		ImGui::Begin("MVP Demo");
		ImGui::SetWindowFontScale(1.5f);

		ImGui::Text("Projection");
		ImGui::BeginGroup();
		ImGui::SliderFloat("Field of View", &fov, 0.0f, 180.0f);
		ImGui::SliderFloat("Aspect Ratio", &ratio, 0.0f, 2.0f);
		ImGui::SliderFloat("Near plane", &near, 0.0f, 100.0f);
		ImGui::SliderFloat("Far plane", &far, 0.0f, 100.0f);
		ImGui::EndGroup();

		ImGui::Text("View (lookat)");
		ImGui::BeginGroup();
		ImGui::PushItemWidth(100);
		ImGui::SliderFloat("##eye_x", &eye.x, -50.0f, 50.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##eye_y", &eye.y, -50.0f, 50.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##eye_z", &eye.z, -50.0f, 50.0f);
		ImGui::SameLine();
		ImGui::Text("Eye");

		ImGui::SliderFloat("##center_x", &center.x, -50.0f, 50.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##center_y", &center.y, -50.0f, 50.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##center_z", &center.z, -50.0f, 50.0f);
		ImGui::SameLine();
		ImGui::Text("Center");

		ImGui::SliderFloat("##up_x", &up.x, -1.0f, 1.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##upy", &up.y, -1.0f, 1.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##upz", &up.z, -1.0f, 1.0f);
		ImGui::SameLine();
		ImGui::Text("Up");
		ImGui::PopItemWidth();
		ImGui::EndGroup();

		ImGui::Text("Model");
		ImGui::BeginGroup();
		ImGui::PushItemWidth(100);
		ImGui::SliderFloat("##model_11", &model[0][0], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_12", &model[1][0], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_13", &model[2][0], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_14", &model[3][0], -10.0f, 10.0f);

		ImGui::SliderFloat("##model_21", &model[0][1], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_22", &model[1][1], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_23", &model[2][1], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_24", &model[3][1], -10.0f, 10.0f);

		ImGui::SliderFloat("##model_31", &model[0][2], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_32", &model[1][2], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_33", &model[2][2], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_34", &model[3][2], -10.0f, 10.0f);

		ImGui::SliderFloat("##model_41", &model[0][3], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_42", &model[1][3], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_43", &model[2][3], -10.0f, 10.0f);
		ImGui::SameLine();
		ImGui::SliderFloat("##model_44", &model[3][3], -10.0f, 10.0f);

		ImGui::PopItemWidth();
		ImGui::EndGroup();

	}
	ImGui::End();




}

void MVPDemo::update(GLFWwindow* window)
{

}
