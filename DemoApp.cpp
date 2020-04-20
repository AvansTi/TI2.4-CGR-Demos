#include "DemoApp.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
#include <imgui.h>
#include "examples/imgui_impl_glfw.h"
#include "examples/imgui_impl_opengl3.h"

#include "ProjectionDemo.h"
#include "MVPDemo.h"
#include "ColorDemo.h"
#include "DepthDemo.h"
#include "TextureDemo.h"
#include "CameraDemo.h"
#include "ModelDemo.h"


DemoApp::DemoApp()
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
		throw "Could not initialize glwf";
	}
    glfwMakeContextCurrent(window);

    tigl::init();
	

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style 
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(nullptr);



	init();
}

void DemoApp::run()
{
	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		update();
		draw();


		{
			ImGui::SetNextWindowPos(ImVec2(0, 0));
			ImGui::Begin("Demo Selection");

			if (ImGui::Button("Projection"))
				activeDemo = projectionDemo;
			if (ImGui::Button("Model View Projection"))
				activeDemo = mvpDemo;
			if (ImGui::Button("Color"))
				activeDemo = colorDemo;
			if (ImGui::Button("Depth"))
				activeDemo = depthDemo;
			if (ImGui::Button("Texture"))
				activeDemo = textureDemo;
			if (ImGui::Button("Camera"))
				activeDemo = cameraDemo;
			if (ImGui::Button("Model"))
				activeDemo = modelDemo;

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}


void DemoApp::init()
{
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if(key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(window, true);
	});


	projectionDemo = new ProjectionDemo();
	mvpDemo = new MVPDemo();
	colorDemo = new ColorDemo();
	depthDemo = new DepthDemo();
	textureDemo = new TextureDemo();
	cameraDemo = new CameraDemo();
	modelDemo = new ModelDemo();


	activeDemo = projectionDemo;

}

void DemoApp::draw()
{
	glm::ivec2 windowSize;
	glfwGetWindowSize(window, &windowSize.x, &windowSize.y);
	glViewport(0, 0, windowSize.x, windowSize.y);
	glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	activeDemo->draw();


}

void DemoApp::update()
{
	activeDemo->update(window);
}
