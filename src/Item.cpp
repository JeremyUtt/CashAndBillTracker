#include "Item.h"

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
    return name;
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
