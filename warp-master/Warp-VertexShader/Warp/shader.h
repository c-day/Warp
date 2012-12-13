#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <stdio.h>
#include <iostream>
#include <sstream>
#include <assert.h>


using namespace std;

class Shader
{
public:
	Shader();
	void TakeDown();
	void Use();
	bool Initialize(char * vertex_shader_file, char * fragment_shader_file);

	GLuint vertex_shader_id;
	GLuint fragment_shader_id;
	GLuint program_id;
	bool LoadShader(const char * file_name, GLuint shader_id);
	stringstream GetShaderLog(GLuint shader_id);
	GLuint size_handle;
	GLuint center_handle_red;
	GLuint center_handle_green;
	GLuint mouse_handle;
	GLuint mouse_start_handle;
	GLuint image_handle;
	GLuint vert_handle;
	GLuint norm_handle;
	GLuint mv_mat_handle;
	GLuint norm_mat_handle;
	GLuint mvp_mat_handle;
};