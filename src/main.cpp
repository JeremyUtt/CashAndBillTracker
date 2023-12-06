#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Button.h"
#include "Item.h"
#include "User.h"
#include "UserButton.h"
using namespace std;

void renderWindow(vector<User*>& users, vector<Item*>& items);
void handleEvents(sf::RenderWindow& window, vector<Button*> buttons, ButtonLink buyTable);

void testing() {
    cout << "Hello world!" << endl;
}

void toggleButton(Button* button, ButtonLink link) {
    cout << "Hello world! cbtcbrtcbtbf" << endl;

    auto color1 = sf::Color(0x227335ff);
    auto color2 = sf::Color(0xa60d2cff);
    if (button->getColor() == color1) {
        button->setColor(color2);
        if(link.item != nullptr && link.user != nullptr){
            link.item->removeUser(link.user);
        }
    } else {
        button->setColor(color1);
        if(link.item != nullptr && link.user != nullptr){
            link.item->addUser(link.user);
        }
    }


}

int main() {
    cout << "Hello World!" << endl;
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
                item->addUser(users[i]);
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

void handleEvents(sf::RenderWindow& window, vector<Button*> buttons, ButtonLink* buyTable) {
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




void renderWindow(vector<User*>& users, vector<Item*>& items) {
    vector<Button*> buttons;
    
    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Cost and Bill Tracker");
    sf::View view = window.getDefaultView();

    sf::Font notoSans;
    if (!notoSans.loadFromFile("/home/jeremy/dev/gitted/CBT/NotoSans-Bold.ttf")) {
        exit(-1);
    }

    sf::Text titleScreenText;
    titleScreenText.setFont(notoSans);
    titleScreenText.setString("Cost and Bill Tracker");
    titleScreenText.setFillColor(sf::Color::White);
    titleScreenText.setCharacterSize(30);
    titleScreenText.setPosition(20, 20);
    // Button pog(50, 70, 200, 100, testing);

    // Button pog2(300, 0, 100, 500, testing);
    // pog.setText("Pog", notoSans, 20);
    // pog2.setText("Pog2", notoSans, 20);
    // buttons.push_back(&pog);
    // buttons.push_back(&pog2);

    #define TEXT_SPACING 50
    vector<sf::Text> itemDrawObjects;

    // Created Buy table for what buttons are associated to what item and user
    ButtonLink* buyTable = new ButtonLink[items.size()];


    for (int i = 0; i < items.size(); i++) {
        // Create Text Object
        sf::Text itemText;
        itemText.setFont(notoSans);
        itemText.setString(items[i]->getName());
        itemText.setPosition(20, TEXT_SPACING * i + TEXT_SPACING + 20);
        itemDrawObjects.push_back(itemText);


        // Create Button Object
        for (size_t j = 0; j < users.size(); j++) {
            Button* userButton = new Button(200 + 150 * j, TEXT_SPACING * i + TEXT_SPACING + 20, 120, 50, toggleButton);
            userButton->setText(users[j]->getName(), notoSans, 25);
            userButton->setColor(sf::Color(0xa60d2cff));
            ButtonLink link;
            link.item = items[i];
            link.user = users[j];
            
            buyTable[buttons.size()] = link;
            buttons.push_back(userButton);
        }
    }

    while (window.isOpen()) {
        handleEvents(window, buttons, buyTable);
        window.clear(sf::Color(0x181a1b00));
        window.draw(titleScreenText);

        for (size_t i = 0; i < buttons.size(); i++) {
            buttons[i]->render(window);
        }

        for (size_t i = 0; i < itemDrawObjects.size(); i++) {
            window.draw(itemDrawObjects[i]);
        }

        window.display();
        sf::sleep(sf::milliseconds(50));
    }
    delete[] buyTable;
}