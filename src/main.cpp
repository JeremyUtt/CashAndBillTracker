#include "main.h"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "layout.h"
using namespace std;

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
    titleScreenText.setPosition(LEFT_OFFSET, TOP_OFFSET);

    // Created Buy table for what buttons are associated to what item and user
    // only the toggle buttons for adding items to a users cart should be added to this table
    vector<ButtonLink> buyTable;

    // Interface for all items to buy
    vector<sf::Text> itemDrawObjects;
    vector<sf::Text> itemUpdateObjects;
    vector<sf::Text> UserTotalUpdateObjects;

    const vector<string> tags = {"Name:", "Total:", "Users: (Select All)", "Price Per Person:"};
    const vector<int> xPositions = {NAME_START_X, TOTAL_START_X, BUTTON_START_X, BUTTON_START_X + ITEM_X_SPACING + (int)users.size() * (ITEM_X_SPACING + BUTTON_WIDTH)};
    for (size_t i = 0; i < 4; i++) {
        sf::Text tagText;
        tagText.setFont(notoSans);
        tagText.setString(tags[i]);
        tagText.setPosition(xPositions[i], TOP_OFFSET + ITEM_Y_SPACING);
        tagText.setCharacterSize(FONT_SIZE);
        itemDrawObjects.push_back(tagText);
    }

    for (size_t i = 0; i < items.size(); i++) {
        // Create Name Object
        sf::Text nameText;
        nameText.setFont(notoSans);
        nameText.setString(items[i]->getName());
        nameText.setPosition(NAME_START_X, ITEM_Y_SPACING * (i + 1) + NAME_START_Y);
        nameText.setCharacterSize(FONT_SIZE);
        itemDrawObjects.push_back(nameText);

        // Create Total
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

        // Create Price Per Person Object
        sf::Text pppText;
        pppText.setFont(notoSans);
        pppText.setPosition((BUTTON_WIDTH + ITEM_X_SPACING) * users.size() + ITEM_X_SPACING + BUTTON_START_X, ITEM_Y_SPACING * (i + 1) + NAME_START_Y);
        pppText.setCharacterSize(FONT_SIZE);
        itemUpdateObjects.push_back(pppText);
    }

    for (size_t i = 0; i < users.size(); i++) {
        sf::Text peopleNames;
        peopleNames.setFont(notoSans);
        peopleNames.setPosition(USER_TOTAL_X + (USER_SPACING_X * i), USER_TOTAL_Y);
        peopleNames.setCharacterSize(FONT_SIZE);
        peopleNames.setString(users[i]->getName());
        itemDrawObjects.push_back(peopleNames);

        sf::Text peopleTotals;
        peopleTotals.setFont(notoSans);
        peopleTotals.setPosition(USER_TOTAL_X + (USER_SPACING_X * i), USER_TOTAL_Y + USER_SPACING_Y);
        peopleTotals.setCharacterSize(FONT_SIZE);
        UserTotalUpdateObjects.push_back(peopleTotals);
    }

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

        for (size_t i = 0; i < itemUpdateObjects.size(); i++) {
            string text = fltToStr(items[i]->pricePerPerson());
            if (text == "inf") {
                text = "Select one or more";
            }

            itemUpdateObjects[i].setString(text);
            window.draw(itemUpdateObjects[i]);
        }

        for (size_t i = 0; i < UserTotalUpdateObjects.size(); i++) {
            string text = fltToStr(users[i]->getTotal());
            UserTotalUpdateObjects[i].setString(text);
            window.draw(UserTotalUpdateObjects[i]);
        }

        window.display();
        sf::sleep(sf::milliseconds(50));
    }
    // delete[] buyTable;
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
                        if (buttons.at(i)->updateHoverStatus(event.mouseButton.x, event.mouseButton.y)) {
                            buttons.at(i)->callFunc(buyTable[i]);

                            // Update User Totals
                            updateTotals(users, items);
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

void userToggleButton(Button* button, ButtonLink& link) {
    auto color1 = sf::Color(BUTTON_COLOR_OFF);
    auto color2 = sf::Color(BUTTON_COLOR_ON);

    // auto price = link.item->pricePerPerson();

    if (button->getColor() == color1) {
        button->setColor(color2);
        link.item->addUser(link.user);

    } else {
        button->setColor(color1);
        link.item->removeUser(link.user);
        // price *= -1;
    }

    // auto addedUsers = link.item->getAddedUsers();
    // for (size_t j = 0; j < addedUsers.size(); j++) {
    //     addedUsers[j]->setTotal(addedUsers[j]->getTotal() + price);
    // }

    // cout << link.user->getName() << ": " << link.user->getTotal() << endl;
}

string fltToStr(float num) {
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << num;
    return stream.str();
}

void updateTotals(vector<User*>& users, vector<Item*>& items) {
    for (size_t i = 0; i < users.size(); i++) {
        users[i]->setTotal(0);
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
}