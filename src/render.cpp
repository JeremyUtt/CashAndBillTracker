#include "render.h"
#include "logic.h"
#include <GLFW/glfw3.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_opengl3.h"

using namespace std;
using namespace ImGui;

ImFont* font1;
ImFont* font2;
const vector<string> tags = {"Name:", "Total:", "Users: (Select one or more per item)", "Price Per Person:"};

void loop(GLFWwindow* window, vector<User*>& users, vector<Item*>& items, bool* checkedTable) {
    using namespace ImGui;

    Begin("Fullscreen Window",
          NULL,
          ImGuiWindowFlags_NoResize |
              ImGuiWindowFlags_NoMove |
              ImGuiWindowFlags_NoCollapse |
              ImGuiWindowFlags_NoTitleBar |
              ImGuiWindowFlags_NoBringToFrontOnFocus);
    // Begin("Table");

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    SetWindowSize(ImVec2(width, height));
    SetWindowPos(ImVec2(0, 0));

    ImGui::PushFont(font2);
    ImGui::PushFont(font1);
    Text("Cost and Bill Tracker");
    ImGui::PopFont();

    if (BeginTable("main", 3 + users.size(), ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX)) {
        for (size_t i = 0; i < 2; i++) {
            TableNextColumn();
            TableHeader(tags[i].c_str());
        }
        for (size_t i = 0; i < users.size() + 1; i++) {
            TableHeader("");
            TableNextColumn();
        }
        TableHeader(tags[3].c_str());

        // TableNextRow();

        // Repeat for every item in the list
        for (size_t i = 0; i < items.size(); i++) {
            // Create Name coloum

            TableNextColumn();
            Text(items[i]->getName().c_str());

            // Create Total (2nd) coloum
            TableNextColumn();
            Text(fltToStr(items[i]->getTotalPrice()).c_str());

            // Create Button Objects
            for (size_t j = 0; j < users.size(); j++) {
                TableNextColumn();

                std::cout << i << " " << j << std::endl;

                string name = users[j]->getName() + "##" + to_string(i * users.size() + j);

                bool clicked = Checkbox(name.c_str(), &checkedTable[i * users.size() + j]);
                if (clicked) {
                    std::cout << "Hi" << std::endl;
                    if (checkedTable[i * users.size() + j]) {
                        items[i]->addUser(users[j]);
                    } else {
                        items[i]->removeUser(users[j]);
                    }
                    updateTotals(users, items);
                }
            }

            // Create Price Per Person (last) column
            string text = fltToStr(items[i]->pricePerPerson());
            if (text == "$inf") {
                text = "Select at least one person";
            }

            TableNextColumn();
            Text(text.c_str());

            // TableNextRow();
        }
        EndTable();
    }

    // Create section that will contain each users total cost

    if (BeginTable("totals", 1 + users.size(), ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX)) {
        TableNextColumn();

        TableHeader("User:");
        for (auto user : users) {
            TableNextColumn();
            TableHeader(user->getName().c_str());
        }
        TableNextColumn();
        Text("Total:");
        // Show USers total
        for (auto user : users) {
            TableNextColumn();
            Text(fltToStr(user->getTotal()).c_str());
        }

        EndTable();
    }

    // for (size_t i = 0; i < users.size(); i++) {
    //     // List Everyones names
    //     sf::Text peopleNames;
    //     peopleNames.setFont(notoSans);
    //     peopleNames.setPosition(USER_TOTAL_X + (USER_SPACING_X * i), ITEM_Y_SPACING * (items.size() + 2) + NAME_START_Y);
    //     peopleNames.setCharacterSize(FONT_SIZE);
    //     peopleNames.setString(users[i]->getName());
    //     itemDrawObjects.push_back(peopleNames);

    //     // Below each name, print their total price
    //     sf::Text peopleTotals;
    //     peopleTotals.setFont(notoSans);
    //     peopleTotals.setPosition(USER_TOTAL_X + (USER_SPACING_X * i), ITEM_Y_SPACING * (items.size() + 2) + NAME_START_Y + USER_SPACING_Y);
    //     peopleTotals.setCharacterSize(FONT_SIZE);
    //     UserTotalUpdateObjects.push_back(peopleTotals);
    // }

    ImGui::PopFont();

    End();
}
