#include "mge/objects/TextField.h"

TextField::TextField(std::string pFontName, int pFontSize) {
	_font = new sf::Font();
	if (!_font->loadFromFile(config::MGE_FONT_PATH + pFontName)) std::cout << "ERROR LOADING FONT" << std::endl;
	_text = new sf::Text("TEXTFIELD", *_font, pFontSize);
	_text->setColor(sf::Color(1, 0, 0));

}

TextField::~TextField() {

}
sf::Text* TextField::getText() {
	return _text;
}