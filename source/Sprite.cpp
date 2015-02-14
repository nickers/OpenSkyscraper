#include "Sprite.h"
#include "OpenGL.h"

using namespace OT;


void Sprite::Render(sf::RenderTarget & target) const
{
	glTranslatef(-0.375f, -0.375f, 0.f);
	//sf::Sprite::Render(target);
	target.draw(*this);
}		
