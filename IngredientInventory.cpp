/**
 * @brief This class represents the ingredient Inventory of the user, it contains an unordered map with ingredient id and amount
 * @author Xingjian Mao
 * @date 2021/11/30
 */
#include "IngredientInventory.h"
#include <unordered_map>

using namespace std;

/**
 * @brief This is the constructor of the class, it receives an unordered map links ingredient id and its amount
 * @param new_ingredients unordered map links ingredient id and its amount
 */
IngredientInventory::IngredientInventory(std::unordered_map<std::string, int> new_ingredients){
    ingredients = new_ingredients;
}

/**
 * De-constructor for the object
 */
IngredientInventory::~IngredientInventory()= default;;

/**
 * @brief This class gets the ingredient amount of the inventory
 * @param ingredient_id represents the ingredient id
 * @return int represents the amount of the ingredient
 */
int IngredientInventory::get_ingredient_amount(std::string ingredient_id){
    return ingredients.at(ingredient_id);
}

/**
 * @brief This class sets the ingredient amount of the inventory
 * @param ingredient_id String represents the ingredient id
 * @param amountP represents the amount
 */
void IngredientInventory::set_ingredient_amount(string ingredient_id, int amountP){

    ingredients[ingredient_id] = amountP;

}

/**
 * @brief This class returns the unordered map contains ingredients and their corresponding amount
 * @return unordered map contains ingredients and their corresponding amount
 */
unordered_map<string, int> IngredientInventory::get_all_inventory() {
    return ingredients;
}
