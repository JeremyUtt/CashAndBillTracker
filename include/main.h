#pragma once

#include <string>
#include <vector>

#include "Item.h"
#include "User.h"

void readManual(std::vector<User*>& users, std::vector<Item*>& items);
void readCSV(std::string filename,std::vector<User*>& users, std::vector<Item*>& items);
std::string fltToStr(float num);
void updateTotals(std::vector<User*>& users, std::vector<Item*>& items);
