//
// Created by Jerry Mao on 2021-11-08.
//
#include <string>

#ifndef GROUP23_KITCHENWARE_H
#define GROUP23_KITCHENWARE_H

using namespace std;

/**
 * @brief This class represents the kitchenware inventory, it contains an kitchenware id and a kitchenware name
 */
class Kitchenware {
private:
    string kitchenware_id;
    string kitchenware_name;

public:
    Kitchenware(string kitchenware_idP, string kitchenware_nameP);
    ~Kitchenware();
    string get_kitchenware_id();
    void set_kitchenware_id(string kitchenware_idP);
    string get_kitchenware_name();
    void set_kitchenware_name(string new_kitchenware_name);

};


#endif //CS3307_GROUP_KITCHENWARE_H
