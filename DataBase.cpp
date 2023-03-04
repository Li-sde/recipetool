/**
 * Creating a Database object to allow QWidget to connect to window
 * @author Donald Cheng Hong Zou
 * @date 2021/11/30
 */

#include "DataBase.h"
/**
 * Database object constructor to allow each class to get and set data to the database file
 * @brief Database object constructor
 */
DataBase::DataBase() {
    this->m_db = QSqlDatabase::addDatabase("QSQLITE");
    this->search = new QSqlQuery(this->m_db);
    this->m_db.setDatabaseName("EasyCooking.sqlite");
    if (!m_db.open()){
        std::cerr << "Database connection failed." << std::endl;
        exit(0);
    }else{
        std::cout << "Database connected." << std::endl;
    }
}

/**
 * Database deconstructor to allow memory to be clear
 * @brief Database deconstructor
 */
DataBase::~DataBase() = default;

/**
 * A method to return all ingredient from the database to a vector which contained Ingredient*
 * @brief Get all ingredients
 * @return std::vector<Ingredient*> A vector contained Ingredient object pointers
 */
std::vector<Ingredient*> DataBase::getAllIngredient() {
    this->search->exec("SELECT * FROM ingredient ORDER BY ingredient_name");
    std::vector<Ingredient*> vec;

    while (this->search->next()){
        std::string ingredient_id = search->value(search->record().indexOf("id")).toString().toStdString();
        std::string ingredient_name =  search->value(search->record().indexOf("ingredient_name")).toString().toStdString();
        std::string best_storing_duration = search->value(search->record().indexOf("best_storing_duration")).toString().toStdString();
        nlohmann::json nutrition = nlohmann::json::parse(search->value(search->record().indexOf("nutritional_value")).toString().toStdString());

        int calories = json::parse(to_string(nutrition["Calories"]))["value"];
        double totalFat = json::parse(to_string(nutrition["Fat"]))["value"];
        double sodium =  json::parse(to_string(nutrition["Sodium, Na"]))["value"];
        double totalCarbs = json::parse(to_string(nutrition["Carbohydrate"]))["value"];
        double protein = json::parse(to_string(nutrition["Protein"]))["value"];
        std::unordered_map<std::string, double> otherNutritionalValues;
        std::vector<std::string> n = {"Alcohol, ethyl", "Water", "Caffeine", "Theobromine", "Sugars", "Fiber", "Calcium, Ca", "Iron, Fe", "Magnesium, Mg", "Phosphorus, P", "Potassium, K", "Zinc, Zn", "Copper, Cu", "Selenium, Se", "Retinol", "Vitamin A, RAE", "Carotene, beta", "Carotene, alpha", "Vitamin E", "Vitamin D", "Cryptoxanthin, beta", "Lycopene", "Lutein + zeaxanthin", "Vitamin C", "Thiamin", "Riboflavin", "Niacin", "Vitamin B6", "Folate", "Vitamin B12", "Choline", "Vitamin K", "Folic acid", "Folate, food", "Folate, DFE", "Vitamin E, added", "Vitamin B12, added", "Cholesterol", "Saturated fatty acids", "Butanoic acid", "Hexanoic acid", "Octanoic acid", "Decanoic acid", "Dodecanoic acid", "Tetradecanoic acid", "Hexadecanoic acid", "Octadecanoic acid", "Octadecenoic acid", "Octadecadienoic acid", "Octadecatrienoic acid", "Eicosatetraenoic acid", "Docosahexaenoic n-3 acid (DHA)", "Hexadecenoic acid", "Octadecatetraenoic acid", "Eicosenoic acid", "Eicosapentaenoic n-3 acid (EPA)", "Docosenoic acid", "Docosapentaenoic n-3 acid (DPA)", "Monounsaturated fatty acids", "Polyunsaturated fatty acids", "Tocopherol, alpha", "Net carbs"};
        for (const auto& i : n){
            try{
                otherNutritionalValues[i] = json::parse(to_string(nutrition[i]))["value"];
            }catch (detail::type_error &e){}
        }
        auto *t_n = new NutritionalValue(calories, totalFat, sodium, totalCarbs, protein, otherNutritionalValues);
        auto *tmp = new Ingredient(ingredient_name, best_storing_duration, t_n,ingredient_id);
        vec.push_back(tmp);
    }
    search->clear();
    return vec;
}

