#include "User.h"
#include "Item.h"
User::User() {
}

User::User(std::string name, bool isBuyer) {
    this->name_ = name;
    this->isBuyer_ = isBuyer;
}

void User::addItem(Item* item) {
    items_.push_back(item);
}

void User::removeItem(Item* item) {
    // items.erase(5);
}

int User::calcuateTotal() {
    int sum;
    for (size_t i = 0; i < items_.size(); i++)
    {
        sum += items_[i]->getTotalPrice();
    }
    return sum;
}

void User::setName(std::string name) {
    this->name_ = name;
}

std::string User::getName() {
    return name_;
}

void User::setBuyerStatus(bool isBuyer) {
    this->isBuyer_ = isBuyer;
}

bool User::getBuyerStatus() {
    return isBuyer_;
}

std::vector<Item* > User::getAddedItems() {
    return items_;
}

