#ifndef MAIN_H
#define MAIN_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "Button.h"
#include "Item.h"
#include "User.h"

void readManual(std::vector<User*>& users, std::vector<Item*>& items);
void readCSV(std::vector<User*>& users, std::vector<Item*>& items);

void renderWindow(std::vector<User*>& users, std::vector<Item*>& items);
void handleEvents(sf::RenderWindow& window, std::vector<Button*> buttons, std::vector<ButtonLink> buyTable,std::vector<User*>& users, std::vector<Item*>& items);
void userToggleButton(Button* button, ButtonLink& link);
std::string fltToStr(float num);
void updateTotals(std::vector<User*>& users, std::vector<Item*>& items);
#endif