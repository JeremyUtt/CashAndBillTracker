#include "User.h"
#include "Item.h"
User::User() {
}

User::User(std::string name, bool isBuyer) {
}

void User::addItem(Item* item) {
    items.push_back(item);
}

void User::removeItem(Item* item) {
    // items.erase(5);
}

int User::calcuateTotal() {
    int sum;
    for (size_t i = 0; i < items.size(); i++)
    {
        sum += items[i]->getTotalPrice();
    }
    return sum;
}

void User::setName(std::string name) {
    this->name = name;
}

std::string User::getName() {
    return name;
}

void User::setBuyerStatus(bool isBuyer) {
    this->isBuyer = isBuyer;
}

bool User::getBuyerStatus() {
    return isBuyer;
}

std::vector<Item* > User::getAddedItems() {
    return items;
}

