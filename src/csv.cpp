#include <fstream>
#include <iostream>
#include <sstream>

#include "logic.h"
#include "nfd.h"
using namespace std;

void readCSV(string fileName, vector<User*>& users, vector<Item*>& items) {
    ifstream file(fileName);
    if (file.fail()) {
        cerr << "ERROR: File does not exist or is not readable" << endl;
        exit(-1);
    }

    // Read user names from the first line of the file
    // https://favtutor.com/blogs/split-string-cpp
    string names;
    getline(file, names, '\n');
    stringstream nameStream(names);

    // Create User objects based on the names
    // https://stackoverflow.com/questions/10376199/how-can-i-use-non-default-delimiters-when-reading-a-text-file-with-stdfstream
    string uName;
    bool getBuyer = true;
    while (getline(nameStream, uName, ',')) {
        User* buyer = new User(uName, getBuyer);
        getBuyer = false;
        users.push_back(buyer);
    }

    // Read item details from the remaining lines of the file
    string iName, price, quantity;
    while (getline(file, iName, ',')) {
        getline(file, price, ',');
        getline(file, quantity, '\n');

        // https://www.programiz.com/cpp-programming/string-float-conversion
        Item* item = new Item(iName, stof(price), stoi(quantity));
        items.push_back(item);
    }
    file.close();
}

string openCSV() {
    string toReturn;

    NFD_Init();
    nfdu8char_t* outPath;
    nfdu8filteritem_t filter = {"CSV files", "csv"};
    nfdopendialogu8args_t args = {0};
    args.filterList = &filter;
    args.filterCount = 1;
    nfdresult_t result = NFD_OpenDialogU8_With(&outPath, &args);
    if (result == NFD_OKAY) {
        // puts("Success!");
        // puts(outPath);
        toReturn = outPath;
        NFD_FreePathU8(outPath);
    } else if (result == NFD_CANCEL) {
        puts("User pressed cancel.");
    } else {
        printf("Error: %s\n", NFD_GetError());
    }

    NFD_Quit();

    return toReturn;
}