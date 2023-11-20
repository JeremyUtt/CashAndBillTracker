#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

typedef std::function<void()> buttonFunction;

class Button {
private:
    int xPos;
    int yPos;
    int width;
    int height;
    bool active;
    bool hasText;
    bool hovered;
    sf::Text text;
    buttonFunction func;

public:
    Button(int x, int y, int width, int height, const buttonFunction& func);
    bool updateHoverStatus(int mouseX, int mouseY);
    void render(sf::RenderWindow& window);
    void setActiveStatus(bool status);
    void setText(std::string text, sf::Font& font, int fontSize);
    void callFunc();
};

#endif