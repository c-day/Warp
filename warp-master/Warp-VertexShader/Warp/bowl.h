
#pragma once
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <assert.h>

#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

using namespace std;

// set up the bowl class with proper functions and initializations
class Bowl
{
public:
	bool filled;
	int count;
	vector<GLdouble> va_vertices;
	vector<GLdouble> va_colors;
	vector<GLdouble> va_normals;
	vector<GLdouble> va_texture;
	vector<GLuint> va_indices;
	vector<glm::vec3> bowl_vertices;
	GLuint pop_handle;
	Bowl();
	void bowlbot();
	void bowlmake();
	void setTex(GLuint tex);
	vector<glm::vec3> getVertArray();
};