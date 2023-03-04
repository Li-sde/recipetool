/**
* @brief this class have all function need to create a recipe and all recipe function that usefull
*@author Jiaao Cai
*@date 2021/11/30
*/

#include "recipe.h"

/**
* this class have all function need to create a recipe and all recipe function that usefull
* @param new_recipe_id give id
* @param new_recipe_name give name
* @param new_cuisine new cuisine
* @param new_time_minutes cook time 
* @param new_ingredients add new ingredients
* @param new_procedure add new procedure
*/
recipe::recipe(std::string new_recipe_id, std::string new_recipe_name, std::string new_cuisine,  int new_time_minutes,
               std::unordered_map<std::string,int> new_ingredients,
               std::unordered_map<std::string, int> new_kitchenware, std::unordered_map<std::string, std::vector<std::string>> new_procedure){
    recipe_id = new_recipe_id;
    recipe_name = new_recipe_name;
    time_minutes = new_time_minutes;
    ingredients = new_ingredients;
    kitchenware = new_kitchenware;
    procedure = new_procedure;
    cuisine_type = new_cuisine;
}

/**
 * @brief A de-constructor for this class
 */
recipe::~recipe(){

}

/**
* @return recipe_id ID
*/
std::string recipe::get_recipe_id(){
    return recipe_id;
}

/**
* set a new id
* @param new_recipe_id new id 
*/
void recipe::set_recipe_id(int new_recipe_id){
    recipe_id = new_recipe_id;
}
std::string recipe::get_recipe_name(){
    return recipe_name;
}

/**
* set a new name
* @param new_recipe_name new name
*/
void recipe::set_recipe_name(std::string new_recipe_name){
    recipe_name = new_recipe_name;
}

/**
* @return time_minutes return cook time
*/
int recipe::get_time_minutes(){
    return time_minutes;
}

/**
* set a new cook time
* @param new_time_minutes new cooke time
*/
void recipe::set_time_minutes(int new_time_minutes){
    time_minutes = new_time_minutes;
}

/**
* @return cuisine_type 
*/
std::string recipe::get_cuisine_type(){
    return cuisine_type;
}

/**
* set new cuisine type
* @param new_cuisine_type
*/
void recipe::set_cuisine_type(std::string new_cuisine_type){
    cuisine_type = new_cuisine_type;
}

/**
* @return ingredients 
*/
std::unordered_map<std::string, int> recipe::get_ingredients(){
    return ingredients;
}

/**
* set a new ingredients
* @param new_ingredients 
*/
void recipe::set_ingredients(std::unordered_map<std::string,int> new_ingredients){
    ingredients.insert(new_ingredients.begin(),new_ingredients.end());
}

/**
* @brief ingrediant +1
*  @param ingredient_id witch ingredient
*/
void recipe::increment_ingredient_amount(std::string ingredient_id){
    ingredients[ingredient_id]++;
}

/**
* @brief ingrediant -1
*  @param ingredient_id witch ingredient
*/
void recipe::decrement_ingredient_amount(std::string ingredient_id){
    ingredients[ingredient_id]--;
}

/**
* @brief change ingrediant number
*  @param ingredient_id witch ingredient
* @param amount new number
*/
void recipe::set_ingredient_amount(std::string ingredient_id, int amount){
    ingredients[ingredient_id] = amount;
}

/**
* @return kitchenware 
*/
std::unordered_map<std::string, int> recipe::get_kitchenware(){
    return kitchenware;
}

/**
* set a new kitchenware
* @param new_kitchenware
*/
void recipe::set_kitchenware(std::unordered_map<std::string,int> new_kitchenware){
    kitchenware.insert(new_kitchenware.begin(),new_kitchenware.end());
}

/**
* @brief kitchenware +1
*  @param kitchenware_id witch kitchenware
*/
void recipe::increment_kitchenware_amount(std::string kitchenware_id){
    kitchenware[kitchenware_id]++;
}

/**
* @brief kitchenware -1
*  @param kitchenware_id witch kitchenware
*/
void recipe::decrement_kitchenware_amount(std::string kitchenware_id){
    kitchenware[kitchenware_id]--;
}

/**
* @brief change kitchenware number
*  @param kitchenware_id witch ingredient
* @param amount new number
*/
void recipe::set_kitchenware_amount(std::string kitchenware_id, int amount){
    kitchenware[kitchenware_id] = amount;
}

/**
* @brief set procedure that user input 
*  @param new_procedures 
*/
void recipe::set_procedure(std::unordered_map<std::string, std::vector<std::string>> new_procedures){
    procedure = new_procedures;
}

/**
* @brief return procedure
*  @return procedure 
*/
std::unordered_map<std::string, std::vector<std::string>> recipe::get_procedure() {
    return procedure;
}
