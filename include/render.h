#pragma once
#include "imgui_impl_glfw.h"
#include <vector>
#include "Item.h"
#include "User.h"

void loop(GLFWwindow* window, std::vector<User*>& users, std::vector<Item*>& items, bool* buyTable);

extern ImFont* font1;
extern ImFont* font2;