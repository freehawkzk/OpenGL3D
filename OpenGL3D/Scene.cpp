#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
}


CScene::~CScene()
{
}

bool CScene::Render()
{
	for (size_t i = 0; i < m_vObjs.size(); i++)
	{
		m_vObjs[i]->Render();
	}
	return true;
}