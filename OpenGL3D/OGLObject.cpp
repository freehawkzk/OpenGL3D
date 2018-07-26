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
	
	return true;
}
bool OGLObject::Render()
{
	return true;
}
bool OGLObject::Destory()
{
	return false;
}



COGLPoint::COGLPoint() : m_glfPointSize(10)
{

}

COGLPoint::~COGLPoint()
{
	if (m_pVerts)
	{
		delete m_pVerts;
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
		GLuint shaders[2] = { 0,0 };
		shaders[0] = GetShaderLoader()->CreateShaderFromFile("./shaders/singlePoint.vs.glsl", GL_VERTEX_SHADER);
		shaders[1] = GetShaderLoader()->CreateShaderFromFile("./shaders/singlePoint.fs.glsl", GL_FRAGMENT_SHADER);
		m_gluProgram = GetShaderLoader()->LinkProgram(shaders, 2);
		return true;
	}
	return true;
}
int g_count = 0;
bool COGLPoint::MakeMesh()
{
	if (!m_bCreatedMesh)
	{
		glGenVertexArrays(1, &m_gluVAO);
		glBindVertexArray(m_gluVAO);
		glGenBuffers(1, &m_gluBuffer[0]);
		glGenBuffers(1, &m_gluBuffer[1]);
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, m_gluBuffer[0]);
	if (!m_pVerts)
	{
		m_pVerts = new vmath::vec4;
	}
	*m_pVerts = vmath::vec4(0 + 0.01*g_count, 0 + 0.01*g_count, 0.5, 1.0);
	if (g_count > 100)
	{
		g_count = -100;
	}
	g_count++;
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), (unsigned char*)m_pVerts, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(m_gluVAO, 0, m_gluBuffer[0], 0, sizeof(vmath::vec4));
	glVertexArrayAttribFormat(m_gluVAO, 0, 4, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(m_gluVAO, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	
	glBindBuffer(GL_ARRAY_BUFFER, m_gluBuffer[1]);
	m_vPointColor = vmath::vec4((0+0.01*g_count+1)/2, (0 + 0.01*g_count + 1) / 4, 0.0, 1.0);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), (unsigned char*)(&m_vPointColor), GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(m_gluVAO, 1, m_gluBuffer[1], 0, sizeof(vmath::vec4));
	glVertexArrayAttribFormat(m_gluVAO, 1, 4, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(m_gluVAO, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	m_bCreatedMesh = true;

	return true;
}

bool COGLPoint::Render()
{
	glPushMatrix();
	SetUp();
	glUseProgram(m_gluProgram);
	glPointSize(m_glfPointSize);
	glDrawArrays(GL_POINTS, 0, 1);
	glPopMatrix();
	return true;
}

bool COGLPoint::Destory()
{
	glDeleteVertexArrays(1, &m_gluVAO);
	glDeleteProgram(m_gluProgram);
	return true;
}