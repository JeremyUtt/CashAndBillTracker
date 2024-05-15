#pragma once

#include <string>
#include <vector>
#include "Item.h"
#include "User.h"

std::string fltToStr(float num);

void updateTotals(std::vector<User*>& users, std::vector<Item*>& items);
