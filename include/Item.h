#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

#include "User.h"
class Item {
private:
    int _barcode;
    std::string _name;
    float _pricePerQuantity;
    int _quantity;
    std::vector<User*> _users;

public:
    // Constructor
    Item(std::string name, float pricePerQuantity, int quantity);

    // Getters/Setters
    void setBarcode(int barcode);
    int getBarcode() const;
    void setName(std::string name);
    std::string getName() const;
    void setPricePerQuantity(float pricePerQuantity);
    float getPricePerQuantity() const;
    void setQuantity(int quantity);
    int getQuantity() const;

    // "Complex" methods
    float getTotalPrice() const;
    void addUser(User* user);
    void removeUser(User* user);
    std::vector<User*> getAddedUsers() const;
    double pricePerPerson() const;
    // void updateUserTotals();
};

#endif