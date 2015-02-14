#include "Stairs.h"

using namespace OT::Item;


void Stairs::init()
{
	frameCount = 14;
	sf::Texture *t = new sf::Texture();
	t->loadFromImage(App->bitmaps["simtower/stairs"]);
	sprite.setTexture(*t);

	//sprite.SetImage(App->bitmaps["simtower/stairs"]);
	Stairlike::init();
}
