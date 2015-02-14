#include "Escalator.h"

using namespace OT::Item;


void Escalator::init()
{
	frameCount = 8;
	sf::Texture *t = new sf::Texture();
	t->loadFromImage(App->bitmaps["simtower/escalator"]);
	sprite.setTexture(*t);
	//sprite.SetImage(App->bitmaps["simtower/escalator"]);
	Stairlike::init();
}
