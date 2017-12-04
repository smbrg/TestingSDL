#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(Game* pParent, const char* pTextureSheet, int nXpos, int nYpos)
{
	m_nXpos = nXpos;
	m_nYpos = nYpos;
	m_pObjectTexture = pParent->getTextureManager()->loadTexture(pTextureSheet);
	m_pParent = pParent;
}

GameObject::~GameObject()
{
}

void GameObject::update()
{
	m_nXpos++;
	m_nYpos++;

	m_SrcRect.h = 32;
	m_SrcRect.w = 32;
	m_SrcRect.x = 0;
	m_SrcRect.y = 0;


	m_DestRect.w = m_SrcRect.w * 2;
	m_DestRect.h = m_SrcRect.h * 2;
	m_DestRect.x = m_nXpos;
	m_DestRect.y = m_nYpos;
}

void GameObject::render()
{
	SDL_RenderCopy(m_pParent->getRenderer(), m_pObjectTexture, &m_SrcRect, &m_DestRect);
}
