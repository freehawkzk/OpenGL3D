#include "stdafx.h"
#include "OGLObject.h"


OGLObject::OGLObject():m_gluProgram(-1),m_gluVAO(-1),m_pVerts(NULL),m_nVertsCount(0),m_bCreatedMesh(false)
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
		"    color = vec4(sin(gl_FragCoord.x * 0.25) * 0.5 + 0.5,cos(gl_FragCoord.y * 0.25) * 0.5 + 0.5, sin(gl_FragCoord.x * 0.15) * cos(gl_FragCoord.y * 0.15), 1.0);                             \n"
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



COGLPoint::COGLPoint():m_gluBuffer(0),m_glfPointSize(10)
{

}

COGLPoint::~COGLPoint()
{
	if (m_pVerts)
	{
		delete[] m_pVerts;
		m_pVerts = NULL;
	}
}

bool COGLPoint::SetUp()
{
	bool hr = true;
	hr = hr && MakeShaderProgram();
	hr = hr && MakeMesh();

	return hr;
}

bool COGLPoint::MakeShaderProgram()
{
	if (m_gluProgram == -1)
	{
		static const char * vs_source[] =
		{
			"#version 420 core                                                 \n"
			"                                                                  \n"
			"void main(void)                                                   \n"
			"{                                                                 \n"
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
			"    color = vec4(1.0,0.0,0.0, 1.0);                             \n"
			"}                                                                 \n"
		};

		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fs, 1, fs_source, NULL);
		glCompileShader(fs);
		GLint hr = GL_TRUE;
		glGetShaderiv(fs, GL_COMPILE_STATUS, &hr);
		if (hr != GL_TRUE)
		{
			return false;
		}

		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vs, 1, vs_source, NULL);
		glCompileShader(vs);
		glGetShaderiv(vs, GL_COMPILE_STATUS, &hr);
		if (hr != GL_TRUE)
		{
			return false;
		}

		m_gluProgram = glCreateProgram();
		glAttachShader(m_gluProgram, vs);
		glAttachShader(m_gluProgram, fs);

		glLinkProgram(m_gluProgram);

		glDeleteShader(vs);
		glDeleteShader(fs);
		return true;
	}
	return true;
}

bool COGLPoint::MakeMesh()
{
	if (!m_bCreatedMesh)
	{
		glGenVertexArrays(1, &m_gluVAO);
		glBindVertexArray(m_gluVAO);

		glGenBuffers(1, &m_gluBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_gluBuffer);
		if (!m_pVerts)
		{
			m_pVerts = new float[4];
			m_pVerts[0] = 0.25;
			m_pVerts[1] = -0.25;
			m_pVerts[2] = 0.5;
			m_pVerts[3] = 1.0;
		}
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), (unsigned char*)m_pVerts, GL_STATIC_DRAW);
		m_bCreatedMesh = true;
	}
	
	return true;
}

bool COGLPoint::Render()
{
	SetUp();
	glUseProgram(m_gluProgram);
	glPointSize(m_glfPointSize);
	glDrawArrays(GL_POINTS, 0, 1);
	return true;
}

bool COGLPoint::Destory()
{

	return true;
}