/**
 * A method to get the kitchenware inventory, and return it as a unordered_map
 * @brief Get kitchenware inventory
 * @return std::unordered_map<std::string, int> A unordered_map contained a string as key and integer as value
 */
std::unordered_map<std::string, int> DataBase::getKitchenWareInventory() {
    std::unordered_map<std::string, int> inventory;
    this->search->exec("SELECT kitchenware_id, amount FROM kitchenware_inventory");
    while (this->search->next()){
        inventory[search->value(0).toString().toStdString()] = search->value(1).toInt();
    }
    search->clear();
    return inventory;
}

/**
 * A method to get all kitchenware from the database and return all kitchenware in a vector
 * @brief Get all kitchenware
 * @return std::vector<Kitchenware*> A vector which contained Kitchenware object pointers.
 */
std::vector<Kitchenware *> DataBase::getAllKitchenware() {
    std::vector<Kitchenware *> kit;
    this->search->exec("SELECT id, kitchenware_name FROM kitchenware ORDER BY kitchenware_name");
    while(this->search->next()){
        auto *tmp = new Kitchenware(search->value(0).toString().toStdString(),
                                           search->value(1).toString().toStdString());
        kit.push_back(tmp);
    }
    search->clear();
    return kit;
}

/**
 * A method to get ingredient inventory, which is what the user had and return it in a unordered map
 * @brief Get ingredient inventory
 * @return std::unordered_map<std::string, int>  A unordered_map contained a string as key and integer as value
 */
std::unordered_map<std::string, int> DataBase::getIngredientInventory() {
    std::unordered_map<std::string, int> inventory;
    this->search->exec("SELECT ingredient_id, amount FROM ingredient_inventory");
    while (this->search->next()){
        inventory[search->value(0).toString().toStdString()] = search->value(1).toInt();
    }
    search->clear();
    return inventory;
}

/**
 * A method to get ingredient by using their ID, and return the ingredient object
 * @brief Get ingredient by ID
 * @param id Ingredient ID
 * @return Ingredient* Object that contained the ingredient of tha ID
 * @return nullptr Will return nullptr if the ingredient does not exist
 */
Ingredient *DataBase::getIngredientByID(const std::string& id) {
    std::string stmt = "SELECT * FROM ingredient WHERE id = '" + id + "'";
    this->search->exec(QString::fromStdString(stmt));
    std::vector<Ingredient*> vec;
    while (this->search->next()){
        std::string ingredient_id = search->value(search->record().indexOf("id")).toString().toStdString();
        std::string ingredient_name =  search->value(search->record().indexOf("ingredient_name")).toString().toStdString();
        std::string best_storing_duration = search->value(search->record().indexOf("best_storing_duration")).toString().toStdString();
        json nutrition = json::parse(search->value(search->record().indexOf("nutritional_value")).toString().toStdString());

        int calories = json::parse(to_string(nutrition["Calories"]))["value"];
        double totalFat = json::parse(to_string(nutrition["Fat"]))["value"];
        double sodium =  json::parse(to_string(nutrition["Sodium, Na"]))["value"];
        double totalCarbs = json::parse(to_string(nutrition["Carbohydrate"]))["value"];
        double protein = json::parse(to_string(nutrition["Protein"]))["value"];
        std::unordered_map<std::string, double> otherNutritionalValues;
        std::vector<std::string> n = {"Alcohol, ethyl", "Water", "Caffeine", "Theobromine", "Sugars", "Fiber", "Calcium, Ca", "Iron, Fe", "Magnesium, Mg", "Phosphorus, P", "Potassium, K", "Zinc, Zn", "Copper, Cu", "Selenium, Se", "Retinol", "Vitamin A, RAE", "Carotene, beta", "Carotene, alpha", "Vitamin E", "Vitamin D", "Cryptoxanthin, beta", "Lycopene", "Lutein + zeaxanthin", "Vitamin C", "Thiamin", "Riboflavin", "Niacin", "Vitamin B6", "Folate", "Vitamin B12", "Choline", "Vitamin K", "Folic acid", "Folate, food", "Folate, DFE", "Vitamin E, added", "Vitamin B12, added", "Cholesterol", "Saturated fatty acids", "Butanoic acid", "Hexanoic acid", "Octanoic acid", "Decanoic acid", "Dodecanoic acid", "Tetradecanoic acid", "Hexadecanoic acid", "Octadecanoic acid", "Octadecenoic acid", "Octadecadienoic acid", "Octadecatrienoic acid", "Eicosatetraenoic acid", "Docosahexaenoic n-3 acid (DHA)", "Hexadecenoic acid", "Octadecatetraenoic acid", "Eicosenoic acid", "Eicosapentaenoic n-3 acid (EPA)", "Docosenoic acid", "Docosapentaenoic n-3 acid (DPA)", "Monounsaturated fatty acids", "Polyunsaturated fatty acids", "Tocopherol, alpha", "Net carbs"};
        for (const auto& i : n){
            try{
                otherNutritionalValues[i] = json::parse(to_string(nutrition[i]))["value"];
            }catch (detail::type_error &e){}
        }
        auto *t_n = new NutritionalValue(calories, totalFat, sodium, totalCarbs, protein, otherNutritionalValues);
        auto *tmp = new Ingredient(ingredient_name, best_storing_duration, t_n,ingredient_id);
        return tmp;
    }
    search->clear();
    return nullptr;
}

