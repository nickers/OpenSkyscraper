#include "../Game.h"
#include "../Math/Rand.h"
#include "Metro.h"

using namespace OT;
using namespace OT::Item;


Metro::~Metro()
{
}

void Metro::init()
{
	Item::init();
	
	open = true;
	trainPresent = true;

	sf::Texture *t = new sf::Texture();
	t->loadFromImage(App->bitmaps["simtower/metro/station"]);
	station.setTexture(*t);
	//station.SetImage(App->bitmaps["simtower/metro/station"]);
	station.setOrigin(0, 96);
	//platform.SetImage(App->bitmaps["simtower/metro/station"]);
	platform.setTexture(*t);
	platform.setOrigin(0, 30);
	addSprite(&station);
	addSprite(&platform);
	spriteNeedsUpdate = true;

	assert(game->metroStation == NULL);
	game->metroStation = this;
	
	updateSprite();
}

void Metro::encodeXML(tinyxml2::XMLPrinter & xml)
{
	Item::encodeXML(xml);
	xml.PushAttribute("open", open);
	xml.PushAttribute("trainPresent", trainPresent);
}

void Metro::decodeXML(tinyxml2::XMLElement & xml)
{
	Item::decodeXML(xml);
	open = xml.BoolAttribute("open");
	trainPresent = xml.BoolAttribute("trainPresent");
	updateSprite();
}

void Metro::updateSprite()
{
	spriteNeedsUpdate = false;
	int stationIndex = 2, platformIndex = 2;
	if (open) {
		stationIndex = 1;
		platformIndex = (trainPresent ? 0 : 1);
	}

	station.setTextureRect(sf::IntRect(stationIndex*240, 0, (stationIndex+1)*240, 66));
	//station.Resize(240, 66);

	platform.setTextureRect(sf::IntRect(platformIndex*240, 66, (platformIndex+1)*240, 96));
	//platform.Resize(240, 30);
}

void Metro::advance(double dt)
{
	//Open
	if (game->time.checkHour(7)) {
		open = true;
		spriteNeedsUpdate = true;
	}
	
	//Close
	if (game->time.checkHour(23) && open) {
		open = false;
		spriteNeedsUpdate = true;
	}
	
	if (spriteNeedsUpdate) updateSprite();
}
