#include "Item.h"

#include <iostream>

const float TAX_RATE = 0.18;

Item::Item(std::string name, float pricePerQuantity, int quantity) {
    this->_name = name;
    this->_pricePerQuantity = pricePerQuantity;
    this->_quantity = quantity;
}

void Item::setBarcode(int barcode) {
    this->_barcode = barcode;
}

int Item::getBarcode() const {
    return _barcode;
}

void Item::setName(std::string name) {
    this->_name = name;
}

std::string Item::getName() const {
    return this->_name;
}

void Item::setPricePerQuantity(float pricePerQuantity) {
    this->_pricePerQuantity = pricePerQuantity;
}

float Item::getPricePerQuantity() const {
    return _pricePerQuantity;
}

void Item::setQuantity(int quantity) {
    this->_quantity = quantity;
}

int Item::getQuantity() const {
    return _quantity;
}

float Item::getTotalPrice() const {
    return _pricePerQuantity * _quantity;
}

void Item::addUser(User* user) {
    _users.push_back(user);
}

void Item::removeUser(User* user) {
    // Search for user to remove
    int index = -1;
    for (size_t i = 0; i < _users.size(); i++) {
        if (_users[i] == user) {
            index = i;
            break;
        }
    }

    // If user found, remove them.
    if (index != -1) {
        _users.erase(_users.begin() + index);
    }
}

std::vector<User*> Item::getAddedUsers() const {
    return _users;
}

double Item::pricePerPerson() const {
    return getTotalPrice() / _users.size();
}

bool Item::hasTax() const {
    return _tax;
}

void Item::setTax(bool tax) {
    _tax = tax;
}

float Item::getTax() const {

    if (!_tax) {
        return 0;
    }
    return getTotalPrice() * TAX_RATE;
}

double Item::taxPerPerson() const {
    
    if (!_tax) {
        return 0;
    }

    return getTax() / _users.size();
}