#pragma once
#include "OGLObject.h"
class CScene
{
public:
	CScene();
	~CScene();

	virtual bool Render();
public:
	VOGLOBJECTS m_vObjs;
};

