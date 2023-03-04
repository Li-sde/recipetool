/**
 * @brief This class represents the kitchenware inventory, it contains an kitchenware id and a kitchenware name
 * @author Xingjian Mao
 * @date 2021/11/30
 */
#include "Kitchenware.h"
#include <string>

using namespace std;
/**
 * @brief This method is the constructor, it sets the id and the name of the kitchenware
 * @param kitchenware_idP ID of the kitchenware
 * @param kitchenware_nameP Name of the kitchenware
 * @date 2021/11/30
 */
Kitchenware::Kitchenware(string kitchenware_idP, string kitchenware_nameP) {
    kitchenware_id = kitchenware_idP;
    kitchenware_name = kitchenware_nameP;
}

/**
 * @brief De-constructor for this class
 */
Kitchenware::~Kitchenware()= default;


/**
 * @brief This method returns the kitchenware id
 * @return string represents ktichenware id
 */
string Kitchenware::get_kitchenware_id(){
    return kitchenware_id;
}


/**
 * @brief This method sets the kitchenware id
 * @param String represents kitchenware ID
 */
void Kitchenware::set_kitchenware_id(string kitchenware_idP) {
    kitchenware_id = kitchenware_idP;
}


/**
 * @brief method returns the kitchenware name
 * @return string represents kitchenware name
 */
string Kitchenware::get_kitchenware_name(){
    return kitchenware_name;
}


/**
 * @brief This method sets the kitchenware name
 * @param new_kitchenware_name string represents kitchenware name
 */
void Kitchenware::set_kitchenware_name(string new_kitchenware_name) {
    kitchenware_name = new_kitchenware_name;
}