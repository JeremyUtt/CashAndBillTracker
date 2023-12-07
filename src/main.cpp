#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Button.h"
#include "Item.h"
#include "User.h"
#include "layout.h"
using namespace std;

void renderWindow(vector<User*>& users, vector<Item*>& items);
void handleEvents(sf::RenderWindow& window, vector<Button*> buttons, vector<ButtonLink> buyTable);

void userToggleButton(Button* button, ButtonLink& link) {
    auto color1 = sf::Color(BUTTON_COLOR_OFF);
    auto color2 = sf::Color(BUTTON_COLOR_ON);

    // auto color1 = sf::Color(0x227335ff);
    // auto color2 = sf::Color(0xa60d2cff);

    if (button->getColor() == color1) {
        button->setColor(color2);
        link.item->removeUser(link.user);

    } else {
        button->setColor(color1);
        link.item->addUser(link.user);
    }
}

int main() {
    vector<Item*> items;
    vector<User*> users;

    cout << "Enter name of person Buying: ";
    string name;
    cin >> name;
    User* buyer = new User(name, true);
    users.push_back(buyer);
    while (true) {
        cout << "Enter next users name: (or q to quit)";
        cin >> name;
        if (name == "q") {
            break;
        }

        User* user = new User(name, false);
        users.push_back(user);
    }

    while (true) {
        cout << "Enter Name of Product (or q to quit):";
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

        for (size_t i = 0; i < users.size(); i++) {
            cout << "is User " << users[i]->getName() << " Buying this: ";
            cin >> input;
            if (input == "y" || input == "Y") {
                // item->addUser(users[i]);
            }
        }
    }

    for (size_t i = 0; i < items.size(); i++) {
        auto addedUsers = items[i]->getAddedUsers();
        auto price = items[i]->pricePerPerson();
        for (size_t j = 0; j < addedUsers.size(); j++) {
            addedUsers[j]->setTotal(addedUsers[j]->getTotal() + price);
        }
    }

    for (size_t i = 0; i < users.size(); i++) {
        cout << users[i]->getName() << ": " << users[i]->getTotal() << endl;
    }

    renderWindow(users, items);
    return 0;
}

void renderWindow(vector<User*>& users, vector<Item*>& items) {
    // Create Buttons array
    vector<Button*> buttons;

    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Cost and Bill Tracker");

    // Load Text Font
    sf::Font notoSans;
    if (!notoSans.loadFromFile("/home/jeremy/Dev/CBT/NotoSans-Bold.ttf")) {
        exit(-1);
    }

    // Create Title Text
    sf::Text titleScreenText;
    titleScreenText.setFont(notoSans);
    titleScreenText.setString("Cost and Bill Tracker");
    titleScreenText.setFillColor(sf::Color::White);
    titleScreenText.setCharacterSize(30);
    titleScreenText.setPosition(20, 20);

    // Created Buy table for what buttons are associated to what item and user
    // only the toggle buttons for adding items to a users cart should be added to this table
    vector<ButtonLink> buyTable;

    // Interface for all items to buy
    vector<sf::Text> itemDrawObjects;

    // For each item
    for (size_t i = 0; i < items.size(); i++) {
        // Create Text Object
        sf::Text itemText;
        itemText.setFont(notoSans);
        itemText.setString(items[i]->getName());
        itemText.setPosition(LEFT_OFFSET, ITEM_Y_SPACING * i + ITEM_Y_SPACING + TOP_OFFSET);
        itemDrawObjects.push_back(itemText);

        // Create Button Object
        for (size_t j = 0; j < users.size(); j++) {
            Button* userButton = new Button(BUTTON_START_X + BUTTON_X_SPACING * j,
                                            ITEM_Y_SPACING * i + ITEM_Y_SPACING + TOP_OFFSET,
                                            BUTTON_WIDTH,
                                            BUTTON_HEIGHT,
                                            userToggleButton);
            userButton->setText(users[j]->getName(), notoSans, 25);
            userButton->setColor(sf::Color(BUTTON_COLOR_OFF));
            ButtonLink link;
            link.item = items[i];
            link.user = users[j];

            buyTable.push_back(link);
            buttons.push_back(userButton);
        }
    }

    while (window.isOpen()) {
        handleEvents(window, buttons, buyTable);
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

        window.display();
        sf::sleep(sf::milliseconds(50));
    }
    // delete[] buyTable;
}

void handleEvents(sf::RenderWindow& window, vector<Button*> buttons, vector<ButtonLink> buyTable) {
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
                        if (buttons.at(i)->updateHoverStatus(event.mouseButton.x, event.mouseButton.y)) {
                            buttons.at(i)->callFunc(buyTable[i]);
                        }
                    }
                }
                break;

            case sf::Event::MouseMoved:
                // cout << "Hello world" << endl;
                for (size_t i = 0; i < buttons.size(); i++) {
                    buttons.at(i)->updateHoverStatus(event.mouseMove.x, event.mouseMove.y);
                }
                break;

            case sf::Event::Resized:
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
