/**
 * A class to store user's kitchenware inventory
 * @class KitchenwareInventory(std::unordered_map<std::string, int> kitchenwareInventory)
 * @author Donald Cheng Hong Zou
 * @date 2021/11/30
 */

#include "KitchenwareInventory.h"

/**
 * KitchenwareInventory object constructor
 * @brief KitchenwareInventory object constructor
 * @param kitchenwareInventory A unordered map from database
 */
KitchenwareInventory::KitchenwareInventory(std::unordered_map<std::string, int> kitchenwareInventory) {
    this->kitchenware = std::move(kitchenwareInventory);
}

/**
 * Deconstructor
 */
KitchenwareInventory::~KitchenwareInventory() = default;

/**
 * A method to get the kitchenware amount in the inventory
 * @param kitchenware_id A string hold the kitchenware id
 * @return int Amount of the kitchenware
 */
int KitchenwareInventory::get_kitchenware_amount(std::string kitchenware_id) {
    int result;
    try{
        result = this->kitchenware.at(kitchenware_id);
    } catch (std::out_of_range &e){
        result = -1;
    }
    return result;
}

/**
 * A method to set kitchenware amount
 * @brief Set kitchenware amount
 * @param kitchenware_id
 * @param amount
 */
void KitchenwareInventory::set_kitchenware_amount(std::string kitchenware_id, int amount) {
    this->kitchenware[kitchenware_id] = amount;
}

/**
 * A method to get all inventory
 * @brief Get all inventory
 * @return unordered map
 */
std::unordered_map<std::string, int> KitchenwareInventory::get_all_inventory() {
    return this->kitchenware;
}
