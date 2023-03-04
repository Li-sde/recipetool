//
// Created by Jerry Mao on 2021-11-09.
//

#ifndef GROUP23_INGREDIENTINVENTORY_H
#define GROUP23_INGREDIENTINVENTORY_H
#include <string>
#include <unordered_map>

using namespace std;

/**
 * @brief This class represents the ingredient Inventory of the user, it contains an unordered map with ingredient id and amount
 */
class IngredientInventory {
private:
    unordered_map<string, int> ingredients;
public:
    IngredientInventory(unordered_map<std::string, int> new_ingredients);
    ~IngredientInventory();
    int get_ingredient_amount(string ingredient_id);
    void set_ingredient_amount(string ingredient_id, int amount);
    unordered_map<string, int> get_all_inventory();
};


#endif //GROUP23_INGREDIENTINVENTORY_H
