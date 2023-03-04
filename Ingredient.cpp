/**
 * This class represents the ingredient, it contains a name, a best storing duration, a nutrition value object and an ID
 * @author Xingjian Mao
 * @date 2021/11/30
 */
#include "Ingredient.h"
#include <string>
#include <unordered_map>

using namespace std;

/**
 * @brief This method is the constructor of the class sets the name, storing duration, nutritino value
 * and an ID
 * @param ingredient_nameP name
 * @param best_storing_durationP storing duration
 * @param nutritionalValue NutritionalValue
 * @param ingredient_id Ingredient ID
 */
Ingredient::Ingredient(string ingredient_nameP, string best_storing_durationP,
                       NutritionalValue *nutritionalValue, string ingredient_id) {
    this->ingredient_id = ingredient_id;
    this->best_storing_duration = best_storing_durationP;
    this->NutritionValue = nutritionalValue;
    this->ingredient_name = ingredient_nameP;

}

/**
 * @brief This method returns the ingredient name
 * @return string represents ingredient name
 */
string Ingredient::get_ingredient_name(){
    return ingredient_name;
};

/**
 * @brief Method returns best storing duration
 * @return string represents best storing duration
 */
string Ingredient::get_best_storing_duration(){
    return best_storing_duration;
};

/**
 * @brief Method returns int represents the nutrtion value
 * @param item_name nutrition name
 * @return int represents nutrition amount
 */
int Ingredient::get_nutritional_value(string item_name) {
    if (item_name == "Calories"){
        return this->NutritionValue->getCalories();
    }
    else if (item_name == "Total Fat"){
        return this->NutritionValue->getTotalFat();
    }
    else if (item_name == "Sodium"){
        return this->NutritionValue->getSodium();
    }
    else if (item_name == "Total Carbs"){
        return this->NutritionValue->getTotalCarbs();
    }
    else if (item_name == "Protein"){
        return this->NutritionValue->getProtein();
    }
    else{
        return -1;
    }
}

/**
 * @brief This method returns other nutritiona vale
 * @param item_name nutrition name
 * @return int represents nutrition amount
 */
int Ingredient::get_other_nutritional_value(string item_name){
    return this->NutritionValue->getOtherNutritionalValue(item_name);
}

/**
 * @brief method sets the name of the ingredient
 * @param name ingredient name
 */
void Ingredient::set_ingredient_name(string name){
    ingredient_name = name;
}

/**
 * @brief method sets the best storing date
 * @param day int represents the day of best storing
 */
void Ingredient::set_best_storing_name(int day) {
    best_storing_duration = day;
}

/**
 * @brief method sets the nutition value
 * @param item_name nutrition name
 * @param nutritional_value nutrition amount
 *
 */

void Ingredient::set_nutritional_value(string item_name, int nutritional_value) {
    if (item_name == "Calories"){
        this->NutritionValue->setCalories(nutritional_value);
    }
    else if (item_name == "Total Fat"){
        this->NutritionValue->setTotalFat(nutritional_value);
    }
    else if (item_name == "Sodium"){
        this->NutritionValue->setSodium(nutritional_value);
    }
    else if (item_name == "Total Carbs"){
        this->NutritionValue->setTotalFat(nutritional_value);
    }
    else if (item_name == "Protein"){
        this->NutritionValue->setProtein(nutritional_value);
    }
}

/**
 * @brief method sets the other nutritonal value
 * @param nutritional_value nutritional value
 * @param item_name nutrition name
 */
void Ingredient::set_other_nutritional_value(string item_name, int nutritional_value) {
    this->NutritionValue->addOtherNutritionalValue(item_name, nutritional_value);
}


/**
 * @brief method sets the ID
 * @return int represents ID
 */
string Ingredient::get_ingredient_id() {
    return this->ingredient_id;
}
