#pragma once
#include <string>
class User {
private:
    std::string _name;
    bool _isBuyer;
    double _currentTotal;
    double _tax;

public:
    User(std::string name, bool isBuyer);
    void setName(std::string name);
    std::string getName() const;
    void setBuyerStatus(bool isBuyer);
    bool getBuyerStatus() const;
    void setSubTotal(double total);
    double getSubTotal() const;
    double getTax() const;
    void setTax(double tax);
};
