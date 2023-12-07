#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Button.h"
#include "Item.h"
#include "User.h"

void renderWindow(std::vector<User*>& users, std::vector<Item*>& items);
void handleEvents(sf::RenderWindow& window, std::vector<Button*> buttons, std::vector<ButtonLink> buyTable);
void userToggleButton(Button* button, ButtonLink& link);
std::string fltToStr(float num);
#endif