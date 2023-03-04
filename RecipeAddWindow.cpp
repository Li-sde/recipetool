/**
 * A class for the Add recipe window
 * @brief Add Recipe Window
 * @author Donald Cheng Hong Zou
 * @date 2021/11/30
 */

#include "RecipeAddWindow.h"

/**
 * A constructor for this class
 * @brief RecipeAddWindow constructor
 * @param db The database this window will use to store recipe
 */
RecipeAddWindow::RecipeAddWindow(DataBase *db) {
    DB = db;
    this->scroll = new QScrollArea();
    this->RecipeAddLayout = new QVBoxLayout();
    this->RecipeAddWindowWidget = new QWidget();
    this->RecipeAddWindowWidget->setWindowTitle("Add a new Recipe");
    this->RecipeAddWindowWidget->setFixedSize(500, 700);
    this->RecipeAddWindowWidget->setStyleSheet("background-color: #ffffff");
    this->Body = new QGroupBox();
    this->BodyLayout = new QVBoxLayout();
    RecipeAddHeader();
    RecipeAddRecipeName();
    RecipeAddTypeAndDuration();
    RecipeAddIngredient();
    RecipeAddKitchenware();
    RecipeAddProcedure();
    auto *submitButton = new QPushButton("Save");
    submitButton->setStyleSheet("color: #FFFFFF; background-color: #C37000; padding: 20px 16px; border: 0; font-size: 16px;");
    submitButton->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(submitButton, SIGNAL(clicked()), SLOT(RecipeNewSubmit()));
    this->BodyLayout->addWidget(submitButton);
    this->RecipeAddLayout->setMargin(0);
    this->BodyLayout->addStretch();
    this->BodyLayout->setMargin(0);
    this->Body->setLayout(BodyLayout);
    this->RecipeAddLayout->addWidget(this->scroll);
    this->RecipeAddWindowWidget->setLayout(RecipeAddLayout);
    this->Body->setStyleSheet("QGroupBox { background-color: white; border: none; }");
    this->scroll->setStyleSheet("QScrollArea { border: none; background-color: white }");
    this->scroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    this->scroll->setWidgetResizable(true);
    this->scroll->setWidget(Body);
}

/**
 * @brief De-constructor for this class
 */
RecipeAddWindow::~RecipeAddWindow() = default;

/**
 * A method to show the window
 * @brief WindowShow
 */
void RecipeAddWindow::WindowShow() {
    this->RecipeAddWindowWidget->show();
}

/**
 * @brief WindowClose
 * A method to close this window
 */
void RecipeAddWindow::WindowClose() {
    this->RecipeAddWindowWidget->close();
}

/**
 * A method to add the Recipe Add window header
 * @brief Add header for this window
 */
void RecipeAddWindow::RecipeAddHeader() {
    auto *RecipeAddTitleContainer = new QGroupBox();
    auto *RecipeAddTitleContainerLayout = new QHBoxLayout();
    auto *RecipeAddTitle = new QLabel("Add Recipe");
    RecipeAddTitle->setStyleSheet("background-color: #ffffff; color: #5F3600; font-size: 20px;");
    RecipeAddTitle->setMargin(0);
    RecipeAddTitleContainerLayout->addStretch();
    RecipeAddTitleContainerLayout->addWidget(RecipeAddTitle);
    RecipeAddTitleContainerLayout->addStretch();
    RecipeAddTitleContainerLayout->setMargin(0);
    RecipeAddTitle->setFixedHeight(70);
    RecipeAddTitleContainer->setStyleSheet("background-color: #ffffff; padding: 0; border: none;");
    RecipeAddTitleContainer->setLayout(RecipeAddTitleContainerLayout);
    this->BodyLayout->addWidget(RecipeAddTitleContainer);
}

/**
 * A method to add a recipe name text box
 * @brief Add recipe name text box
 */
void RecipeAddWindow::RecipeAddRecipeName() {
    this->RecipeName = new QLineEdit();
    this->RecipeName->setStyleSheet("color: #5F3600; border: none; border-bottom: 1px solid #707070; font-size: 20px; margin: 16px 32px 0px 32px");
    this->RecipeName->setPlaceholderText("Recipe Name");
    this->RecipeName->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->BodyLayout->addWidget(RecipeName);
}

