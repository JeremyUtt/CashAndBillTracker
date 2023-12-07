#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
class User {
private:
    std::string name_;
    bool isBuyer_;
    double currentTotal;

public:
    User();
    User(std::string name, bool isBuyer);
    void setName(std::string name);
    std::string getName();
    void setBuyerStatus(bool isBuyer);
    bool getBuyerStatus();
    void setTotal(double total);
    double getTotal();
};

#endif