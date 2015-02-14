#include <cassert>
#include "../Game.h"
#include "Lobby.h"

using namespace OT;
using namespace Item;


Lobby::~Lobby()
{
	assert(position.y != 0);
}

void Lobby::init()
{
	Item::init();
	bool groundLobby = (position.y == 0);
	
	Path p = (groundLobby ? "simtower/lobby/normal" : "simtower/lobby/sky");

	sf::Texture *t = new sf::Texture();
	t->loadFromImage(App->bitmaps[p]);
	background.setTexture(*t);
	//background.SetImage(App->bitmaps[p]);
	background.setOrigin(0, 36);
	overlay = background;
	
	if (groundLobby) {
		assert(game->mainLobby == NULL);
		game->mainLobby = this;
		
		for (int i = 0; i < 2; i++) {
			t = new sf::Texture();
			t->loadFromImage(App->bitmaps["simtower/deco/entrances"]);
			entrances[i].setTexture(*t);
			//entrances[i].SetImage(App->bitmaps["simtower/deco/entrances"]);
			entrances[i].setOrigin(56*(1-i), 36);
			entrances[i].setTextureRect(sf::IntRect(i*56, 0, (i+1)*56, 36));
			addSprite(&entrances[i]);
		}
	}
	
	updateSprite();
}

void Lobby::encodeXML(tinyxml2::XMLPrinter & xml)
{
	Item::encodeXML(xml);
	xml.PushAttribute("width", size.x);
}

void Lobby::decodeXML(tinyxml2::XMLElement & xml)
{
	Item::decodeXML(xml);
	size.x = xml.IntAttribute("width");
	updateSprite();
}

void Lobby::updateSprite()
{
	int y = 0;
	if (game->rating == 2) y = 1;
	if (game->rating >= 3) y = 2;
	
	sf::IntRect rect(0, y*36, 0, (y+1)*36);
	rect.width = 7 * 8 - rect.left;
	overlay.setTextureRect(rect);
	rect.left  = (rect.left+rect.width);
	rect.width = 312 - rect.left;
	background.setTextureRect(rect);
	
	entrances[0].setPosition(0, entrances[0].getPosition().y);
	//entrances[0].SetX(0);
	entrances[1].setPosition(GetSize().x, entrances[1].getPosition().y);
	//entrances[1].SetX(GetSize().x);
}

void Lobby::Render(sf::RenderTarget & target) const
{
	Item::Render(target);
	sf::FloatRect view = target.getView().getViewport();
	recti rect = getRect();
	
	int minx = std::max<int>(floor(view.left / 256), floor(rect.minX() / 32.0));
	int maxx = std::min<int>(ceil((view.left+view.width) / 256), ceil (rect.maxX() / 32.0));
	Sprite b = background;

	for (int x = minx; x < maxx; x++) {
		int offl = std::max<int>(0, rect.minX() - x*32) * 8;
		int offr = std::max<int>(0, (x+1)*32 - rect.maxX()) * 8;
		sf::IntRect sr = background.getTextureRect();
		sr.left  += offl;
		//sr.Right -= offr;
		b.setTextureRect(sr);
		
		//b.SetX((x * 32 - rect.minX()) * 8 + offl);
		b.setPosition((x * 32 - rect.minX()) * 8 + offl, b.getPosition().y);
		target.draw(b);
		
		game->drawnSprites++;
	}
	
	Sprite o = overlay;
	sf::IntRect sr = o.getTextureRect();
	sr.width = std::min<int>(sr.width, GetSize().x - 16 - sr.left);
	o.setTextureRect(sr);
	target.draw(o);
	game->drawnSprites++;
}
