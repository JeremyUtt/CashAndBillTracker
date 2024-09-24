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

#include <fstream>
#include <iostream>
#include <sstream>

#include "csv.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "logic.h"
#include "nfd.h"
#include "render.h"

using namespace std;
using namespace ImGui;

const char* title = "Cost and Bill Tracker";
const int width = 1280;
const int height = 720;
const string fontPath = "/home/jeremy/Dev/CBT/assets/NotoSans-Bold.ttf";
const int titleFontSize = 25;
const int fontSize = 20;

int main(int argc, char** argv) {
    vector<Item*> items;
    vector<User*> users;

    NFD_Init();
    NFD_Quit();

    // Ask user for type of data input
    if (argc == 2) {
        readCSV(argv[1], users, items);
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
    io.IniFilename = nullptr;
    font1 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), titleFontSize);
    font2 = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        loop(window, users, items);

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
