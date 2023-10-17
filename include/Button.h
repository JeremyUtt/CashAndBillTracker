#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <string>
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

public:
    Button();
    Button(int x, int y, int width, int height);
    bool updateHoverStatus(int mouseX, int mouseY);
    void render(sf::RenderWindow& window, sf::Font& textFont);
    void setActiveStatus(bool status);
    void setText(std::string text, sf::Font& font, int fontSize);
};

#endif