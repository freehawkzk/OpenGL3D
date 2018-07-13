#pragma once
#include "stdafx.h"
class OGLObject
{
public:
	OGLObject();
	~OGLObject();
public:
	GLuint m_gluProgram;
	GLuint m_gluVAO;

	virtual bool SetUp();
	virtual GLuint MakeShaderProgram() { return 0; };
	virtual bool MakeMesh() { return true; };
	virtual bool Update() { return true; };
	virtual bool Render();
	virtual bool Destory();
};

