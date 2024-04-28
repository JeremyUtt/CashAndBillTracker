/* CSCI 200: Final Project: Cost and Bill Tracker
 *
 * Author: Jeremy Utt
 *
 * The program will store a list (in the form of a vector) of purchased items and
 * their prices, allowing each participant to specify whether they are 'in' on any individual item or
 * not. The item information is inputted either through the terminal, or through a csv file input.
 * The all will then open a SFML window where users can make their selections.
 * as users update preferences, the app calculates the amount each individual
 * owes to the person who made the purchases. If multiple users contribute to a single item, the
 * app evenly distributes the cost among them. This project aims to solve the real world problem
 * of me and my roommates splitting the bills after buying groceries.
 *
 * References:
 *
 * https://www.programiz.com/cpp-programming/string-float-conversion
 * https://favtutor.com/blogs/split-string-cpp
 * https://stackoverflow.com/questions/10376199/how-can-i-use-non-default-delimiters-when-reading-a-text-file-with-stdfstream
 * https://www.sfml-dev.org/documentation/2.6.1/
 * https://www.geeksforgeeks.org/convert-float-to-string-in-cpp/
 * https://stackoverflow.com/questions/41959721/passing-function-to-class-in-c
 *
 */

#include "main.h"

#include <GLFW/glfw3.h>
#include <stdio.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "layout.h"
#include <unordered_map>
#include <utility> // for std::pair



using namespace std;
using namespace ImGui;

const char* title = "Application title";
const int width = 1280;
const int height = 720;
ImFont* font1;

struct ButtonLink {
    Item* item;
    User* user;
};


void app(GLFWwindow* window, vector<User*>& users, vector<Item*>& items, bool* buyTable);

int main() {
    vector<Item*> items;
    vector<User*> users;

    // Ask user for type of data input
    while (true) {
        cout << "How would you like in input the data?" << endl;
        cout << "1. A CSV File, 2. Manually (1,2):";
        int choice;
        cin >> choice;
        // Check id wrong datatype entered (or other failure)
        if (cin.fail()) {
            cin.clear();
            cout << "Invalid choice" << endl;
            continue;
        }
        if (choice == 1) {
            // function will modify the users and items vector
            readCSV(users, items);
            break;
        } else if (choice == 2) {
            // function will modify the users and items vector
            readManual(users, items);
            break;
        } else {
            cout << "Invalid choice" << endl;
        }
    }

    bool* buyTable = new bool[users.size() * items.size()];

    std::cout << users.size() * items.size() << std::endl;

    for (size_t i = 0; i < users.size() * items.size(); i++)
    {
        buyTable[i] = false;
        // std::cout << buyTable[i] << std::endl;
    }
    


    if (!glfwInit()) {
        return 1;
    }

    GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) {
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);  // Enable vsync

    // int width, height, channels;
    // unsigned char* pixels = stbi_load("/home/jeremy/Dev/ImGuiTest/icon.png", &width, &height, &channels, 4);

    // GLFWimage images[1];
    // images[0].width = width;
    // images[0].height = height;
    // images[0].pixels = pixels;
    // glfwSetWindowIcon(window, 1, images);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGuiIO& io = ImGui::GetIO();
    font1 = io.Fonts->AddFontFromFileTTF("/home/jeremy/Dev/CBT/NotoSans-Bold.ttf", 20);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        app(window, users, items, buyTable);

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);

        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

