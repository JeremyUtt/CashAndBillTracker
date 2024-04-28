// #ifndef BUTTON_H
// #define BUTTON_H
// #include <SFML/Graphics.hpp>
// #include <functional>
// #include <string>

// #include "Item.h"
// #include "User.h"

// struct ButtonLink {
//     Item* item;
//     User* user;
// };

// class Button {
// private:
//     int _xPos;
//     int _yPos;
//     int _width;
//     int _height;
//     bool _active;
//     bool _hasText;
//     bool _hovered;
//     sf::Text _text;
//     sf::Color _color;
//     // https://stackoverflow.com/questions/41959721/passing-function-to-class-in-c
//     // (i made this part before learning function pointers in class)
//     std::function<void(Button*, ButtonLink&)> _func;

// public:
//     Button(int x, int y, int width, int height, const std::function<void(Button*, ButtonLink&)> func);
//     bool updateHoverStatus(int mouseX, int mouseY);
//     void render(sf::RenderWindow& window) const;
//     void setActiveStatus(bool status);
//     void setText(std::string text, sf::Font& font, int fontSize);
//     sf::Color getColor() const;
//     void setColor(sf::Color color);
//     void callFunc(ButtonLink& link);
// };
// #endif