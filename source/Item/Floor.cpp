#include <cassert>
#include "../Game.h"
#include "Floor.h"

using namespace OT;
using namespace Item;


Floor::~Floor() {}

void Floor::init()
{
	Item::init();
	
	layer = -1;
	
	sf::Texture *t = new sf::Texture();
	t->loadFromImage(App->bitmaps["simtower/floor"]);
	background.setTexture(*t);
	//background.SetImage(App->bitmaps["simtower/floor"]);
	background.setTextureRect(sf::IntRect(0, 0, 8, 36));
	background.setOrigin(0, 36);
	//background.Resize(0, 36);

	//ceiling.SetImage(App->bitmaps["simtower/floor"]);
	t = new sf::Texture();
	t->loadFromImage(App->bitmaps["simtower/floor"]);
	ceiling.setTexture(*t);
	ceiling.setTextureRect(sf::IntRect(0, 0, 8, 12));
	//ceiling.Resize(0, 12);
	ceiling.setPosition(0, -GetSize().y);

	interval.insert(position.x);
	interval.insert(getRect().maxX());
	
	updateSprite();
}

void Floor::encodeXML(tinyxml2::XMLPrinter & xml)
{
	Item::encodeXML(xml);
	xml.PushAttribute("width", size.x);
}

void Floor::decodeXML(tinyxml2::XMLElement & xml)
{
	Item::decodeXML(xml);
	size.x = xml.IntAttribute("width");
	updateSprite();
}

void Floor::updateSprite() {}

void Floor::Render(sf::RenderTarget & target) const
{
	bool drawBackground = true;
	int left = 0;
	int right = 0;
	Sprite b = background;
	Sprite c = ceiling;
	for(std::multiset<int>::const_iterator i = interval.begin(); i != interval.end();) {
		if(drawBackground) {
			// Draw full floor sprite
			drawBackground = false;
			left = *i; ++i;
			if(i == interval.end()) break;
			right = *i;
			if(left == right) continue;

			////b.Resize((right - left) * 8.0f, 36.0f);
			//b.SetX((left - position.x) * 8.0f);
			b.setPosition((left - position.x) * 8.0f, b.getPosition().y);
			target.draw(b);
		} else {
			// Draw only ceiling sprite
			drawBackground = true;
			left = *i; ++i;
			if(i == interval.end()) break;
			right = *i;
			if(left == right) continue;

			//c.Resize((right - left) * 8.0f, 12.0f);
			//c.SetX((left - position.x) * 8.0f);
			c.setPosition((left - position.x) * 8.0f, c.getPosition().y);
			target.draw(c);
		}

		game->drawnSprites++;
	}
}
