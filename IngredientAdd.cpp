
/**
 * @brief This class creates the ingredient add window allows user add new ingredient into the database
 * @author Xingjian Mao
 * @date 2021/11/30
 */

#include "IngredientAdd.h"


/**
 * This is the constructor of the class takes the target database and creates an add window
 * @brief IngredientAdd Constructor
 * @param db target database
 */
IngredientAdd::IngredientAdd(DataBase *db) {
    DB = db;
    IngredientAddW->setAttribute(Qt::WA_DeleteOnClose);
    QObject::connect(IngredientAddW, SIGNAL(destroyed(QObject*)), SLOT(showIngredientWindow()));
    IngredientAddW->setWindowTitle("Add Ingredient");
    IngredientAddW->setFixedSize(800, 400);
    IngredientAddW->setStyleSheet("background-color: #ffffff");

    SelectIngredient();

    auto *submitButton = new QPushButton("Add");
    submitButton->setStyleSheet("color: #FFFFFF; background-color: #C37000; padding: 20px 16px; border: 0; font-size: 16px;");
    submitButton->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(submitButton, SIGNAL(clicked()), SLOT(IngredientNewSubmit()));
    this->BodyLayout->addWidget(submitButton);

    IngredientAddLayout->setMargin(0);
    BodyLayout->addStretch();
    BodyLayout->setMargin(0);
    Body->setLayout(BodyLayout);
    IngredientAddW->setLayout(IngredientAddLayout);

    Body->setStyleSheet("QGroupBox { background-color: white; border: none; }");
    auto *PlaceHold_1 = new QLabel();
    auto *PlaceHold_2 = new QLabel();
    auto *PlaceHold_3 = new QLabel();
    auto *PlaceHold_4 = new QLabel();
    auto *PlaceHold_5 = new QLabel();

    this->IngredientAddLayout->addWidget(PlaceHold_1);
    this->IngredientAddLayout->addWidget(PlaceHold_2);
    this->IngredientAddLayout->addWidget(PlaceHold_3);
    this->IngredientAddLayout->addWidget(PlaceHold_4);
    this->IngredientAddLayout->addWidget(PlaceHold_5);

    IngredientAddLayout->addWidget(Body);
    IngredientAddW->show();

}


/**
 * This method creates components allows user to select the new ingredient
 * @brief Select Ingredient
 */
void IngredientAdd::SelectIngredient() {

    auto *layout = new QVBoxLayout();
    IngredientList->setStyleSheet("margin: 0; padding: 0; background-color: white; border: 0");
    layout->setMargin(0);
    layout->setSpacing(8);
    layout->addWidget(IngredientAddRow());
    IngredientList->setLayout(layout);
    BodyLayout->addWidget(IngredientList);
}


/**
 * This method represents the ingredient detailed window with its amount and nutrition, and allows user to edit the amount
 * @brief Add a new ingredient row
 * @return QGroupBox contains a new row of adding
 */
QGroupBox* IngredientAdd::IngredientAddRow(){
    auto *IngredientBox = new QComboBox();
    IngredientBox->setStyleSheet("QComboBox { color: #5F3600; border: none; border-bottom: 1px solid #707070; padding: 0; font-size: 20px }");
    IngredientBox->setMinimumContentsLength(IngredientAddW->width()/2);

    std::vector<Ingredient*> ing = DB->getAllIngredient();
    IngredientBox->addItem("Select an Ingredient", QVariant("0"));

    for (Ingredient* i : ing){
        IngredientBox->addItem(QString::fromStdString(i->get_ingredient_name()), QVariant(QString::fromStdString(i->get_ingredient_id())));
    }
    auto *amount = new QLineEdit();
    amount->setAttribute(Qt::WA_MacShowFocusRect, false);
    amount->setPlaceholderText("Amount");
    auto *container = new QGroupBox();
    container->setStyleSheet("QGroupBox{ background: white; padding: 0px 32px; border: none; } QLineEdit { color: #5F3600; border: none; border-bottom: 1px solid #707070; font-size: 20px}");
    auto *layout_1 = new QVBoxLayout();
    layout_1->setMargin(0);
    layout_1->setSpacing(16);
    layout_1->addWidget(IngredientBox);
    layout_1->addWidget(amount);
    container->setLayout(layout_1);
    this->Ingredient_map[IngredientBox] = amount;
    return container;
}

/**
 * This method handles the submit from the user
 * @brief Submit new ingredient
 */
void IngredientAdd::IngredientNewSubmit() {
    auto *msg = new QMessageBox();
    for (auto[key, val]: this->Ingredient_map) {
        if (key->currentData().toString().toStdString() == "0") {
            msg->setText("Oops! There are 1 or more Ingredient you haven't select.");
            msg->exec();
            return;
        } else if (val->text().isEmpty()) {
            msg->setText("Oops! There are 1 or more Ingredient does not specified the amount.");
            msg->exec();
            return;
        } else {
            try {
                int amount = std::stoi(val->text().toStdString());
            } catch (exception &e) {
                msg->setText("Oops! One of the kitchenware amount is not an integer.");
                msg->exec();
                return;
            }
        }
    }

    // Finalizing the recipe
    std::unordered_map<std::string, int> Ing_map;
    for (auto [key, val] : this->Ingredient_map){
        Ing_map[key->currentData().toString().toStdString()] = std::stoi(val->text().toStdString());
        if (DB->addIngredientInventory(key->currentData().toString().toStdString(), val->text().toInt())){
            msg->setText("Ingredient Inventory Saved!");
            msg->exec();
            IngredientAddW->close();
        }
        else{
            msg->setText("Oops! save failed!");
            msg->exec();
        }
    }
}

/**
 * @brief Destructor of the class
 */
IngredientAdd::~IngredientAdd(){}

/**
 * @brief method shows the window
 */
void IngredientAdd::showIngredientWindow() {
    auto *IngredientInventoryWindowPointer = new IngredientInventoryWindow(DB);
}
