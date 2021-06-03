#pragma once

#include <GL/glew.h>
#include "Demo.h"
#include <glm/glm.hpp>
#include "Util.h"
class ObjModel;

class ModelDemo : public Demo
{
	ObjModel* model;
	OrbitCam cam;
	double lastX, lastY;

	bool lightingEnabled = false;
	glm::vec3 lightPos = glm::vec3(0, 1, 0);
	bool directional = false;
	glm::vec3 lightAmbient = glm::vec3(0.5f);
	glm::vec3 lightDiffuse = glm::vec3(0.5f);
	glm::vec3 lightSpecular = glm::vec3(0.5f);
	float shinyness = 1;

public:
	ModelDemo();
	virtual void init() override;
	virtual void draw() override;
	virtual void update(GLFWwindow* window) override;


};

