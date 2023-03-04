/**
 * @author: Bo Yuan Shi
 * @brief: Nutritional value class
 * This class is responsible for containing the nutritional value for each ingredient
 */

#include <unordered_map>
#include <string>
#include "NutritionalValue.h"

/**
 * Constructor for this class
 * @brief NutritionalValue constructor
 * @param calories Calories of the ingredient
 * @param totalFat Total Fat of the ingredient
 * @param sodium Sodium for the ingredient
 * @param totalCarbs Total Carbohydrate for the ingredient
 * @param protein Total protein for the ingredient
 * @param otherNutritionalValues A map containing other nutritional value
 */
NutritionalValue::NutritionalValue(int calories, double totalFat, double sodium, double totalCarbs, double protein,
                 std::unordered_map<std::string, double> otherNutritionalValues) {
    this->calories = calories;
    this->totalFat = double((int)(totalFat * 100))/ 100;
    this->sodium = double((int)(sodium * 100)) / 100;
    this->totalCarbs = double((int)(totalCarbs * 100)) / 100;
    this->protein = double((int)(protein * 100)) / 100;
    this->otherNutritionalValues = otherNutritionalValues;
}

/**
 * De-constructor for this class
 */
NutritionalValue::~NutritionalValue() = default;

/**
 * Get calories for this ingredient
 * @brief Get Calories
 * @return int An Integer value for calories
 */
int NutritionalValue::getCalories() {
    return this->calories;
}

/**
 * Get total fat for this ingredient
 * @brief Get total fat
 * @return double An decimal value for total fat
 */
double NutritionalValue::getTotalFat() {
    return this->totalFat;
}

/**
 * Get sodium for this ingredient
 * @brief Get sodium
 * @return double An decimal value for sodium
 */
double NutritionalValue::getSodium() {
    return this->sodium;
}

/**
 * Get total carbohydrate for this ingredient
 * @brief Get carbohydrate
 * @return double An decimal value for carbohydrate
 */
double NutritionalValue::getTotalCarbs() {
    return this->totalCarbs;
}

/**
 * Get total protein for this ingredient
 * @brief Get protein
 * @return double An decimal value for protein
 */
double NutritionalValue::getProtein() {
    return this->protein;
}

/**
 * Get the value for other nutrient by name
 * @brief Get other nutritional value
 * @param nutrientName A string containing the nutritional name
 * @return double An decimal value
 */
double NutritionalValue::getOtherNutritionalValue(std::string nutrientName) {
    double result;
    try {
        result = this->otherNutritionalValues.at(nutrientName);
    } catch (std::out_of_range &e) {
        result = -1.0;
    }
    return result;
}

/**
 * A setter method for calories
 * @brief Set calories
 * @param calories
 */
void NutritionalValue::setCalories(int calories) {
    this->calories = calories;
}

/**
 * A setter method for total fat
 * @brief Set total fat
 * @param totalFat
 */
void NutritionalValue::setTotalFat(double totalFat) {
    this->totalFat = double((int)(totalFat * 100))/ 100;
}

/**
 * A setter method for sodium
 * @brief Set sodium
 * @param sodium
 */
void NutritionalValue::setSodium(double sodium) {
    this->sodium = double((int)(sodium * 100))/ 100;
}

/**
 * A setter method for totalCarbs
 * @brief Set totalCarbs
 * @param totalCarbs
 */
void NutritionalValue::setTotalCarbs(double totalCarbs) {
    this->totalCarbs = double((int)(totalCarbs * 100))/ 100;
}

/**
 * A setter method for protein
 * @brief Set protein
 * @param protein
 */
void NutritionalValue::setProtein(double protein) {
    this->protein = double((int)(protein * 100))/ 100;
}

/**
 * A setter method other nutritional value
 * @brief Set other nutritional value
 * @param nutrientName Name of the nutrition
 * @param nutrientAmount Amount of the nutrition
 */
void NutritionalValue::addOtherNutritionalValue(std::string nutrientName, double nutrientAmount) {
    otherNutritionalValues[nutrientName] = double((int)(nutrientAmount * 100))/ 100;
}

