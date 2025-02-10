#pragma once
#include <SFML/Graphics.hpp>
//#include <SFML/System.hpp>

class Textbox
{
	public:
		Textbox(sf::Vector2f pos, sf::Vector2f size, sf::Color color, const std::string& fontPath);

		void render(sf::RenderWindow& window);

		bool loadFont(const std::string& fontPath);

		void setText(const std::string& str);
	private:
		sf::Vector2f position, size;
		sf::RectangleShape background;
		sf::Text text;
		sf::Font font;
		std::string str;

};