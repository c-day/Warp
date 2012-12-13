#include "ADSShader.h"


ADSShader::ADSShader()
{
	this->normal_map_handle = this->second_normal_map_handle = BAD_GL_VALUE;
	this->ka_handle = this->kd_handle = this->ks_handle = BAD_GL_VALUE;
	this->la_handle = this->ld_handle = this->ls_handle = BAD_GL_VALUE;
	this->position_handle = this->shininess_handle = BAD_GL_VALUE;
	this->do_normal_mapping_handle = BAD_GL_VALUE;
}

bool ADSShader::Initialize(char * vertex_shader_file, char * fragment_shader_file)
{
	if (!Shader::Initialize(vertex_shader_file, fragment_shader_file))
		return false;

	this->ka_handle = glGetUniformLocation(program_id, (const GLchar *) "material.ka");
	this->kd_handle = glGetUniformLocation(program_id, (const GLchar *) "material.kd");
	this->ks_handle = glGetUniformLocation(program_id, (const GLchar *) "material.ks");
	this->la_handle = glGetUniformLocation(program_id, (const GLchar *) "light.la");
	this->ld_handle = glGetUniformLocation(program_id, (const GLchar *) "light.ld");
	this->ls_handle = glGetUniformLocation(program_id, (const GLchar *) "light.ls");
	this->position_handle = glGetUniformLocation(program_id, (const GLchar *) "light.position");
	this->shininess_handle = glGetUniformLocation(program_id, (const GLchar *) "material.shininess");
	this->normal_map_handle = glGetUniformLocation(program_id, (const GLchar *) "normal_map");
	this->second_normal_map_handle = glGetUniformLocation(program_id, (const GLchar *) "second_normal_map");
	this->do_normal_mapping_handle = glGetUniformLocation(program_id, (const GLchar *) "do_normal_mapping");
	return true;
}

void ADSShader::SetLight(glm::vec4 position, glm::vec3 la, glm::vec3 ld, glm::vec3 ls)
{
	glUniform4fv(this->position_handle, 1, (const GLfloat *) &position);
	glUniform3fv(this->la_handle, 1, (const GLfloat *) &la);
	glUniform3fv(this->ld_handle, 1, (const GLfloat *) &ld);
	glUniform3fv(this->ls_handle, 1, (const GLfloat *) &ls);
}

void ADSShader::SetMaterial(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess)
{
	glUniform3fv(this->ka_handle, 1, (const GLfloat *) &ka);
	glUniform3fv(this->kd_handle, 1, (const GLfloat *) &kd);
	glUniform3fv(this->ks_handle, 1, (const GLfloat *) &ks);
	glUniform1f(this->shininess_handle, shininess);
}