/**
* Creating a window for Recipe List and user can search recipe with keywords
*@author Jiaao Cai
*@date 2021/11/30
*/


#include "RecipeListWindow.h"
#include "RecipeAddWindow.h"
#include "RecipeWindow.h"
#include "main.h"
/**
*@brief This function is constructor for this class ,by calling it creates a Recipe List window based on DataBase
* @param DataBase* db need to input database in this window
* 
*/
RecipeListWindow::RecipeListWindow(DataBase* db)
{
    DB = db;
    MainLayout->setSpacing(0);
    Recipe_List_Window->setWindowTitle("Recipes");
    Recipe_List_Window->setFixedSize(1280, 800);
    Recipe_List_Window->setLayout(MainLayout);
    Recipe_List_Window->setStyleSheet("QWidget { background-image:url(\"assets/img/background.png\") }");
    MainLayout->setMargin(0);
    RecipeListWindowNav();
    Recipe_List_Window->show();
    Recipe_List_Window->setStyleSheet("QPushButton{color: #C37000} ");
}

RecipeListWindow::~RecipeListWindow() {}

/**
*@brief This function is help create window, and add all layout into box
*/
void RecipeListWindow::RecipeListWindowNav() {
    RecipeListWindowNavBody();

    RecipeListWindowSerchBar();
    MainLayout->addWidget(NavBox);
    MainLayout->addWidget(searchBox);
    RecipeList();
}

/**
*@brief This function is create serch bar and in bar have serch input place, determine button.
*/
void RecipeListWindow::RecipeListWindowSerchBar() {
    auto* m_button = new QPushButton("Search");
    // set size and location of the button
    m_button->setStyleSheet("background-color: #C37000; color: white; font-size: 20px; padding: 16px 32px; border-radius: 10px");
    // Connect button signal to appropriate slot
    connect(m_button, &QPushButton::released, this, &RecipeListWindow::handleButton);

    //input place
    text->setStyleSheet("background-color: #BCBCBC; color: #707070; border: none; font-size: 20px; padding: 16px 32px; border-radius:10px;");
    text->setPlaceholderText("Input Keywords");

    SerchLayout->addWidget(text);
    SerchLayout->addWidget(m_button);
    searchBox->setStyleSheet("background-color: white; border: 0; padding: 0 64px;");
    searchBox->setLayout(SerchLayout);
}

/**
*@brief This function is create main title bar with name:Recipes add and back button 
*/
void RecipeListWindow::RecipeListWindowNavBody() {

    // Nav Title
    auto* NavTitle = new QLabel("Recipes");
    NavTitle->setStyleSheet("color: #C37000; font-size: 40px; font-weight: bold");
    // Nav Back Button
    auto* BackButton = new QPushButton("  Back");
    BackButton->setIcon(QIcon("assets/icons/left-brown.svg"));
    BackButton->setStyleSheet(" ");
    BackButton->setIconSize(QSize(32, 32));
    connect(BackButton, &QPushButton::released, this, &RecipeListWindow::handleBackButton);
    auto* AddButton = new QPushButton("  Add");
    AddButton->setIcon(QIcon("assets/icons/add.svg"));//
    AddButton->setStyleSheet(" ");
    AddButton->setIconSize(QSize(32, 32));
    connect(AddButton, &QPushButton::released, this, &RecipeListWindow::handleAddButton);

    // Add Widget for button title and placeholder(info prompt)
    NavLayout->addWidget(BackButton, 0, 0, 1, 1, { Qt::AlignLeft });
    NavLayout->addWidget(AddButton, 0, 2, 1, 1, { Qt::AlignRight });//
    NavLayout->addWidget(NavTitle, 0, 1, 1, 1, { Qt::AlignCenter });
    NavBox->setMinimumHeight(90);
    NavBox->setStyleSheet("QGroupBox{background-color: white; border: 0; padding: 0 64px;} QPushButton { font-size: 20px; color: #C37000; background-color: white; border: 0; }");
    NavBox->setLayout(NavLayout);
}