/**
 * A method to get kitchenware by its ID and return the kitchenware method
 * @brief Get kitchenware by ID
 * @param id Kitchenware ID
 * @return Kitchenware* Pointer of a Kitchenware object
 * @return nullptr Will return this if the ingredient ID does not exist
 */
Kitchenware *DataBase::getKitchenwareByID(const std::string& id) {
    std::string stmt = "SELECT id, kitchenware_name FROM kitchenware WHERE id = '" + id + "'";
    this->search->exec(QString::fromStdString(stmt));
    while(this->search->next()){
        auto *tmp = new Kitchenware(search->value(0).toString().toStdString(),
                                    search->value(1).toString().toStdString());
        return tmp;
    }
    search->clear();
    return nullptr;
}

/**
 * A method to add a ingredient to the ingredient inventory table in database
 * @brief Add a ingredient into inventory
 * @param ingredient_id Ingredient ID
 * @param amount The amount of the the ingredient
 * @return true If it updated successfully
 * @return false If it updated unsuccessfully
 */
bool DataBase::addIngredientInventory(const std::string& ingredient_id, int amount) {
    std::string stmt = "SELECT ingredient_id, amount, COUNT(*) FROM ingredient_inventory WHERE ingredient_id = '" + ingredient_id + "'";
    this->search->exec(QString::fromStdString(stmt));
    this->search->next();
    if (this->search->value(2).toInt() == 1){
        stmt = "UPDATE ingredient_inventory SET amount = " + to_string(amount) + " WHERE ingredient_id = '"
                           + ingredient_id + "'";
        std::cout << stmt << std::endl;
    }else{
        stmt = "INSERT INTO ingredient_inventory (ingredient_id, amount) VALUES ('" + ingredient_id + "', " + to_string(amount) + ")";
        std::cout << stmt << std::endl;
    }
    this->search->clear();
    this->search->exec(QString::fromStdString(stmt));
    if (this->search->numRowsAffected() != 1){
        return false;
    }
    this->m_db.commit();
    return true;
}

/**
 * A method to add a kitchenware to the kitchenware inventory table in database
 * @brief Add a kitchenware into inventory
 * @param kitchenware_id Kitchenware ID
 * @param amount The amount the user want to add
 * @return true If it updated successfully
 * @return false If it updated unsuccessfully
 */
bool DataBase::addKitchenwareInventory(const std::string& kitchenware_id, int amount) {
    std::string stmt = "SELECT COUNT(*) FROM kitchenware_inventory WHERE kitchenware_id = '" + kitchenware_id + "'";
    this->search->exec(QString::fromStdString(stmt));
    this->search->next();
    if (this->search->value(0).toInt() == 1){
        stmt = "UPDATE kitchenware_inventory SET amount = " + to_string(amount) + " WHERE kitchenware_id = '"
               + kitchenware_id + "'";
    }else{
        stmt = "INSERT INTO kitchenware_inventory (kitchenware_id, amount) VALUES ('" + kitchenware_id + "', " + to_string(amount) + ")";
    }
    this->search->clear();
    this->search->exec(QString::fromStdString(stmt));
    this->m_db.commit();
    if (this->search->numRowsAffected() != 1){
        return false;
    }
    return true;
}

