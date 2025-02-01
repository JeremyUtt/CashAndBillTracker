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

void User::setSubTotal(double total) {
    this->_currentTotal = total;
}

double User::getSubTotal() const {
    return this->_currentTotal;
}

double User::getTax() const {
    return _tax;
}

void User::setTax(double tax) {
    this->_tax = tax;
}