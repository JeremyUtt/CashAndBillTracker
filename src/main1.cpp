// #include <GLFW/glfw3.h>
// #include <stdio.h>

// #include <fstream>
// #include <iomanip>
// #include <iostream>
// #include <sstream>

// #include "imgui.h"
// #include "imgui_impl_glfw.h"
// #include "imgui_impl_opengl3.h"
// #include "layout.h"
// #include "main.h"
// // #define STB_IMAGE_IMPLEMENTATION

// // #include "stb_image.h"
// using namespace std;

// const char* title = "Application title";
// const int width = 1280;
// const int height = 720;

// void app(GLFWwindow* window);

// int main() {
//     vector<Item*> items;
//     vector<User*> users;

//     // Ask user for type of data input
//     while (true) {
//         cout << "How would you like in input the data?" << endl;
//         cout << "1. A CSV File, 2. Manually (1,2):";
//         int choice;
//         cin >> choice;
//         // Check id wrong datatype entered (or other failure)
//         if (cin.fail()) {
//             cin.clear();
//             cout << "Invalid choice" << endl;
//             continue;
//         }
//         if (choice == 1) {
//             // function will modify the users and items vector
//             readCSV(users, items);
//             break;
//         } else if (choice == 2) {
//             // function will modify the users and items vector
//             readManual(users, items);
//             break;
//         } else {
//             cout << "Invalid choice" << endl;
//         }
//     }

//     if (!glfwInit()) {
//         return 1;
//     }

//     GLFWwindow* window = glfwCreateWindow(width, 720, title, nullptr, nullptr);
//     if (window == nullptr) {
//         return 1;
//     }

//     glfwMakeContextCurrent(window);
//     glfwSwapInterval(1);  // Enable vsync

//     // int width, height, channels;
//     // unsigned char* pixels = stbi_load("/home/jeremy/Dev/ImGuiTest/icon.png", &width, &height, &channels, 4);

//     // GLFWimage images[1];
//     // images[0].width = width;
//     // images[0].height = height;
//     // images[0].pixels = pixels;
//     // glfwSetWindowIcon(window, 1, images);

//     ImGui::CreateContext();
//     ImGui::StyleColorsDark();

//     ImGui_ImplGlfw_InitForOpenGL(window, true);
//     ImGui_ImplOpenGL3_Init("#version 130");

//     ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

//     while (!glfwWindowShouldClose(window)) {
//         glfwPollEvents();

//         // Start the Dear ImGui frame
//         ImGui_ImplOpenGL3_NewFrame();
//         ImGui_ImplGlfw_NewFrame();
//         ImGui::NewFrame();

//         app(window);

//         ImGui::Render();
//         int display_w, display_h;
//         glfwGetFramebufferSize(window, &display_w, &display_h);
//         glViewport(0, 0, display_w, display_h);

//         glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
//         glClear(GL_COLOR_BUFFER_BIT);
//         ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

//         glfwSwapBuffers(window);
//     }

//     ImGui_ImplOpenGL3_Shutdown();
//     ImGui_ImplGlfw_Shutdown();
//     ImGui::DestroyContext();

//     glfwDestroyWindow(window);
//     glfwTerminate();
// }

// void app(GLFWwindow* window) {
//     using namespace ImGui;

//     Begin("Fullscreen Window",
//           NULL,
//           ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar |
//               ImGuiWindowFlags_NoBringToFrontOnFocus);

//     Text("Fullscreen window Text");

//     int width, height;
//     glfwGetWindowSize(window, &width, &height);

//     SetWindowSize(ImVec2(width, height));
//     SetWindowPos(ImVec2(0, 0));
//     End();

//     Begin("Normal Window");

//     Text("Hello World!");

//     End();
// }