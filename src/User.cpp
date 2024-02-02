#include "User.h"

#include "Item.h"

User::User(std::string name, bool isBuyer) {
    this->_name = name;
    this->_isBuyer = isBuyer;
    this->_currentTotal = 0;
}

void User::setName(std::string name) {
    this->_name = name;
}

std::string User::getName() const {
    return _name;
}

void User::setBuyerStatus(bool isBuyer) {
    this->_isBuyer = isBuyer;
}

bool User::getBuyerStatus() const {
    return _isBuyer;
}

void User::setTotal(double total) {
    this->_currentTotal = total;
}

double User::getTotal() const {
    return this->_currentTotal;
}