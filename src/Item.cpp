#include "Item.h"

#include <iostream>

Item::Item() {
}

Item::Item(std::string name, float pricePerQuantity, int quantity) {
    this->name = name;
    this->pricePerQuantity = pricePerQuantity;
    this->quantity = quantity;
}

void Item::setBarcode(int barcode) {
    this->barcode = barcode;
}

int Item::getBarcode() {
    return barcode;
}

void Item::setName(std::string name) {
    this->name = name;
}

std::string Item::getName() {
    return this->name;
}

void Item::setPricePerQuantity(float pricePerQuantity) {
    this->pricePerQuantity = pricePerQuantity;
}

float Item::getPricePerQuantity() {
    return pricePerQuantity;
}

void Item::setQuantity(int quantity) {
    this->quantity = quantity;
}

int Item::getQuantity() {
    return quantity;
}

float Item::getTotalPrice() {
    return pricePerQuantity * quantity;
}

void Item::addUser(User* user) {
    users_.push_back(user);
}

void Item::removeUser(User* user) {
    // Search for user to remove
    int index = -1;
    for (size_t i = 0; i < users_.size(); i++) {
        if (users_[i] == user) {
            index = i;
            break;
        }
    }

    // If user found, remove them.
    if (index != -1) {
        users_.erase(users_.begin() + index);
    }
}

std::vector<User*> Item::getAddedUsers() {
    return users_;
}

double Item::pricePerPerson() {
    return getTotalPrice() / users_.size();
}