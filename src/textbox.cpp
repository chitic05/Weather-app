#include "textbox.h"
#include <iostream>
Textbox::Textbox(sf::Vector2f pos, sf::Vector2f size, sf::Color color, const std::string& fontPath) : background(size)
	{
		position = pos;
		size = size;

		background.setFillColor(color);
		background.setPosition(pos);

		if(!loadFont(fontPath))
		{
			std::cout << "Font can't load\n";
		}
		else
		{
			str = "";
			text.setFont(font);
			text.setCharacterSize(24);
			text.setPosition(sf::Vector2f(position.x+10.0f, position.y + 10.0f));
			text.setColor(sf::Color::White);
		}

	}

bool Textbox::loadFont(const std::string& fontPath)
{
	return font.loadFromFile(fontPath);
}

void Textbox::setText(const std::string& str)
{
	text.setString(str);
}

void Textbox::render(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(text);
}
