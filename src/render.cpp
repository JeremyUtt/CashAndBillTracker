#include "render.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "csv.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "logic.h"

using namespace std;
using namespace ImGui;

ImFont* font1;
ImFont* font2;
void mainWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items);
void addUserWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items);
void addItemWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items);
string openCSV();

const vector<string> tags = {"Name:", "Total:", "Users: (Select one or more per item)", "Price Per Person:"};

void loop(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
    using namespace ImGui;
    PushFont(font2);

    mainWindow(window, users, items);

    SetNextWindowPos(ImVec2(250, 350), ImGuiCond_FirstUseEver);
    SetNextWindowSize(ImVec2(250, 125), ImGuiCond_FirstUseEver);
    addUserWindow(window, users, items);

    SetNextWindowPos(ImVec2(700, 350), ImGuiCond_FirstUseEver);
    SetNextWindowSize(ImVec2(250, 180), ImGuiCond_FirstUseEver);
    addItemWindow(window, users, items);

    PopFont();
}

void mainWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
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

    PushFont(font1);
    Text("Cost and Bill Tracker");
    PopFont();

    if (Button("Load From CSV", ImVec2(150, 40))) {
        string result = openCSV();
        if (result != "") {
            users.clear();
            items.clear();
            readCSV(result, users, items);
            updateTotals(users, items);
        }
    }

    if (BeginTable("main", 3 + users.size(), ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX)) {
        for (std::size_t i = 0; i < 2; i++) {
            TableNextColumn();
            TableHeader(tags[i].c_str());
        }
        PushStyleColor(ImGuiCol_Button, ImVec4(.6, 0, 0, 1));
        PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.8, 0, 0, 1));
        PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0, 0, 1));
        for (std::size_t i = 0; i < users.size(); i++) {
            TableNextColumn();
            // TableHeader("hi");

            string text = "X: " + users[i]->getName();

            if (Button(text.c_str(), ImVec2(100, 25))) {
                cout << "Remove User: " << users[i]->getName() << endl;
                users.erase(users.begin() + i);
                updateTotals(users, items);
            }
        }
        TableNextColumn();
        TableHeader(tags[3].c_str());

        // TableNextRow();

        // Repeat for every item in the list
        for (std::size_t i = 0; i < items.size(); i++) {
            // Create Name coloum

            TableNextColumn();
            if (Button(("X" + to_string(i)).c_str(), ImVec2(25, 25))) {
                cout << "Remove Item: " << items[i]->getName() << endl;
                items.erase(items.begin() + i);
                updateTotals(users, items);
            }
            SameLine();
            Text(items[i]->getName().c_str());

            // Create Total (2nd) coloum
            TableNextColumn();
            Text(fltToStr(items[i]->getTotalPrice()).c_str());

            vector<User*> usersWithItem = items[i]->getAddedUsers();

            // Create Button Objects
            for (std::size_t j = 0; j < users.size(); j++) {
                TableNextColumn();

                string name = users[j]->getName() + "##" + to_string(i * users.size() + j);

                bool checked = false;
                // check if user is in on the item
                for (auto user : usersWithItem) {
                    if (user == users[j]) {
                        checked = true;
                        break;
                    }
                }

                bool clicked = Checkbox(name.c_str(), &checked);
                if (clicked) {
                    if (checked) {
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

    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
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
            ImGui::Text(fltToStr(user->getTotal()).c_str());
        }

        EndTable();
    }

    End();
}

void addUserWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
    Begin("Add User", NULL, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

    static char name[100];

    ImGui::InputText("Name", name, 100);

    if (Button("Add User", ImVec2(100, 40)) && name[0] != '\0') {
        cout << "Add User: " << name << endl;

        users.push_back(new User(name, false));
        updateTotals(users, items);

        for (std::size_t i = 0; i < 100; i++) {
            name[i] = '\0';
        }
    }

    End();
}

void addItemWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
    Begin("Add Item", NULL, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

    static char name[100];
    static float price;
    static int quantity = 1;

    ImGui::InputText("Name", name, 100);
    ImGui::InputFloat("Price", &price);
    ImGui::InputInt("Quantity", &quantity);

    if (Button("Add Item", ImVec2(100, 40)) && name[0] != '\0' && quantity > 0 && price > 0) {
        cout << "Add Item: " << name << endl;
        items.push_back(new Item(name, price, quantity));
        updateTotals(users, items);

        for (std::size_t i = 0; i < 100; i++) {
            name[i] = '\0';
            price = 0;
            quantity = 1;
        }
    }

    End();
}
