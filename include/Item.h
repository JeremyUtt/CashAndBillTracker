#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "User.h"
class Item
{
private:
    int barcode;
    std::string name;
    float pricePerQuantity;
    int _quantity;
    std::vector<User*> _users;
public:
    // Construstor
    Item(std::string name, float pricePerQuantity, int quantity);
    
    // Getters/Setters
    void setBarcode(int barcode);
    int getBarcode();
    void setName(std::string name);
    std::string getName();
    void setPricePerQuantity(float pricePerQuantity);
    float getPricePerQuantity();
    void setQuantity(int quantity);
    int getQuantity();
    
    // "Complex" methods
    float getTotalPrice();  
    void addUser(User* user);
    void removeUser(User* user);
    std::vector<User*> getAddedUsers();
    double pricePerPerson();
    // void updateUserTotals();

};


#endif