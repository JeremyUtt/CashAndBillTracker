#ifndef USER_BUTTON_H
#define USER_BUTTON_H
#include "Button.h"
#include "Item.h"
#include "User.h"

class UserButton : public Button {
    using Button::Button;

private:
    User* _user;
    Item* _item;

public:
    void LinkUserItem(User* user, Item* item);
};
#endif