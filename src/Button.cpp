#include "Button.h"

#include <SFML/Graphics.hpp>
#include <string>

Button::Button(int x, int y, int width, int height, const std::function<void(Button*, ButtonLink&)> func) {
    this->xPos_ = x;
    this->yPos_ = y;
    this->width_ = width;
    this->height_ = height;
    this->active_ = true;
    this->hasText_ = false;
    this->hovered_ = false;
    this->func = func;
}

bool Button::updateHoverStatus(int mouseX, int mouseY) {
    if (!active_) {
        this->hovered_ = false;
        return false;
    }
    if (mouseX > xPos_ && mouseX < xPos_ + width_) {
        if (mouseY > yPos_ && mouseY < yPos_ + height_) {
            this->hovered_ = true;
            return true;
        }
    }
    this->hovered_ = false;
    return false;
}

void Button::render(sf::RenderWindow& window) {
    // Created a draw object, configures it, and
    // draws it to the screen
    const int borderWidth = 3;
    auto drawObject = sf::RectangleShape(sf::Vector2f(width_, height_));
    drawObject.setPosition(sf::Vector2f(xPos_, yPos_));
    drawObject.setOutlineThickness(borderWidth);
    drawObject.setFillColor(color_);
    // change border color depending on if its activaly holvered over
    if (this->hovered_) {
        drawObject.setOutlineColor(sf::Color::Blue);
    } else {
        drawObject.setOutlineColor(sf::Color::White);
    }

    window.draw(drawObject);

    if (hasText_) {
        window.draw(this->text_);
    }
}

void Button::setText(std::string string, sf::Font& font, int fontSize) {
    // configures a text element to be drawn inside the button
    this->hasText_ = true;
    this->text_ = sf::Text(string, font, fontSize);
    int textX = xPos_ + (width_ / 2) - (this->text_.getLocalBounds().width / 2);
    int textY = yPos_ + (height_ / 2) - (this->text_.getLocalBounds().height / 2);
    this->text_.setPosition(sf::Vector2f(textX, textY));
}

void Button::callFunc(ButtonLink& link) {
    // calls function that is passed to the class at
    // object/instance creation time

    // uses ButtonLink& link to have less parameters
    func(this, link);
}

sf::Color Button::getColor() {
    return color_;
}

void Button::setColor(sf::Color color) {
    this->color_ = color;
}