/**
 * A method to get all recipe into a vector from the database
 * @brief Get all recipe
 * @return vector<recipe*> A vector containing all recipe
 */
std::vector<recipe *> DataBase::getAllRecipe() {
    std::vector<recipe*> rec;
    this->search->exec("SELECT id, name, cuisine, time_required_minutes, ingredient, kitchenware, procedure FROM recipe");
    while(this->search->next()){
        std::string id = this->search->value(0).toString().toStdString();
        std::string name = this->search->value(1).toString().toStdString();
        std::string cuisine = this->search->value(2).toString().toStdString();
        int time_required = this->search->value(3).toInt();
        std::string pro = this->search->value(6).toString().toStdString();
        const char x = '\\';
        const char y = '\'';
        std::replace(pro.begin(), pro.end(), x, y);

        json ingredient = json::parse(this->search->value(4).toString().toStdString());
        json kitchenware = json::parse(this->search->value(5).toString().toStdString());
        json procedure = json::parse(pro);


        std::unordered_map<std::string, int> ingredient_map;
        std::unordered_map<std::string, int> kitchenware_map;
        std::unordered_map<std::string, std::vector<std::string>> procedure_map;
        for (auto& i : ingredient){
            json tmp = json::parse(to_string(i));
            ingredient_map[tmp["ingredient_id"]] = tmp["amount"];
        }
        for (auto &i : kitchenware){
            kitchenware_map[i] = 1;
        }
        for (auto &i : procedure.items()){
            json detail = json::parse(to_string(i.value()));
            std::vector<std::string> det;
            for (auto &k : detail.items()){
                det.push_back(k.value());
            }
            procedure_map[i.key()] = det;
        }
        auto *recipe_obj = new recipe(id, name, cuisine, time_required, ingredient_map, kitchenware_map, procedure_map);
        rec.push_back(recipe_obj);
    }
    this->search->clear();
    return rec;
}

/**
 * A method to update recipe into the database
 * @brief Updating Recipe
 * @param rec a recipe pointer
 * @return true if update successfully
 * @return false if update not success
 */
bool DataBase::updateRecipe(recipe *rec) {
    json ingredient_map;
    json kitchenware_map;
    json procedure_map;

    for(auto [id, amount] : rec->get_ingredients()){
        json tmp;
        tmp["ingredient_id"] = id;
        tmp["amount"] = amount;
        ingredient_map.push_back(tmp);
    }

    for (auto [id, amount] : rec->get_kitchenware()){
        kitchenware_map += id;
    }

    for (auto [title, steps] : rec->get_procedure()){
        for (const auto& i : steps){
            procedure_map[title] += i;
        }
    }

    std::string stmt = "UPDATE recipe SET name = '" + rec->get_recipe_name() + "', cuisine = '" + rec->get_cuisine_type()+"'";
    stmt += ", time_required_minutes = " + std::to_string(rec->get_time_minutes());
    stmt += ", ingredient = json('" + to_string(ingredient_map) + "'), kitchenware = json('" + to_string(kitchenware_map) + "')";
    stmt += ", procedure = json('" + to_string(procedure_map) + "') WHERE id = '" + rec->get_recipe_id() +"'";
    if (this->search->exec(QString::fromStdString(stmt))){
        this->search->clear();
        this->m_db.commit();
        return true;
    }else{
       return false;
    }
}

/**
 * Add a new recipe into the database and return true or false
 * @brief Add new recipe
 * @param rec Recipe object pointer
 * @return true if adding successfully
 * @return false if adding not success
 */
