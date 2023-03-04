/**
 * @author: Bo Yuan Shi
 * @brief: Mainmenu class, responsible for the main menu.
 * This class is responsible for the UI behind all of the main menu, and linking between the main menu and other
 * classes within this project.
 */

#include "mainMenu.h"

/**
 * @author: Bo Yuan Shi
 * @brief: Constructor for the main menu
 * This class is where all of the UI for the main menu is generated and set up. Handlers for buttons are also set here,
 * allowing the program to jump between mainmenu and recipe, ingredients and kitchenware.
 * @param *DB Takes in a DataBase object, which will be passed around to other classes
 */
mainMenu::mainMenu(DataBase *DB) {
    db = DB;

    // Fonts and css that will be used
    auto TITLE_FONT = "font-size: 40px; color: #C37000; font-weight: bold";
    auto NORMAL_TEXT_FONT = "font-size: 20px; color: #5F3600; margin-bottom: 15px";
    auto CURRENT_TIME_FONT = "font-size: 80px; color: #FFFFFF; font-weight: bold";
    auto CURRENT_DATE_FONT = "font-size: 32px; color: #FFFFFF; margin-left: 5px";
    auto RIGHT_ARROW_FILE_LOCATION = "assets/icons/right.svg";
    auto RIGHT_ARROW_STYLE = "border: 0px; float: right; max-width: 45px; max-height: 45px";

    // Main window
    window = new QWidget;
    window->setFixedSize(1280, 800);
    window->setObjectName("Window");
    window->setStyleSheet("QWidget#Window{background-image:url(\"assets/img/background.png\")}");

    layout = new QGridLayout;

    // Recipes Card/Button Beginning
    recipeWidget = new QWidget();
    recipeWidget->setObjectName("RecipeWidget");
    recipeWidget->setStyleSheet("QWidget#RecipeWidget{background-color: #EDEDED; "
                                "border-radius: 25px; margin: 15% 0%; max-width: 400px}");
    recipeLayout = new QGridLayout;

    recipeLayoutTitle = new QLabel("Recipes");
    recipeLayoutTitle->setStyleSheet(TITLE_FONT);
    recipeLayoutTitle->setContentsMargins(5,0,0,0);
    recipeLayoutText = new QLabel("Find your cooking inspiration");
    recipeLayoutText->setStyleSheet(NORMAL_TEXT_FONT);
    recipeButton = new QPushButton;
    recipeButton->setIcon(QIcon(RIGHT_ARROW_FILE_LOCATION));
    recipeButton->setStyleSheet(RIGHT_ARROW_STYLE);
    recipeButton->setIconSize(QSize(45,45));
    recipeButton->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(recipeButton, SIGNAL(clicked()), this, SLOT(HandleRecipeButtonPress()));

    recipeLayout->addWidget(recipeLayoutTitle, 0, 0, Qt::AlignLeft);
    recipeLayout->addWidget(recipeLayoutText, 1, 0, Qt::AlignLeft);
    recipeLayout->addWidget(recipeButton, 2, 0, Qt::AlignRight);
    recipeLayout->setContentsMargins(40, 40, 40, 40);
    recipeLayout->setSpacing(0);
    recipeWidget->setLayout(recipeLayout);
    // Recipes Card/Button End

    // Ingredients Card/Button Beginning
    ingredientWidget = new QWidget();
    ingredientWidget->setObjectName("IngredientWidget");
    ingredientWidget->setStyleSheet("QWidget#IngredientWidget{background-color: #EDEDED; "
                                    "border-radius: 25px; margin: 15% 0%; max-width: 400px}");
    ingredientLayout = new QGridLayout;

    ingredientLayoutTitle = new QLabel("Ingredients");
    ingredientLayoutTitle->setStyleSheet(TITLE_FONT);
    ingredientLayoutTitle->setContentsMargins(5, 0, 0, 0);
    ingredientLayoutText = new QLabel("Store all ingredients you have");
    ingredientLayoutText->setStyleSheet(NORMAL_TEXT_FONT);
    ingredientButton = new QPushButton;
    ingredientButton->setIcon(QIcon(RIGHT_ARROW_FILE_LOCATION));
    ingredientButton->setStyleSheet(RIGHT_ARROW_STYLE);
    ingredientButton->setIconSize(QSize(45,45));
    ingredientButton->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(ingredientButton, SIGNAL(clicked()), this, SLOT(HandleIngredientButtonPress()));

    ingredientLayout->addWidget(ingredientLayoutTitle, 0, 0, Qt::AlignLeft);
    ingredientLayout->addWidget(ingredientLayoutText, 1, 0, Qt::AlignLeft);
    ingredientLayout->addWidget(ingredientButton, 2, 0, Qt::AlignRight);
    ingredientLayout->setContentsMargins(40, 40, 40, 40);
    ingredientWidget->setLayout(ingredientLayout);
    // Ingredients Card/Button End

    // Kitchenware Card/Button Beginning
    kitchenwareWidget = new QWidget();
    kitchenwareWidget->setObjectName("KitchenwareWidget");
    kitchenwareWidget->setStyleSheet("QWidget#KitchenwareWidget{background-color: #EDEDED; "
                                     "border-radius: 25px; margin: 15% 0%; max-width: 400px}");
    kitchenwareLayout = new QGridLayout();

    kitchenwareLayoutTitle = new QLabel("Kitchenware");
    kitchenwareLayoutTitle->setStyleSheet(TITLE_FONT);
    kitchenwareLayoutTitle->setContentsMargins(5, 0, 0, 0);
    kitchenwareLayoutText = new QLabel("Store all kitchenware you have");
    kitchenwareLayoutText->setStyleSheet(NORMAL_TEXT_FONT);
    kitchenwareButton = new QPushButton;
    kitchenwareButton->setIcon(QIcon(RIGHT_ARROW_FILE_LOCATION));
    kitchenwareButton->setStyleSheet(RIGHT_ARROW_STYLE);
    kitchenwareButton->setIconSize(QSize(45,45));
    kitchenwareButton->setCursor(QCursor(Qt::PointingHandCursor));
    QObject::connect(kitchenwareButton, SIGNAL(clicked()), this, SLOT(HandleKitchenwareButtonPress()));

    kitchenwareLayout->addWidget(kitchenwareLayoutTitle, 0, 0, Qt::AlignLeft);
    kitchenwareLayout->addWidget(kitchenwareLayoutText, 1, 0, Qt::AlignLeft);
    kitchenwareLayout->addWidget(kitchenwareButton, 2, 0, Qt::AlignRight);
    kitchenwareLayout->setContentsMargins(40, 40, 40, 40);
    kitchenwareWidget->setLayout(kitchenwareLayout);
    // Kitchenware Card/Button End

    // Current Time and Date
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, [&]() {
        QTime currentTime = QTime::currentTime();
        QString time = currentTime.toString();
        currentTimeLabel->setText(time);
    });
    timer->start();

    currentTimeLabel = new QLabel(QTime::currentTime().toString());
    currentTimeLabel->setStyleSheet(CURRENT_TIME_FONT);
    currentDateLabel = new QLabel(QDate::currentDate().toString());
    currentDateLabel->setStyleSheet(CURRENT_DATE_FONT);

    timeDateWidget = new QWidget();
    timeDateLayout = new QGridLayout();
    timeDateLayout->addWidget(currentTimeLabel);
    timeDateLayout->addWidget(currentDateLabel);
    timeDateWidget->setLayout(timeDateLayout);

    // Add all widgets onto the layout group
    layout->addWidget(timeDateWidget, 0, 0);
    layout->addWidget(recipeWidget, 0, 1);
    layout->addWidget(ingredientWidget, 1, 1);
    layout->addWidget(kitchenwareWidget, 2, 1);

    // Find window setup
    window->setLayout(layout);
    window->setWindowTitle("Main Menu");
    window->show();
}

