#include "Button.h"

#include <SFML/Graphics.hpp>
#include <string>
Button::Button(/* args */) {
    this->xPos = 0;
    this->yPos = 0;
    this->width = 100;
    this->height = 50;
    this->active = true;
    this->hasText = false;
    this->hovered = false;
}
Button::Button(int x, int y, int width, int height) {
    this->xPos = x;
    this->yPos = y;
    this->width = width;
    this->height = height;
    this->active = true;
    this->hasText = false;
    this->hovered = false;
}

bool Button::updateHoverStatus(int mouseX, int mouseY) {
    if (!active) {
        this->hovered = false;
        return false;
    }
    if (mouseX > xPos && mouseX < xPos + width) {
        if (mouseY > yPos && mouseY < yPos + height) {
            this->hovered = true;
            return true;
        }
    }
    this->hovered = false;
    return false;
}

void Button::render(sf::RenderWindow& window, sf::Font& textFont) {
    const int borderWidth = 1;
    auto drawObject = sf::RectangleShape(sf::Vector2f(width, height));
    drawObject.setPosition(sf::Vector2f(xPos, yPos));
    drawObject.setOutlineThickness(borderWidth);
    drawObject.setFillColor(sf::Color(0x2b2b2bff));
    if (this->hovered) {
        drawObject.setOutlineColor(sf::Color::Blue);
    } else {
        drawObject.setOutlineColor(sf::Color::White);
    }

    window.draw(drawObject);

    if (hasText) {
        window.draw(this->text);
    }
}

void Button::setText(std::string string, sf::Font& font, int fontSize) {
    this->hasText = true;
    this->text = sf::Text(string, font, fontSize);
    int textX = xPos + (width / 2) - (this->text.getLocalBounds().width / 2);
    int textY = yPos + (height / 2) - (this->text.getLocalBounds().height / 2);
    this->text.setPosition(sf::Vector2f(textX, textY));
}