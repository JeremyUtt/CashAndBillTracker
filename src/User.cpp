#include "User.h"
#include "Item.h"

User::User(std::string name, bool isBuyer) {
    this->name_ = name;
    this->isBuyer_ = isBuyer;
    this->currentTotal = 0;
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

void User::setTotal(double total){
    this->currentTotal = total;
}

double User::getTotal(){
    return this->currentTotal;
}