/**
 * A method to add a type input and duration input for this window
 * @brief Add type and duration input
 */
void RecipeAddWindow::RecipeAddTypeAndDuration() {
    auto *container = new QGroupBox();
    container->setStyleSheet("QGroupBox{ background: white; padding: 16px 32px; border: none; } QLineEdit { color: #5F3600; border: none; border-bottom: 1px solid #707070; font-size: 20px; }");
    auto *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(16);
    this->RecipeDuration = new QLineEdit();
    this->RecipeDuration->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->RecipeDuration->setPlaceholderText("Duration");
    this->RecipeType = new QLineEdit();
    this->RecipeType->setAttribute(Qt::WA_MacShowFocusRect, false);
    this->RecipeType->setPlaceholderText("Cuisine Type");
    layout->addWidget(RecipeDuration);
    layout->addWidget(RecipeType);
    container->setLayout(layout);
    this->BodyLayout->addWidget(container);

}

/**
 * A method to add ingredient dropdown
 * @brief Add ingredient dropdown
 */
void RecipeAddWindow::RecipeAddIngredient() {
    IngredientList = new QGroupBox();
    auto *layout = new QVBoxLayout();
    auto *label = new QLabel("INGREDIENT");
    auto *addIngredientButton = new QPushButton("Add Ingredient");
    addIngredientButton->setCursor(QCursor(Qt::PointingHandCursor));
    IngredientList->setStyleSheet("margin: 0; padding: 0; background-color: white; border: 0");
    label->setStyleSheet("font-size: 16px; color: #C37000; padding: 0px 26px");
    layout->setMargin(0);
    layout->setSpacing(8);
    layout->addWidget(label);
    layout->addWidget(this->RecipeAddIngredientRow());
    IngredientList->setLayout(layout);
    this->BodyLayout->addWidget(IngredientList);
    addIngredientButton->setStyleSheet("color: #C37000; border: none; margin: 16px 32px; text-align: right; font-size: 16px");
    QObject::connect(addIngredientButton, SIGNAL( clicked()),SLOT(RecipeNewIngredientRow()));
    this->BodyLayout->addWidget(addIngredientButton);
}

/**
 * A method to add a row of ingredient dropdown
 * @brief Add a new row of ingredient
 * @return QGroupBox Containing the row
 */
QGroupBox *RecipeAddWindow::RecipeAddIngredientRow() {
    auto *deleteButton = new QPushButton("");
    deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
    deleteButton->setIcon(QIcon("assets/icons/delete.svg"));
    auto *ingredient = new QComboBox();
    ingredient->setStyleSheet("QComboBox { color: #5F3600; border: none; border-bottom: 1px solid #707070; padding: 0; font-size: 20px }");

    ingredient->setMinimumWidth(RecipeAddWindowWidget->width()/2);
    std::vector<Ingredient*> ing = DB->getAllIngredient();
    ingredient->addItem("Select an ingredient", QVariant("0"));
    for (Ingredient* i : ing){
        ingredient->addItem(QString::fromStdString(i->get_ingredient_name()), QVariant(QString::fromStdString(i->get_ingredient_id())));
    }
    auto *amount = new QLineEdit();
    amount->setAttribute(Qt::WA_MacShowFocusRect, false);
    amount->setPlaceholderText("Amount");
    auto *container = new QGroupBox();
    container->setStyleSheet("QGroupBox{ background: white; padding: 0px 32px; border: none; } QLineEdit { color: #5F3600; border: none; border-bottom: 1px solid #707070; font-size: 20px}");
    auto *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(16);
    layout->addWidget(ingredient);
    layout->addWidget(amount);
    layout->addWidget(deleteButton);
    container->setLayout(layout);
    this->ingredients_map[ingredient] = amount;
    QObject::connect(deleteButton, SIGNAL(clicked()), SLOT(RecipeDeleteIngredientRow()));
    return container;
}

/**
 * A method to call the function above to add a new row for ingredient
 * @brief Recipe new ingredient row
 */
void RecipeAddWindow::RecipeNewIngredientRow() {
    this->IngredientList->layout()->addWidget(this->RecipeAddIngredientRow());
}

/**
 * A method to delete a ingredient row and show message box
 * @brief Delete ingredient row
 */
