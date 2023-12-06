#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

typedef std::function<void()> buttonFunction;

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
    buttonFunction func;

public:
    Button(int x, int y, int width, int height, const buttonFunction& func);
    bool updateHoverStatus(int mouseX, int mouseY);
    void render(sf::RenderWindow& window);
    void setActiveStatus(bool status);
    void setText(std::string text, sf::Font& font, int fontSize);
    void setColor(sf::Color color);
    void callFunc();
};

#endif