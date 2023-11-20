#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Button.h"
#include "Item.h"
#include "User.h"
using namespace std;

void renderWindow();
void handleEvents(sf::RenderWindow& window, vector<Button*> buttons);

void testing() {
    cout << "Hello world!" << endl;
}

int main() {
    cout << "Hello World!" << endl;
    vector<Item*> items;
    vector<User*> users;

    Item* coke = new Item;
    coke->setName("Diet Cock");
    coke->setQuantity(69);
    coke->setPricePerQuantity(4.20);
    items.push_back(coke);
    cout << coke->getName() << endl;

    Item realCoke = *coke;
    cout << realCoke.getName() << endl;

    cout << items[0]->getName() << endl;
    cout << items[0]->getTotalPrice() << endl;

    Item drP("Dr Pepper", 5, 50);

    cout << drP.getName() << endl;
    cout << drP.getTotalPrice() << endl;

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
            cout << "is User " << users.at(i)->getName() << " Buying this: ";
            cin >> input;
            if (input == "y" || input == "Y") {
                users.at(i)->addItem(item);
            }
        }
    }

    // for (size_t i = 0; i < items.size(); i++) {
    //     cout << items.at(i)->getName() << endl;
    // }


    for (size_t i = 0; i < users.size(); i++)
    {
        cout << users[i]->getName() << ":" << endl;
        vector<Item*> addedItems = users[i]->getAddedItems();
        for (size_t j = 0; j < addedItems.size(); j++)
        {
            cout << "   " << addedItems[j]->getName() << endl;
        }
    }
    

    renderWindow();
    return 0;
}

void handleEvents(sf::RenderWindow& window, vector<Button*> buttons) {
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
                            buttons.at(i)->callFunc();
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

void renderWindow() {
    vector<Button*> buttons;

    sf::RenderWindow window(sf::VideoMode(1280, 720, 32), "Cost and Bill Tracker");
    sf::View view = window.getDefaultView();

    sf::Font notoSans;
    if (!notoSans.loadFromFile("./NotoSans-Bold.ttf")) {
        exit(-1);
    }

    sf::Text titleScreenText;
    titleScreenText.setFont(notoSans);
    titleScreenText.setString("Cost and Bill Tracker");
    titleScreenText.setFillColor(sf::Color::White);
    titleScreenText.setCharacterSize(30);
    titleScreenText.setPosition(20, 20);
    Button pog(50, 70, 200, 100, testing);

    Button pog2(300, 0, 100, 500, testing);
    pog.setText("Pog", notoSans, 20);
    pog2.setText("Pog2", notoSans, 20);
    buttons.push_back(&pog);
    buttons.push_back(&pog2);

    while (window.isOpen()) {
        handleEvents(window, buttons);
        window.clear(sf::Color(0x181a1b00));
        window.draw(titleScreenText);
        pog.render(window);
        pog2.render(window);
        window.display();
    }
}