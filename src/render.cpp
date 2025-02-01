#include "render.h"

#include <GLFW/glfw3.h>

#include <iostream>

#include "csv.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "logic.h"

using namespace std;


ImFont* font1;
ImFont* font2;
void mainWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items);
void addUserWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items);
void addItemWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items);
string openCSV();

bool incomplete = false;

const vector<string> tags = {"Item", "Price Per", "Quantity", "Total", "Price Per Person:", "Tax", "Tax Per", "Tax Total"};

void loop(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {

    ImGui::PushFont(font2);

    mainWindow(window, users, items);

    ImGui::SetNextWindowPos(ImVec2(250, 350), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(250, 125), ImGuiCond_FirstUseEver);
    addUserWindow(window, users, items);

    ImGui::SetNextWindowPos(ImVec2(700, 350), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(250, 180), ImGuiCond_FirstUseEver);
    addItemWindow(window, users, items);

    ImGui::PopFont();
}

void mainWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
    ImGui::Begin("Fullscreen Window",
          NULL,
          ImGuiWindowFlags_NoResize |
              ImGuiWindowFlags_NoMove |
              ImGuiWindowFlags_NoCollapse |
              ImGuiWindowFlags_NoTitleBar |
              ImGuiWindowFlags_NoBringToFrontOnFocus);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    ImGui::SetWindowSize(ImVec2(width, height));
    ImGui::SetWindowPos(ImVec2(0, 0));

    ImGui::PushFont(font1);
    ImGui::Text("Cost and Bill Tracker");
    ImGui::PopFont();

    if (ImGui::Button("Load From CSV", ImVec2(150, 40))) {
        string result = openCSV();
        if (result != "") {
            users.clear();
            items.clear();
            readCSV(result, users, items);
            updateTotals(users, items);
        }
    }

    if (ImGui::BeginTable("main", tags.size() + users.size(), ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX)) {
        incomplete = false;
        // Create Button Style
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(.6, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(.8, 0, 0, 1));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1, 0, 0, 1));
        
        // Add first 4 column headers
        for (std::size_t i = 0; i < 4; i++) {
            ImGui::TableNextColumn();
            ImGui::TableHeader(tags[i].c_str());
        }
        
        // Add User Column Headers
        for (std::size_t i = 0; i < users.size(); i++) {
            ImGui::TableNextColumn();
            // TableHeader("hi");

            string text = "X##" + users[i]->getName();
            if (ImGui::Button(text.c_str(), ImVec2(25, 25))) {
                cout << "Remove User: " << users[i]->getName() << endl;
                users.erase(users.begin() + i);
                updateTotals(users, items);
            }
            ImGui::SameLine();
            ImGui::Text(users[i]->getName().c_str());
        }
        
        // Add rest of column header
        for (std::size_t i = 4; i < tags.size(); i++) {
            ImGui::TableNextColumn();
            ImGui::TableHeader(tags[i].c_str());
        }

        // Create remaining rows
        for (std::size_t i = 0; i < items.size(); i++) {
            // Create Name coloum

            ImGui::TableNextColumn();
            if (ImGui::Button(("X##item" + to_string(i)).c_str(), ImVec2(25, 25))) {
                cout << "Remove Item: " << items[i]->getName() << endl;
                items.erase(items.begin() + i);
                updateTotals(users, items);
            }
            ImGui::SameLine();
            ImGui::Text(items[i]->getName().c_str());

            // Create Price Per (2nd) column
            ImGui::TableNextColumn();
            ImGui::Text(fltToStr(items[i]->getPricePerQuantity()).c_str());

            // Create Quantity (3rd) column
            ImGui::TableNextColumn();
            ImGui::Text(std::to_string(items[i]->getQuantity()).c_str());

            // Create Total (4th) column
            ImGui::TableNextColumn();
            ImGui::Text(fltToStr(items[i]->getTotalPrice()).c_str());

            vector<User*> usersWithItem = items[i]->getAddedUsers();
            // Create Button Objects
            for (std::size_t j = 0; j < users.size(); j++) {
                ImGui::TableNextColumn();

                string name = users[j]->getName() + "##" + to_string(i * users.size() + j);

                bool checked = false;
                // check if user is in on the item
                for (auto user : usersWithItem) {
                    if (user == users[j]) {
                        checked = true;
                        break;
                    }
                }

                bool clicked = ImGui::Checkbox(name.c_str(), &checked);
                if (clicked) {
                    if (checked) {
                        items[i]->addUser(users[j]);
                    } else {
                        items[i]->removeUser(users[j]);
                    }
                    updateTotals(users, items);
                }
            }

            // Create Price Per Person column
            ImGui::TableNextColumn();
            string text = fltToStr(items[i]->pricePerPerson());
            if (text == "$inf") {
                text = "Select at least one person";
                incomplete = true;
            }
            ImGui::Text(text.c_str());

            // Create Tax button column
            ImGui::TableNextColumn();
            string name = "##" + items[i]->getName();
            // check if tax is applied
            bool checked = false;
            if (items[i]->hasTax()) {
                checked = true;
            }
            bool clicked = ImGui::Checkbox(name.c_str(), &checked);
            if (clicked) {
                items[i]->setTax(checked);
                updateTotals(users, items);
            }

            // Create Tax Per Person column
            ImGui::TableNextColumn();
            text = fltToStr(items[i]->taxPerPerson());
            if (text == "$inf") {
                text = "Select at least one person";
            }
            ImGui::Text(text.c_str());

            // Create Tax Total column
            ImGui::TableNextColumn();
            ImGui::Text(fltToStr(items[i]->getTax()).c_str());




        }
        
        ImGui::EndTable();

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
    }


    // Create section that will contain each users total cost
    if (ImGui::BeginTable("totals", 2 + users.size(), ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoHostExtendX)) {
        
        if (incomplete) {
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0, 0, 1));
        }

        float subtotal = 0;
        float tax = 0;
        float total = 0;
        
        for (auto item : items) {
            subtotal += item->getTotalPrice();
            total += item->getTotalPrice();
            if (item->hasTax()) {
                tax += item->getTax();
                total += item->getTax();
            }
        }
        
        ImGui::TableNextColumn();

        ImGui::TableHeader("User:");
        for (auto user : users) {
            ImGui::TableNextColumn();
            ImGui::TableHeader(user->getName().c_str());
        }
        ImGui::TableNextColumn();
        ImGui::TableHeader("Total");
        ImGui::TableNextColumn();
        
        ImGui::Text("Sub Total:");
        for (auto user : users) {
            ImGui::TableNextColumn();
            ImGui::Text(fltToStr(user->getSubTotal()).c_str());
        }
        ImGui::TableNextColumn();
        ImGui::Text(fltToStr(subtotal).c_str());
        ImGui::TableNextColumn();

        ImGui::Text("Tax:");
        for (auto user : users) {
            ImGui::TableNextColumn();
            ImGui::Text(fltToStr(user->getTax()).c_str());
        }
        ImGui::TableNextColumn();
        ImGui::Text(fltToStr(tax).c_str());
        ImGui::TableNextColumn();
        
        ImGui::Text("Total:");
        for (auto user : users) {
            ImGui::TableNextColumn();
            ImGui::Text(fltToStr(user->getSubTotal() + user->getTax()).c_str());
        }
        ImGui::TableNextColumn();
        ImGui::Text(fltToStr(total).c_str());
        ImGui::EndTable();

        if (incomplete) {
            ImGui::PopStyleColor();
        }
    }

    ImGui::End();
}

void addUserWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
    ImGui::Begin("Add User", NULL, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

    static char name[100];

    ImGui::InputText("Name", name, 100);

    if (ImGui::Button("Add User", ImVec2(100, 40)) && name[0] != '\0') {
        cout << "Add User: " << name << endl;

        users.push_back(new User(name, false));
        updateTotals(users, items);

        for (std::size_t i = 0; i < 100; i++) {
            name[i] = '\0';
        }
    }

    ImGui::End();
}

void addItemWindow(GLFWwindow* window, vector<User*>& users, vector<Item*>& items) {
    ImGui::Begin("Add Item", NULL, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

    static char name[100];
    static float price;
    static int quantity = 1;

    ImGui::InputText("Name", name, 100);
    ImGui::InputFloat("Price", &price);
    ImGui::InputInt("Quantity", &quantity);

    if (ImGui::Button("Add Item", ImVec2(100, 40)) && name[0] != '\0' && quantity > 0 && price > 0) {
        cout << "Add Item: " << name << endl;
        items.push_back(new Item(name, price, quantity));
        updateTotals(users, items);

        for (std::size_t i = 0; i < 100; i++) {
            name[i] = '\0';
            price = 0;
            quantity = 1;
        }
    }

    ImGui::End();
}
