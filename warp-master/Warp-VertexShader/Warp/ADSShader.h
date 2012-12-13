#include "shader.h"

#define	BAD_GL_VALUE	((GLuint) -1)

class ADSShader : public Shader
{
public:
	ADSShader();
	virtual bool Initialize(char * vertex_shader_file, char * fragment_shader_file);

	void SetLight(glm::vec4 position, glm::vec3 la, glm::vec3 ld, glm::vec3 ls);
	void SetMaterial(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, float shininess);

	GLuint position_handle;
	GLuint la_handle;
	GLuint ld_handle;
	GLuint ls_handle;
	GLuint ka_handle;
	GLuint kd_handle;
	GLuint ks_handle;
	GLuint shininess_handle;
	GLuint normal_map_handle;
	GLuint second_normal_map_handle;
	GLuint do_normal_mapping_handle;
};