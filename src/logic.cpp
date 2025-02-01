#include "logic.h"

#include <iomanip>
#include <sstream>

using namespace std;

string fltToStr(float num) {
    // Converts a float to a string
    // https://www.geeksforgeeks.org/convert-float-to-string-in-cpp/
    stringstream stream;
    stream << "$" << std::fixed << std::setprecision(2) << num;
    return stream.str();
}

void updateTotals(vector<User*>& users, vector<Item*>& items) {
    // recalutates per person totals from scratch
    for (size_t i = 0; i < users.size(); i++) {
        users[i]->setSubTotal(0);
        users[i]->setTax(0);
    }

    for (size_t i = 0; i < items.size(); i++) {
        auto addedUsers = items[i]->getAddedUsers();
        auto price = items[i]->pricePerPerson();
        // For each participating user, add the items pricePerPerson() to their total
        for (size_t j = 0; j < addedUsers.size(); j++) {
            addedUsers[j]->setSubTotal(addedUsers[j]->getSubTotal() + price);
            // tax
            if (items[i]->hasTax()) {
                addedUsers[j]->setTax(addedUsers[j]->getTax() + items[i]->taxPerPerson());
            }
        }
    }

    // Debugging/Redundant Print Statement
    // for (size_t i = 0; i < users.size(); i++) {
    //     cout << users[i]->getName() << ": " << users[i]->getTotal() << endl;
    // }
}