bool DataBase::addRecipe(recipe *rec) {
    json ingredient_map;
    json kitchenware_map;
    json procedure_map;

    for(auto [id, amount] : rec->get_ingredients()){
        json tmp;
        tmp["ingredient_id"] = id;
        tmp["amount"] = amount;
        ingredient_map.push_back(tmp);
    }

    for (auto [id, amount] : rec->get_kitchenware()){
        kitchenware_map += id;
    }

    for (auto [title, steps] : rec->get_procedure()){
        for (const auto& i : steps){
            procedure_map[title] += i;
        }
    }

    std::string pro = to_string(procedure_map);
    const char x = '\'';
    const char y = '\\';
    std::replace(pro.begin(), pro.end(), x, y);

    std::string stmt = "INSERT INTO recipe (cuisine, ingredient, kitchenware, procedure, name, time_required_minutes) VALUES (";
    stmt += "'" + rec->get_cuisine_type() + "', '" + to_string(ingredient_map) + "', '" + to_string(kitchenware_map) + "'";
    stmt += ", '" + pro + "', '" + rec->get_recipe_name() + "', " + std::to_string(rec->get_time_minutes()) + ")";

    this->search->exec(QString::fromStdString(stmt));
    if (this->search->numRowsAffected() != 1){
        return false;
    }
    this->m_db.commit();
    return true;
}

/**
 * A method to search recipe by using keyword to search a recipe
 * @brief Search recipe
 * @param search A keyword of a recipe's name
 * @return vector<recipe*> A vector containing all matched recipe
 */
std::vector<recipe *> DataBase::searchRecipe(std::string search) {
    std::vector<recipe*> rec;
    std::string stmt = "SELECT id, name, cuisine, time_required_minutes, ingredient, kitchenware, procedure FROM recipe WHERE name LIKE '%"+search+"%'";
    this->search->exec(QString::fromStdString(stmt));
    while(this->search->next()){
        std::string id = this->search->value(0).toString().toStdString();
        std::string name = this->search->value(1).toString().toStdString();
        std::string cuisine = this->search->value(2).toString().toStdString();
        int time_required = this->search->value(3).toInt();
        std::string pro = this->search->value(6).toString().toStdString();
        const char x = '\\';
        const char y = '\'';
        std::replace(pro.begin(), pro.end(), x, y);

        json ingredient = json::parse(this->search->value(4).toString().toStdString());
        json kitchenware = json::parse(this->search->value(5).toString().toStdString());
        json procedure = json::parse(pro);


        std::unordered_map<std::string, int> ingredient_map;
        std::unordered_map<std::string, int> kitchenware_map;
        std::unordered_map<std::string, std::vector<std::string>> procedure_map;
        for (auto& i : ingredient){
            json tmp = json::parse(to_string(i));
            ingredient_map[tmp["ingredient_id"]] = tmp["amount"];
        }
        for (auto &i : kitchenware){
            kitchenware_map[i] = 1;
        }
        for (auto &i : procedure.items()){
            json detail = json::parse(to_string(i.value()));
            std::vector<std::string> det;
            for (auto &k : detail.items()){
                det.push_back(k.value());
            }
            procedure_map[i.key()] = det;
        }
        auto *recipe_obj = new recipe(id, name, cuisine, time_required, ingredient_map, kitchenware_map, procedure_map);
        rec.push_back(recipe_obj);
    }
    this->search->clear();
    return rec;
}

/** A method to filter recipe by name or duration, in ascending or descending order
 * @brief Filter Recipe
 * @param field A string for name of recipe or duration of recipe
 * @param order A string containing ASC or DESC
 * @return vector<recipe*> A vector containing the result
 */