const vector<string> tags = {"Name:", "Total:", "Users: (Select one or more per item)", "Price Per Person:"};
void app(GLFWwindow* window, vector<User*>& users, vector<Item*>& items, bool* buyTable) {
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

    ImGui::PushFont(font1);
    Text("Cost and Bill Tracker");

    // Add header for graphical table
    // const vector<int> xPositions = {NAME_START_X, TOTAL_START_X, BUTTON_START_X, BUTTON_START_X + ITEM_X_SPACING + (int)users.size() * (ITEM_X_SPACING + BUTTON_WIDTH)};

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
                
                bool state;

                bool clicked = Checkbox(users[j]->getName().c_str(), &state);
                if (clicked) {
                    std::cout << "Hi" << std::endl;
                    if (buyTable[i * users.size() + j]) {
                        items[i]->addUser(users[j]);
                    } else {
                        items[i]->removeUser(users[j]);
                    }
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

    ImGui::PopFont();

    End();

    /*
    vector<ButtonLink> buyTable;



    // Create section that will contain each users total cost
    for (size_t i = 0; i < users.size(); i++) {
        // List Everyones names
        sf::Text peopleNames;
        peopleNames.setFont(notoSans);
        peopleNames.setPosition(USER_TOTAL_X + (USER_SPACING_X * i), ITEM_Y_SPACING * (items.size() + 2) + NAME_START_Y);
        peopleNames.setCharacterSize(FONT_SIZE);
        peopleNames.setString(users[i]->getName());
        itemDrawObjects.push_back(peopleNames);

        // Below each name, print their total price
        sf::Text peopleTotals;
        peopleTotals.setFont(notoSans);
        peopleTotals.setPosition(USER_TOTAL_X + (USER_SPACING_X * i), ITEM_Y_SPACING * (items.size() + 2) + NAME_START_Y + USER_SPACING_Y);
        peopleTotals.setCharacterSize(FONT_SIZE);
        UserTotalUpdateObjects.push_back(peopleTotals);
    }

    // Start main draw loop
    while (window.isOpen()) {
        handleEvents(window, buttons, buyTable, users, items);
        window.clear(sf::Color(BACKGROUND_COLOR));
        window.draw(titleScreenText);

        // Draw all Item Names
        for (size_t i = 0; i < itemDrawObjects.size(); i++) {
            window.draw(itemDrawObjects[i]);
        }

        // Draw All Buttons
        for (size_t i = 0; i < buttons.size(); i++) {
            buttons[i]->render(window);
        }

        // Draw some text items that values will update over time
        for (size_t i = 0; i < itemUpdateObjects.size(); i++) {
            string text = fltToStr(items[i]->pricePerPerson());
            if (text == "$inf") {
                text = "Select at least one person";
            }

            itemUpdateObjects[i].setString(text);
            window.draw(itemUpdateObjects[i]);
        }

        // Draw more text items that values will update over time
        for (size_t i = 0; i < UserTotalUpdateObjects.size(); i++) {
            string text = fltToStr(users[i]->getTotal());
            UserTotalUpdateObjects[i].setString(text);
            window.draw(UserTotalUpdateObjects[i]);
        }

        window.display();
        sf::sleep(sf::milliseconds(50));
    } */
}

// void handleEvents(sf::RenderWindow& window, vector<Button*> buttons, vector<ButtonLink> buyTable, vector<User*>& users, vector<Item*>& items) {
//     sf::Event event;
//     while (window.pollEvent(event)) {
//         sf::FloatRect visibleArea;
//         switch (event.type) {
//             case sf::Event::Closed:
//                 window.close();
//                 break;

//             case sf::Event::MouseButtonPressed:
//                 if (event.mouseButton.button == sf::Mouse::Left) {
//                     for (size_t i = 0; i < buttons.size(); i++) {
//                         // if button is clicked on, call its assisiated function
//                         if (buttons.at(i)->updateHoverStatus(event.mouseButton.x, event.mouseButton.y)) {
//                             buttons.at(i)->callFunc(buyTable[i]);

//                             // Update User Totals
//                             updateTotals(users, items);
//                         }
//                     }
//                 }
//                 break;

//             case sf::Event::MouseMoved:
//                 for (size_t i = 0; i < buttons.size(); i++) {
//                     // changes border color of buttons when hovered over
//                     buttons.at(i)->updateHoverStatus(event.mouseMove.x, event.mouseMove.y);
//                 }
//                 break;

//             case sf::Event::Resized:
//                 // this prevented the window from stretching contents when resized
//                 visibleArea.left = 0;
//                 visibleArea.top = 0;
//                 visibleArea.width = event.size.width;
//                 visibleArea.height = event.size.height;
//                 window.setView(sf::View(visibleArea));
//                 break;

//             default:
//                 break;
//         }
//     }
// }

// Good

void readCSV(vector<User*>& users, vector<Item*>& items) {
    // Prompt user for file name
    cout << "Enter Filename:";
    string fileName;
    cin >> fileName;

    ifstream file(fileName);
    if (file.fail()) {
        cerr << "ERROR: File does not exist or is not readable" << endl;
        exit(-1);
    }

    // Read user names from the first line of the file
    // https://favtutor.com/blogs/split-string-cpp
    string names;
    getline(file, names, '\n');
    stringstream nameStream(names);

    // Create User objects based on the names
    // https://stackoverflow.com/questions/10376199/how-can-i-use-non-default-delimiters-when-reading-a-text-file-with-stdfstream
    string uName;
    bool getBuyer = true;
    while (getline(nameStream, uName, ',')) {
        User* buyer = new User(uName, getBuyer);
        getBuyer = false;
        users.push_back(buyer);
    }

    // Read item details from the remaining lines of the file
    string iName, price, quantity;
    while (getline(file, iName, ',')) {
        getline(file, price, ',');
        getline(file, quantity, '\n');

        // https://www.programiz.com/cpp-programming/string-float-conversion
        Item* item = new Item(iName, stof(price), stoi(quantity));
        items.push_back(item);
    }
    file.close();
}

void readManual(vector<User*>& users, vector<Item*>& items) {
    cout << "Enter name of person Buying (one word only): ";
    string name;
    cin >> name;

    User* buyer = new User(name, true);
    users.push_back(buyer);

    // Input other users' names until 'q' is entered
    while (true) {
        cout << "Enter next users name: (one word only)(or q to quit)";
        cin >> name;
        if (name == "q") {
            break;
        }

        User* user = new User(name, false);
        users.push_back(user);
    }

    // Input item details until q is entered
    while (true) {
        cout << "Enter Name of Product (one word only)(or q to quit):";
        string input;
        cin >> input;

        if (input == "q") {
            cout << endl;
            break;
        }

        cout << "Enter Price:";
        double price;
        cin >> price;

        cout << "Enter Quantity:";
        int quantity;
        cin >> quantity;

        Item* item = new Item(input, price, quantity);
        items.push_back(item);
    }
}

// void userToggleButton(Button* button, ButtonLink& link) {
//     // this will be called by individual buttons when clicked

//     // define colors for clicked and unclicked
//     auto color1 = sf::Color(BUTTON_COLOR_OFF);
//     auto color2 = sf::Color(BUTTON_COLOR_ON);

//     // use the color of the button to determine its 'state'
//     if (button->getColor() == color1) {
//         button->setColor(color2);
//         link.item->addUser(link.user);

//     } else {
//         button->setColor(color1);
//         link.item->removeUser(link.user);
//         // price *= -1;
//     }
// }

string fltToStr(float num) {
    // Converts a float to a string
    // https://www.geeksforgeeks.org/convert-float-to-string-in-cpp/
    stringstream stream;
    stream << "$" << std::fixed << std::setprecision(2) << num;
    return stream.str();
}

void updateTotals(vector<User*>& users, vector<Item*>& items) {
    // recalutates per person totals from scratch
    for (size_t i = 0; i < users.size(); i++) {
        users[i]->setTotal(0);
    }

    for (size_t i = 0; i < items.size(); i++) {
        auto addedUsers = items[i]->getAddedUsers();
        auto price = items[i]->pricePerPerson();
        // For each participating user, add the items pricePerPerson() to their total
        for (size_t j = 0; j < addedUsers.size(); j++) {
            addedUsers[j]->setTotal(addedUsers[j]->getTotal() + price);
        }
    }

    // Debugging/Redundant Print Statement
    // for (size_t i = 0; i < users.size(); i++) {
    //     cout << users[i]->getName() << ": " << users[i]->getTotal() << endl;
    // }
}