/**
*@brief This function is help make first recipe list when use first open this window
*/
void RecipeListWindow::RecipeList() {
    vector<recipe*> rec = DB->getAllRecipe();
    int row = 0;
    for (recipe* i: rec) {
        auto* InventoryButton = new QPushButton(QString::fromStdString(i->get_recipe_name()));
        InventoryButton->setObjectName(QString::fromStdString(i->get_recipe_id()));
        InventoryButton->setCursor(Qt::PointingHandCursor);
        connect(InventoryButton, SIGNAL(clicked()), SLOT(handleInventoryButton()));
        InventoryButton->setStyleSheet("background-color:#ffffff; color: #5F3600; font-size: 20px;border-radius:10px");
        InventoryButton->setFixedSize(QSize(640, 100));
        MainListLayout->addWidget(InventoryButton, row, 0, 1, 1,{Qt::AlignCenter});
        row++;
    }
    MainList->setStyleSheet("QGroupBox { border: none; }");
    MainList->setLayout(MainListLayout);
    MainBodyScroll->setWidget(MainList);
    MainBodyScroll->setStyleSheet("QScrollArea { border: none; background-image:url(\"assets/img/background.png\"); }");
    MainBodyScroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    MainBodyScroll->setWidgetResizable(true);
    MainBodyScroll->setMinimumHeight(Recipe_List_Window->height() - NavBox->height());
    MainLayout->addWidget(MainBodyScroll);
}

/**
*@brief This function is help when use push serch button make a new list of recipe with keywords
*
*/
void RecipeListWindow::handleButton()
{
    MainLayout->removeWidget(MainList);
    MainList = new QGroupBox();
    vector<recipe*> rec = DB->searchRecipe(text->text().toStdString());
    MainListLayout = new QGridLayout();
    int row = 0;
    for (recipe* i: rec) {
        auto* InventoryButton = new QPushButton(QString::fromStdString(i->get_recipe_name()));
        InventoryButton->setObjectName(QString::fromStdString(i->get_recipe_id()));

        connect(InventoryButton, SIGNAL(clicked()), SLOT(handleInventoryButton()));
        InventoryButton->setStyleSheet("background-color:#ffffff; color: #5F3600; font-size: 20px;border-radius:10px");
        InventoryButton->setFixedSize(QSize(640, 100));
        MainListLayout->addWidget(InventoryButton, row, 0, 1, 1,{Qt::AlignCenter});
        row++;
    }
    MainList->setStyleSheet("QGroupBox { border: none; }");
    MainList->setLayout(MainListLayout);
    MainBodyScroll->setWidget(MainList);
    MainBodyScroll->setStyleSheet("QScrollArea { border: none; background-image:url(\"assets/img/background.png\"); }");

}

/**
*@brief This function is help get back to main window
*/
void RecipeListWindow::handleBackButton() {
    WindowHide();
    mainMenu* main = new mainMenu(DB);
}

/**
*@brief This function is help to add a new recipe
*/
void RecipeListWindow::handleAddButton() {
    auto* newWindow = new RecipeAddWindow(DB);
    newWindow->WindowShow();
}

/**
*@brief This function is help every recipe button link to it's recipe window
*/
void RecipeListWindow::handleInventoryButton() {
    std::cout << "clicked" << std::endl;
    QWidget* button = qobject_cast<QWidget*>(sender());
    auto* NewWindow = new RecipeWindow(DB->getRecipeByID(button->objectName().toStdString()), DB,
                                       reinterpret_cast<RecipeWindow *>(this));
    NewWindow->WindowShow();  
}

/**
*@brief This function is let other window open this window
*/
void RecipeListWindow::WindowShow() {
    this->Recipe_List_Window->show();
}

/**
*@brief This function is help tp close this window
*/
void RecipeListWindow::WindowHide() {
    this->Recipe_List_Window->hide();
}


