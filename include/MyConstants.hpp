#pragma once
#include <SFML/Graphics.hpp>

namespace Constants
{
	/* Screen Variables */
	const int screen_height{ 800 };
	const int screen_width{ 800 };
	const sf::Vector2f offset{ (float)screen_width / 2.0f, (float)screen_height / 2.0f };

	/* Cosmetic Variables */
	const sf::Color bg{ sf::Color(49, 46, 43) };
	const sf::Color chess_green{ sf::Color(118, 150, 86) };
	const sf::Color chess_white{ sf::Color(238, 238, 210) };
	const sf::Color path_color{ sf::Color{255, 0, 0} };
}