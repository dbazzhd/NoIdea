#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP

#include <SFML\Graphics.hpp>
#include <iostream>
#include "mge/config.hpp"

class TextField {
public:
	TextField(std::string pFontName, int pFontSize);
	~TextField();
	sf::Text* getText();
private:
	sf::Font* _font;
	sf::Text* _text;
};

#endif
