#include "stdafx.h"
#include "OGLObject.h"


OGLObject::OGLObject():m_gluProgram(0),m_gluVAO(0)
{
}


OGLObject::~OGLObject()
{
	Destory();
}

bool OGLObject::SetUp()
{
	static const char * vs_source[] =
	{
		"#version 420 core                                                 \n"
		"                                                                  \n"
		"void main(void)                                                   \n"
		"{                                                                 \n"
		"    const vec4 vertices[] = vec4[](vec4( 0.25, -0.25, 0.5, 1.0),  \n"
		"                                   vec4(-0.25, -0.25, 0.5, 1.0),  \n"
		"                                   vec4( 0.25,  0.25, 0.5, 1.0)); \n"
		"                                                                  \n"
		"    gl_Position = vertices[gl_VertexID];                          \n"
		"}                                                                 \n"
	};

	static const char * fs_source[] =
	{
		"#version 420 core                                                 \n"
		"                                                                  \n"
		"out vec4 color;                                                   \n"
		"                                                                  \n"
		"void main(void)                                                   \n"
		"{                                                                 \n"
		"    color = vec4(0.0, 0.8, 1.0, 1.0);                             \n"
		"}                                                                 \n"
	};


	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, fs_source, NULL);
	glCompileShader(fs);

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, vs_source, NULL);
	glCompileShader(vs);

	m_gluProgram = glCreateProgram();
	glAttachShader(m_gluProgram, vs);
	glAttachShader(m_gluProgram, fs);

	glLinkProgram(m_gluProgram);

	glDeleteShader(vs);
	glDeleteShader(fs);

	glGenVertexArrays(1, &m_gluVAO);
	glBindVertexArray(m_gluVAO);
	return false;
}
bool OGLObject::Render()
{
	static const GLfloat green[] = { 0.0f, 1.0f, 0.0f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, green);

	glUseProgram(m_gluProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	return true;
}
bool OGLObject::Destory()
{
	glDeleteVertexArrays(1, &m_gluVAO);
	glDeleteProgram(m_gluProgram);
	return false;
}