/**
 * @author: Bo Yuan Shi
 * @brief: Handles presses for the recipe button
 * Swaps the control from the main menu to the RecipeListWindow class, and closes the mainmenu window
 */
void mainMenu::HandleRecipeButtonPress() {
    auto *recipeListWindow = new RecipeListWindow(db);
    std::cout << "Recipe Button Pressed" << std::endl;
    window->hide();
}

/**
 * @author: Bo Yuan Shi
 * @brief: Handles presses for the ingredient button
 * Swaps the control from the main menu to the IngredientInventoryWindow class, and closes the mainmenu window
 */
void mainMenu::HandleIngredientButtonPress() {
    auto *IngredientInventoryWindowPointer = new IngredientInventoryWindow(db);
    std::cout << "Ingredient Button Pressed" << std::endl;
    window->hide();
}

/**
 * @author: Bo Yuan Shi
 * @brief: Handles presses for the kitchenware button
 * Swaps the control from the main menu to the KitchenwareInventory class, and closes the mainmenu window
 */
void mainMenu::HandleKitchenwareButtonPress() {
    window->hide();
    std::cout << "Kitchenware Button Pressed" << std::endl;
    KitchenWindow *kitchenWindow = new KitchenWindow(new KitchenwareInventory(db->getKitchenWareInventory()), db);
}

/**
 * @author: Bo Yuan Shi
 * @brief: Deconstructor for the main menu class
 * Deconstructs this class when it is no longer needed
 */
mainMenu::~mainMenu(){}