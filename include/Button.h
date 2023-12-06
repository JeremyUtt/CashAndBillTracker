#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>
#include "Item.h"
#include "User.h"
// typedef std::function<void()> buttonFunction;
struct ButtonLink
{
    Item* item;
    User* user;
};

class Button {

private:
    int xPos_;
    int yPos_;
    int width_;
    int height_;
    bool active_;
    bool hasText_;
    bool hovered_;
    sf::Text text_;
    sf::Color color_;
    std::function<void(Button*, ButtonLink&)> func;

public:
    // Button(int x, int y, int width, int height, const buttonFunction& func);
    Button(int x, int y, int width, int height, const std::function<void(Button*, ButtonLink&)> func1);
    bool updateHoverStatus(int mouseX, int mouseY);
    void render(sf::RenderWindow& window);
    void setActiveStatus(bool status);
    void setText(std::string text, sf::Font& font, int fontSize);
    sf::Color getColor();
    void setColor(sf::Color color);
    void callFunc(ButtonLink& link);
};
#endif