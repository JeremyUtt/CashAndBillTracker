#pragma once
#include <string>
#include <vector>

#include "Item.h"
#include "User.h"

void readCSV(std::string fileName, std::vector<User*>& users, std::vector<Item*>& items);
std::string openCSV();