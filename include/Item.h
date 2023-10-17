#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item
{
private:
    int barcode;
    std::string name;
    float pricePerQuantity;
    int quantity;
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
};


#endif