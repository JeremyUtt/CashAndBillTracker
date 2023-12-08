#include "Button.h"

#include <SFML/Graphics.hpp>
#include <string>

Button::Button(int x, int y, int width, int height, const std::function<void(Button*, ButtonLink&)> func) {
    this->_xPos = x;
    this->_yPos = y;
    this->_width = width;
    this->_height = height;
    this->_active = true;
    this->_hasText = false;
    this->_hovered = false;
    this->_func = func;
}

bool Button::updateHoverStatus(int mouseX, int mouseY) {
    if (!_active) {
        this->_hovered = false;
        return false;
    }
    if (mouseX > _xPos && mouseX < _xPos + _width) {
        if (mouseY > _yPos && mouseY < _yPos + _height) {
            this->_hovered = true;
            return true;
        }
    }
    this->_hovered = false;
    return false;
}

void Button::render(sf::RenderWindow& window) const{
    // Created a draw object, configures it, and
    // draws it to the screen
    const int borderWidth = 3;
    auto drawObject = sf::RectangleShape(sf::Vector2f(_width, _height));
    drawObject.setPosition(sf::Vector2f(_xPos, _yPos));
    drawObject.setOutlineThickness(borderWidth);
    drawObject.setFillColor(_color);
    // change border color depending on if its activaly holvered over
    if (this->_hovered) {
        drawObject.setOutlineColor(sf::Color::Blue);
    } else {
        drawObject.setOutlineColor(sf::Color::White);
    }

    window.draw(drawObject);

    if (_hasText) {
        window.draw(this->_text);
    }
}

void Button::setText(std::string string, sf::Font& font, int fontSize) {
    // configures a text element to be drawn inside the button
    this->_hasText = true;
    this->_text = sf::Text(string, font, fontSize);
    int textX = _xPos + (_width / 2) - (this->_text.getLocalBounds().width / 2);
    int textY = _yPos + (_height / 2) - (this->_text.getLocalBounds().height / 2);
    this->_text.setPosition(sf::Vector2f(textX, textY));
}

void Button::callFunc(ButtonLink& link) {
    // calls function that is passed to the class at
    // object/instance creation time

    // uses ButtonLink& link to have less parameters
    _func(this, link);
}

sf::Color Button::getColor() const{
    return _color;
}

void Button::setColor(sf::Color color) {
    this->_color = color;
}