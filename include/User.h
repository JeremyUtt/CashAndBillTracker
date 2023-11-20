#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <Item.h>
class User
{
private:
    std::string name_;
    bool isBuyer_;
    std::vector<Item*> items_;
public:
    User();
    User(std::string name, bool isBuyer);
    void addItem(Item* item);
    void removeItem(Item* item);
    int calcuateTotal();
    void setName(std::string name);
    std::string getName();
    void setBuyerStatus(bool isBuyer);
    bool getBuyerStatus();
    std::vector<Item*> getAddedItems();
};

#endif