std::vector<recipe*> DataBase::filterRecipe(std::string field, std::string order) {
    std::vector<recipe*> rec;
    std::string stmt = "SELECT id, name, cuisine, time_required_minutes, ingredient, kitchenware, procedure FROM recipe ORDER BY "+field+" "+order;
    this->search->exec(QString::fromStdString(stmt));
    while(this->search->next()){
        std::string id = this->search->value(0).toString().toStdString();
        std::string name = this->search->value(1).toString().toStdString();
        std::string cuisine = this->search->value(2).toString().toStdString();
        int time_required = this->search->value(3).toInt();
        std::string pro = this->search->value(6).toString().toStdString();
        const char x = '\\';
        const char y = '\'';
        std::replace(pro.begin(), pro.end(), x, y);

        json ingredient = json::parse(this->search->value(4).toString().toStdString());
        json kitchenware = json::parse(this->search->value(5).toString().toStdString());
        json procedure = json::parse(pro);


        std::unordered_map<std::string, int> ingredient_map;
        std::unordered_map<std::string, int> kitchenware_map;
        std::unordered_map<std::string, std::vector<std::string>> procedure_map;
        for (auto& i : ingredient){
            json tmp = json::parse(to_string(i));
            ingredient_map[tmp["ingredient_id"]] = tmp["amount"];
        }
        for (auto &i : kitchenware){
            kitchenware_map[i] = 1;
        }
        for (auto &i : procedure.items()){
            json detail = json::parse(to_string(i.value()));
            std::vector<std::string> det;
            for (auto &k : detail.items()){
                det.push_back(k.value());
            }
            procedure_map[i.key()] = det;
        }
        auto *recipe_obj = new recipe(id, name, cuisine, time_required, ingredient_map, kitchenware_map, procedure_map);
        rec.push_back(recipe_obj);
    }
    this->search->clear();
    return rec;
}

/**
 * Filter recipe by name in ascending order
 * @brief Filter Recipe by name in ASC order
 * @return vector<recipe*> A vector containing the result
 */
std::vector<recipe*> DataBase::filterRecipeNameASC() {
    return this->filterRecipe("name", "ASC");
}

/**
 * Filter recipe by name in descending order
 * @brief Filter Recipe by name in DESC order
 * @return vector<recipe*> A vector containing the result
 */
std::vector<recipe*> DataBase::filterRecipeNameDESC() {
    return this->filterRecipe("name", "DESC");
}

/**
 * Filter recipe by duration in ascending order
 * @brief Filter Recipe by duration in ASC order
 * @return vector<recipe*> A vector containing the result
 */
std::vector<recipe*> DataBase::filterRecipeDurationASC() {
    return this->filterRecipe("duration", "ASC");
}

/**
 * Filter recipe by duration in descending order
 * @brief Filter Recipe by duration in DESC order
 * @return vector<recipe*> A vector containing the result
 */
std::vector<recipe*> DataBase::filterRecipeDurationDESC() {
    return this->filterRecipe("duration", "DESC");
}

/**
 * A method to get a recipe by its ID from database
 * @brief Get recipe by ID
 * @param ID A string recipe ID
 * @return recipe* A recipe object pointer containing the data
 */
recipe* DataBase::getRecipeByID(const std::string& ID) {
    std::string stmt = "SELECT id, name, cuisine, time_required_minutes, ingredient, kitchenware, procedure FROM recipe WHERE id = '"+ID+"'";
    this->search->exec(QString::fromStdString(stmt));
    while(this->search->next()){
        std::string id = this->search->value(0).toString().toStdString();
        std::string name = this->search->value(1).toString().toStdString();
        std::string cuisine = this->search->value(2).toString().toStdString();
        int time_required = this->search->value(3).toInt();
        std::string pro = this->search->value(6).toString().toStdString();
        const char x = '\\';
        const char y = '\'';
        std::replace(pro.begin(), pro.end(), x, y);

        json ingredient = json::parse(this->search->value(4).toString().toStdString());
        json kitchenware = json::parse(this->search->value(5).toString().toStdString());
        json procedure = json::parse(pro);


        std::unordered_map<std::string, int> ingredient_map;
        std::unordered_map<std::string, int> kitchenware_map;
        std::unordered_map<std::string, std::vector<std::string>> procedure_map;
        for (auto& i : ingredient){
            json tmp = json::parse(to_string(i));
            ingredient_map[tmp["ingredient_id"]] = tmp["amount"];
        }
        for (auto &i : kitchenware){
            kitchenware_map[i] = 1;
        }
        for (auto &i : procedure.items()){
            json detail = json::parse(to_string(i.value()));
            std::vector<std::string> det;
            for (auto &k : detail.items()){
                det.push_back(k.value());
            }
            procedure_map[i.key()] = det;
        }
        auto *recipe_obj = new recipe(id, name, cuisine, time_required, ingredient_map, kitchenware_map, procedure_map);
        return recipe_obj;
    }
    return nullptr;
}


