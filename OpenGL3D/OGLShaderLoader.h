#pragma once
class COGLShaderLoader
{
public:
	COGLShaderLoader();
	virtual ~COGLShaderLoader();
	GLuint CreateShaderFromFile(const char * filename, GLenum shader_type, bool check_errors=true);
	GLuint CreateShaderFromString(const char * source, GLenum shader_type, bool check_errors = true);
	GLuint LinkProgram(const GLuint * shaders, int shader_count, bool delete_shaders = true, bool check_errors = true);
};

extern COGLShaderLoader g_shaderLoader;

COGLShaderLoader* GetShaderLoader();