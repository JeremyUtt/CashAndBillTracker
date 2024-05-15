#pragma once
#include <string>
class User {
private:
    std::string _name;
    bool _isBuyer;
    double _currentTotal;

public:
    User(std::string name, bool isBuyer);
    void setName(std::string name);
    std::string getName() const;
    void setBuyerStatus(bool isBuyer);
    bool getBuyerStatus() const;
    void setTotal(double total);
    double getTotal() const;
};