void RecipeAddWindow::RecipeDeleteIngredientRow() {
    auto *msg = new QMessageBox();
    if (this->ingredients_map.size() > 1){
        msg->setText("Are you sure to delete this ingredient?");
        msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg->setDefaultButton(QMessageBox::No);
        int ret = msg->exec();
        if (ret == QMessageBox::Yes){
            QWidget *w = qobject_cast<QWidget *>(sender()->parent());
            auto *tmp = (QComboBox*) w->layout()->itemAt(0)->widget();
            this->ingredients_map.erase(tmp);
            this->IngredientList->layout()->removeWidget(w);
        }
    }else{
        msg->setText("Deletion Error: Each Recipe required at least 1 ingredient.");
        msg->exec();
    }
}

/**
 * A method to add kitchenware into the window
 * @brief RecipeAddKitchenware
 */
void RecipeAddWindow::RecipeAddKitchenware() {
    KitchenwareList = new QGroupBox();
    auto *layout = new QVBoxLayout();
    auto *label = new QLabel("KITCHENWARE");
    auto *addKitchenwareButton = new QPushButton("Add Kitchenware");
    addKitchenwareButton->setCursor(QCursor(Qt::PointingHandCursor));
    KitchenwareList->setStyleSheet("margin: 0; padding: 0; background-color: white; border: 0");
    label->setStyleSheet("font-size: 16px; color: #C37000; padding: 0px 26px");
    layout->setMargin(0);
    layout->setSpacing(8);
    layout->addWidget(label);
    layout->addWidget(this->RecipeAddKitchenwareRow());
    KitchenwareList->setLayout(layout);
    this->BodyLayout->addWidget(KitchenwareList);
    addKitchenwareButton->setStyleSheet("color: #C37000; border: none; margin: 16px 32px; text-align: right; font-size: 16px");
    QObject::connect(addKitchenwareButton, SIGNAL( clicked()),SLOT(RecipeNewKitchenwareRow()));
    this->BodyLayout->addWidget(addKitchenwareButton);
}

/**
 * A method to add a new row of kitchenware
 * @brief RecipeAddKitchenwareRow
 * @return QGroupBox Containing a new row kitchenware dropdown
 */
QGroupBox *RecipeAddWindow::RecipeAddKitchenwareRow() {
    auto *deleteButton = new QPushButton("");
    deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
    deleteButton->setIcon(QIcon("assets/icons/delete.svg"));
    QObject::connect(deleteButton, SIGNAL(clicked()), SLOT(RecipeDeleteKitchenwareRow()));
    auto *kitchenware = new QComboBox();
    kitchenware->setStyleSheet("color: #5F3600; border: none; border-bottom: 1px solid #707070; padding: 0; font-size: 20px");
    kitchenware->setMinimumWidth(RecipeAddWindowWidget->width()/2);
    std::vector<Kitchenware*> ing = DB->getAllKitchenware();
    kitchenware->addItem("Select a kitchenware", QVariant("0"));
    for (Kitchenware* i : ing){
        kitchenware->addItem(QString::fromStdString(i->get_kitchenware_name()), QVariant(QString::fromStdString(i->get_kitchenware_id())));
    }
    auto *amount = new QLineEdit();
    amount->setAttribute(Qt::WA_MacShowFocusRect, false);
    amount->setPlaceholderText("Amount");
    auto *container = new QGroupBox();
    container->setStyleSheet("QGroupBox{ background: white; padding: 0px 32px; border: none; } QLineEdit { color: #5F3600; border: none; border-bottom: 1px solid #707070; font-size: 20px}");
    auto *layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(16);
    layout->addWidget(kitchenware);
    layout->addWidget(amount);
    layout->addWidget(deleteButton);
    container->setLayout(layout);
    this->kitchenware_map[kitchenware] = amount;
    return container;
}

/**
 * A slot method for the button to add a kitchenware row
 * @brief Add new row
 */
void RecipeAddWindow::RecipeNewKitchenwareRow() {
    this->KitchenwareList->layout()->addWidget(this->RecipeAddKitchenwareRow());
}

/**
 * A method to delete a kitchenware row
 * @brief RecipeDeleteKitchenwareRow
 */
