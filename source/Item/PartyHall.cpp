#include "../Game.h"
#include "../Math/Rand.h"
#include "PartyHall.h"

using namespace OT;
using namespace OT::Item;


PartyHall::~PartyHall()
{
}

void PartyHall::init()
{
	Item::init();
	
	open = false;
	sf::Texture *t = new sf::Texture();
	t->loadFromImage(App->bitmaps["simtower/partyhall"]);
	sprite.setTexture(*t);
	//sprite.SetImage(App->bitmaps["simtower/partyhall"]);
	sprite.setOrigin(0, 60);
	addSprite(&sprite);
	spriteNeedsUpdate = false;
	
	updateSprite();
}

void PartyHall::encodeXML(tinyxml2::XMLPrinter & xml)
{
	Item::encodeXML(xml);
	xml.PushAttribute("open", open);
}

void PartyHall::decodeXML(tinyxml2::XMLElement & xml)
{
	Item::decodeXML(xml);
	open = xml.BoolAttribute("open");
	updateSprite();
}

void PartyHall::updateSprite()
{
	spriteNeedsUpdate = false;
	int index = (open ? 1 : 0);
	sprite.setTextureRect(sf::IntRect(index*192, 0, (index+1)*192, 60));
	//sprite.Resize(192, 60);
}

void PartyHall::advance(double dt)
{
	//Open
	if (game->time.checkHour(13)) {
		open = true;
		spriteNeedsUpdate = true;
	}
	
	//Close
	if (game->time.checkHour(17) && open) {
		open = false;
		spriteNeedsUpdate = true;
		
		//TODO: Specify party hall income.
		game->transferFunds(10000, "Income from Party Hall");
	}
	
	//TODO: Make people arrive at the hall and leave afterwards.
	
	if (spriteNeedsUpdate) updateSprite();
}

Path PartyHall::getRandomBackgroundSoundPath()
{
	if (!open) return "";
	return "simtower/partyhall";
}
