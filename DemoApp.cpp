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
#include "NormalDemo.h"

#if defined(WIN32) || defined(_WIN64)
//void GLAPIENTRY onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);
void GLAPIENTRY onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
#else
void onDebug(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, GLvoid* userParam)
#endif
{

	if (type == 33361) //VBO setdata
		return;
	if (type == 33357) //deprication warning
		return;
	printf("%s\n", message);
}


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

	glfwSwapInterval(0);
	if (GLEW_ARB_debug_output)
	{
		glDebugMessageCallback(&onDebug, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
		glEnable(GL_DEBUG_OUTPUT);
	}


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
			ImGui::SetNextWindowSize(ImVec2(0, 400));
			ImGui::Begin("Demo Selection");
			for (auto demo : demos)
			{
				if (ImGui::Button(demo->name.c_str()))
					activeDemo = demo;
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			
			static bool vsync = true;
			if (ImGui::Checkbox("Use vsync", &vsync))
			{
				glfwSwapInterval(vsync ? 1 : 0);
			}
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

GLFWkeyfun oldCallback;
void DemoApp::init()
{
	oldCallback = glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
			if (key == GLFW_KEY_ESCAPE)
				glfwSetWindowShouldClose(window, true);
			else
				oldCallback(window, key, scancode, action, mods);
	});


	demos = Demo::getDemos();
	for (auto demo : demos)
		demo->init();
	activeDemo = demos.front();

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
