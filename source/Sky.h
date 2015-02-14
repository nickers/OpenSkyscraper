#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "Math/Vector2D.h"
#include "GameObject.h"
#include "Sound.h"

namespace OT {
	
	class Sky : public GameObject, public sf::Drawable
	{
	public:
		Sky(Game * game);
		
		int from;
		int to;
		double progress;
		
		bool rainyDay;
		double rainAnimation;
		double thunderOverlay;

		void advance(double dt);
		virtual void Render(sf::RenderTarget & target) const;

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
		{
			target.draw(*this, states);
		}
		
		static double cloudNoise(double2 p);
		
		Sound rainSound;
		Sound thunderSound;
		Sound birdsSound;
		Sound cricketsSound;
		double soundCountdown;
	};
}