void RecipeAddWindow::RecipeDeleteKitchenwareRow(){
    auto *msg = new QMessageBox();
    if (this->kitchenware_map.size() > 1){
        msg->setText("Are you sure to delete this kitchenware?");
        msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg->setDefaultButton(QMessageBox::No);
        int ret = msg->exec();

        if (ret == QMessageBox::Yes){
            QWidget *w = qobject_cast<QWidget *>(sender()->parent());
            auto *tmp = (QComboBox*) w->layout()->itemAt(0)->widget();
            this->kitchenware_map.erase(tmp);
            this->KitchenwareList->layout()->removeWidget(w);
        }
    }else{
        msg->setText("Deletion Error: Each Recipe required at least 1 kitchenware.");
        msg->exec();
    }
}

/**
 * Add a procedure input
 * @brief RecipeAddProcedure
 */
void RecipeAddWindow::RecipeAddProcedure() {
    ProcedureList = new QGroupBox();
    auto *layout = new QVBoxLayout();
    auto *label = new QLabel("PROCEDURE");
    auto *addProcedureButton = new QPushButton("Add Procedure");
    addProcedureButton->setCursor(QCursor(Qt::PointingHandCursor));
    ProcedureList->setStyleSheet("margin: 0; padding: 0; background-color: white; border: 0");
    label->setStyleSheet("font-size: 16px; color: #C37000; padding: 0px 26px");
    layout->setMargin(0);
    layout->setSpacing(8);
    layout->addWidget(label);
    layout->addWidget(this->RecipeAddProcedureRow());
    ProcedureList->setLayout(layout);
    this->BodyLayout->addWidget(ProcedureList);
    addProcedureButton->setStyleSheet("color: #C37000; border: none; margin: 16px 32px; text-align: right; font-size: 16px");
    QObject::connect(addProcedureButton, SIGNAL( clicked()),SLOT(RecipeNewProcedureRow()));
    this->BodyLayout->addWidget(addProcedureButton);
}

/**
 * A method to get a new row of procedure row
 * @brief RecipeAddProcedureRow
 * @return QGroupBox containing a new procedure row
 */
QGroupBox* RecipeAddWindow::RecipeAddProcedureRow(){
    auto *deleteButton = new QPushButton(" Delete Step");
    deleteButton->setCursor(QCursor(Qt::PointingHandCursor));
    deleteButton->setStyleSheet("font-size: 16px; color: #C37000");
    deleteButton->setIcon(QIcon("assets/icons/delete.svg"));
    QObject::connect(deleteButton, SIGNAL(clicked()), SLOT(RecipeDeleteProcedureRow()));
    auto *layout = new QVBoxLayout();
    layout->setMargin(0);
    auto *container = new QGroupBox();
    container->setStyleSheet("QGroupBox{ background: white; padding: 0px 32px; border: none; } QLineEdit { color: #5F3600; border: none; border-bottom: 1px solid #707070; font-size: 20px} QTextEdit { font-size: 20px; border: 1px solid #707070; color: #5F3600}");
    auto *step_title = new QLineEdit();
    step_title->setPlaceholderText("Step Title");
    auto *step_detail = new QTextEdit();
    step_detail->setPlaceholderText("Write your step detail here...");
    layout->addWidget(step_title);
    layout->addWidget(step_detail);
    procedure_map[step_title] = step_detail;
    layout->addWidget(deleteButton);
    container->setLayout(layout);
    return container;
}

/**
 * A slot method call to add a new row of procedure
 * @brief RecipeNewProcedureRow
 */
void RecipeAddWindow::RecipeNewProcedureRow() {
    this->ProcedureList->layout()->addWidget(this->RecipeAddProcedureRow());
}

/**
 * Delete procedure row
 * @brief RecipeDeleteProcedureRow
 */
void RecipeAddWindow::RecipeDeleteProcedureRow() {
    auto *msg = new QMessageBox();
    if (this->procedure_map.size() > 1){
        msg->setText("Are you sure to delete this step?");
        msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msg->setDefaultButton(QMessageBox::No);
        int ret = msg->exec();

        if (ret == QMessageBox::Yes){
            QWidget *w = qobject_cast<QWidget *>(sender()->parent());
            auto *tmp = (QLineEdit*) w->layout()->itemAt(0)->widget();
            this->procedure_map.erase(tmp);
            this->ProcedureList->layout()->removeWidget(w);
        }
    }else{
        msg->setText("Deletion Error: Each Recipe required at least 1 step.");
        msg->exec();
    }
}

