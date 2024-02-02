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

#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "layout.h"
using namespace std;

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
    renderWindow(users, items);
    return 0;
}

void readCSV(vector<User*>& users, vector<Item*>& items) {
    // Prompt user for file name
    cout << "Enter Filename:";
    string fileName;
    cin >> fileName;

    ifstream file(fileName);
    if(file.fail()){
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

void renderWindow(vector<User*>& users, vector<Item*>& items) {
    // Create Buttons array
    vector<Button*> buttons;

    // https://www.sfml-dev.org/documentation/2.6.1/
    sf::RenderWindow window(sf::VideoMode(1920, 1080, 32), "Cost and Bill Tracker");

    // Load Text Font
    sf::Font notoSans;
    if (!notoSans.loadFromFile("NotoSans-Bold.ttf")) {
        exit(-1);
    }

    // Create Title Text
    sf::Text titleScreenText;
    titleScreenText.setFont(notoSans);
    titleScreenText.setString("Cost and Bill Tracker");
    titleScreenText.setFillColor(sf::Color::White);
    titleScreenText.setCharacterSize(30);
    titleScreenText.setPosition(LEFT_OFFSET, TOP_OFFSET);

    // Create Buy table for what buttons are associated to what item and user
    // only the toggle buttons for adding items to a users cart should be added to this list
    vector<ButtonLink> buyTable;

    // Interface for all items to buy
    // these vectors will be looped over in the draw loop to render
    vector<sf::Text> itemDrawObjects;
    vector<sf::Text> itemUpdateObjects;
    vector<sf::Text> UserTotalUpdateObjects;

    // Add header for graphical table
    const vector<string> tags = {"Name:", "Total:", "Users: (Select one or more per item)", "Price Per Person:"};
    const vector<int> xPositions = {NAME_START_X, TOTAL_START_X, BUTTON_START_X, BUTTON_START_X + ITEM_X_SPACING + (int)users.size() * (ITEM_X_SPACING + BUTTON_WIDTH)};
    for (size_t i = 0; i < 4; i++) {
        sf::Text tagText;
        tagText.setFont(notoSans);
        tagText.setString(tags[i]);
        tagText.setPosition(xPositions[i], TOP_OFFSET + ITEM_Y_SPACING);
        tagText.setCharacterSize(FONT_SIZE);
        itemDrawObjects.push_back(tagText);
    }

    // Repeat for every item in the list
    for (size_t i = 0; i < items.size(); i++) {
        // Create Name coloum
        sf::Text nameText;
        nameText.setFont(notoSans);
        nameText.setString(items[i]->getName());
        nameText.setPosition(NAME_START_X, ITEM_Y_SPACING * (i + 1) + NAME_START_Y);
        nameText.setCharacterSize(FONT_SIZE);
        itemDrawObjects.push_back(nameText);

        // Create Total (2nd) coloum
        sf::Text totalText;
        totalText.setFont(notoSans);
        totalText.setString(fltToStr(items[i]->getTotalPrice()));
        totalText.setPosition(TOTAL_START_X, ITEM_Y_SPACING * (i + 1) + NAME_START_Y);
        totalText.setCharacterSize(FONT_SIZE);
        itemDrawObjects.push_back(totalText);

        // Create Button Objects
        for (size_t j = 0; j < users.size(); j++) {
            Button* userButton = new Button(BUTTON_START_X + (ITEM_X_SPACING + BUTTON_WIDTH) * j,
                                            ITEM_Y_SPACING * (i + 1) + NAME_START_Y,
                                            BUTTON_WIDTH,
                                            BUTTON_HEIGHT,
                                            userToggleButton);
            userButton->setText(users[j]->getName(), notoSans, FONT_SIZE);
            userButton->setColor(sf::Color(BUTTON_COLOR_OFF));
            ButtonLink link;
            link.item = items[i];
            link.user = users[j];

            buyTable.push_back(link);
            buttons.push_back(userButton);
        }

        // Create Price Per Person (last) coloum
        sf::Text pppText;
        pppText.setFont(notoSans);
        pppText.setPosition((BUTTON_WIDTH + ITEM_X_SPACING) * users.size() + ITEM_X_SPACING + BUTTON_START_X, ITEM_Y_SPACING * (i + 1) + NAME_START_Y);
        pppText.setCharacterSize(FONT_SIZE);
        itemUpdateObjects.push_back(pppText);
    }

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
    }
}

void handleEvents(sf::RenderWindow& window, vector<Button*> buttons, vector<ButtonLink> buyTable, vector<User*>& users, vector<Item*>& items) {
    sf::Event event;
    while (window.pollEvent(event)) {
        sf::FloatRect visibleArea;
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (size_t i = 0; i < buttons.size(); i++) {
                        // if button is clicked on, call its assisiated function
                        if (buttons.at(i)->updateHoverStatus(event.mouseButton.x, event.mouseButton.y)) {
                            buttons.at(i)->callFunc(buyTable[i]);

                            // Update User Totals
                            updateTotals(users, items);
                        }
                    }
                }
                break;

            case sf::Event::MouseMoved:
                for (size_t i = 0; i < buttons.size(); i++) {
                    // changes border color of buttons when hovered over
                    buttons.at(i)->updateHoverStatus(event.mouseMove.x, event.mouseMove.y);
                }
                break;

            case sf::Event::Resized:
                // this prevented the window from stretching contents when resized
                visibleArea.left = 0;
                visibleArea.top = 0;
                visibleArea.width = event.size.width;
                visibleArea.height = event.size.height;
                window.setView(sf::View(visibleArea));
                break;

            default:
                break;
        }
    }
}

void userToggleButton(Button* button, ButtonLink& link) {
    // this will be called by individual buttons when clicked

    // define colors for clicked and unclicked
    auto color1 = sf::Color(BUTTON_COLOR_OFF);
    auto color2 = sf::Color(BUTTON_COLOR_ON);

    // use the color of the button to determine its 'state'
    if (button->getColor() == color1) {
        button->setColor(color2);
        link.item->addUser(link.user);

    } else {
        button->setColor(color1);
        link.item->removeUser(link.user);
        // price *= -1;
    }
}

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