#pragma once

/* HEADER FILE FOR MESH DATA*/

#include <iostream>
#include <vector>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Math
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<camera.h>

struct GLMesh
{
	GLuint vao;
	GLuint vbo;
	GLuint vbos[2];
	GLuint nIndices;

	std::vector<float> v;
	std::vector<float> p;

	float height;
	float width;
	float radius;
	float numOfSides;
	float numOfSlices;
	float numOfStacks;

	glm::mat4 scale;
	glm::mat4 xrotation;
	glm::mat4 yrotation;
	glm::mat4 zrotation;
	glm::mat4 rotation;
	glm::mat4 translation;
	glm::mat4 model;
	glm::vec2 gUVScale;

	const char* texFilename;
	GLuint textureId;

	GLint gTextWrapMode = GL_REPEAT;

	class Mesh
	{};
};
