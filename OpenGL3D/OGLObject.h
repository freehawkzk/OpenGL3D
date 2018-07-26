#pragma once
#include "stdafx.h"
class OGLObject
{
public:
	OGLObject();
	virtual ~OGLObject();
public:
	GLuint m_gluProgram;
	GLuint m_gluVAO;

	virtual bool SetUp();
	virtual bool MakeShaderProgram() { return 0; };
	virtual bool MakeMesh() { return true; };
	virtual bool Update() { return true; };
	virtual bool Render();
	virtual bool Destory();
	
	float* m_pVerts;
	int    m_nVertsCount;
	bool   m_bCreatedMesh;
};

#include <vector>
typedef std::vector<OGLObject*> VOGLOBJECTS;

class COGLPoint:public OGLObject
{
public:
	COGLPoint();
	virtual ~COGLPoint();
	virtual bool SetUp();
	virtual bool MakeShaderProgram();
	virtual bool MakeMesh();
	//virtual bool Update() {};
	virtual bool Render();
	virtual bool Destory();

	GLuint m_gluBuffer;
	GLfloat m_glfPointSize;

protected:
private:
};