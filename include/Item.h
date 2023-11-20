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
    int quantity;
    std::vector<User*> users_;
public:
    Item();
    Item(std::string name, float pricePerQuantity, int quantity);
    void setBarcode(int barcode);
    int getBarcode();
    void setName(std::string name);
    std::string getName();
    void setPricePerQuantity(float pricePerQuantity);
    float getPricePerQuantity();
    void setQuantity(int quantity);
    int getQuantity();
    float getTotalPrice();  
    
    void addUser(User* User);
    std::vector<User*> getAddedUsers();
    double pricePerPerson();
};


#endif