/**
 * A method to submit a new recipe
 * @brief Submit recipe
 */
void RecipeAddWindow::RecipeNewSubmit() {
    auto *msg = new QMessageBox();
    if (this->RecipeName->text().toStdString().empty()){
        msg->setText("Recipe name cannot be empty.");
        msg->exec();
    }
    else if (this->RecipeType->text().toStdString().empty()){
        msg->setText("Recipe type cannot be empty.");
        msg->exec();
    }
    else if (this->RecipeDuration->text().toStdString().empty()){
        msg->setText("Recipe duration cannot be empty.");
        msg->exec();
    }
    else{
        try{
            int duration = std::stoi(this->RecipeDuration->text().toStdString());
        } catch (exception &e) {
            msg->setText("Oops! Duration is not an integer.");
            msg->exec();
            return;
        }
        for (auto [key, val] : this->ingredients_map){
            if(key->currentData().toString().toStdString() == "0"){
                msg->setText("Oops! There are 1 or more ingredient you haven't select.");
                msg->exec();
                return;
            }
            else if(val->text().isEmpty()){
                msg->setText("Oops! There are 1 or more ingredient does not specified the amount.");
                msg->exec();
                return;
            }
            else{
                try{
                    int amount = std::stoi(val->text().toStdString());
                } catch (exception &e) {
                    msg->setText("Oops! One of the ingridient amount is not an integer.");
                    msg->exec();
                    return;
                }
            }
        }
        for (auto [key, val] : this->kitchenware_map){
            if(key->currentData().toString().toStdString() == "0"){
                msg->setText("Oops! There are 1 or more kitchenware you haven't select.");
                msg->exec();
                return;
            }
            else if(val->text().isEmpty()){
                msg->setText("Oops! There are 1 or more kitchenware does not specified the amount.");
                msg->exec();
                return;
            }
            else{
                try{
                    int amount = std::stoi(val->text().toStdString());
                } catch (exception &e) {
                    msg->setText("Oops! One of the kitchenware amount is not an integer.");
                    msg->exec();
                    return;
                }
            }
        }
        if (procedure_map.empty()){
            msg->setText("Oops! Each Recipe required at least 1 step.");
            msg->exec();
            return;
        }else{
            for (auto [key, val] : this->procedure_map){
                if (key->text().isEmpty()){
                    msg->setText("Oops! There are 1 or more procedure title is empty.");
                    msg->exec();
                    return;
                }
            }
        }
        // Finalizing the recipe
        std::string recipe_name = this->RecipeName->text().toStdString();
        int duration = std::stoi(this->RecipeDuration->text().toStdString());
        std::string recipe_type = this->RecipeType->text().toStdString();
        std::unordered_map<std::string, int> ingredients;
        std::unordered_map<std::string, int> kitchenware;
        std::unordered_map<std::string, std::vector<std::string>> procedure;
        for (auto [key, val] : this->ingredients_map){
            ingredients[key->currentData().toString().toStdString()] = std::stoi(val->text().toStdString());
        }
        for (auto [key, val] : this->kitchenware_map){
            kitchenware[key->currentData().toString().toStdString()] = std::stoi(val->text().toStdString());
        }
        for (auto [key, val] : this->procedure_map){
            std::vector<std::string> step;
            std::string data = val->toPlainText().toStdString();
            std::istringstream origStream(data);
            std::string curLine;
            while (std::getline(origStream, curLine))
            {
                if (!curLine.empty()) step.push_back(curLine);
            }
            procedure[key->text().toStdString()] = step;
        }
        rec = new recipe("", recipe_name, recipe_type, duration, ingredients, kitchenware, procedure);
        if (DB->addRecipe(rec)){
            msg->setText("Recipe Saved!");
            msg->exec();
            this->WindowClose();
        }else{
            msg->setText("Oops! Recipe save failed!");
            msg->exec();
        }
    }
}

/**
 * A method to override close event for QWidget
 * @param bar QCloseEvent
 */
void RecipeAddWindow::closeEvent(QCloseEvent *bar) {
    std::cout << "clooosed" << std::endl;
    QWidget::closeEvent(bar);
}

