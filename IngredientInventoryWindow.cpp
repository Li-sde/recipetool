/**
 * @brief This class display the ingredient Inventory Window that lists all Ingredients avaiable in stock
 * And can be redirect to ingredient add window and ingredient detail window
 * @author Xingjian Mao
 * @date 2021/11/30
 */

#include "IngredientInventoryWindow.h"
using namespace std;


/**
 * @brief This method is the constructor of the class, by calling it creates a ingredient inventory
 * window based on parameter DataBase
 * @param *DataBp target database
 *
 */
IngredientInventoryWindow::IngredientInventoryWindow(DataBase *DataBp){
    DataB = DataBp;
    MainLayout->setSpacing(0);
    MainLayout->setMargin(0);
    IngredientInventoryW->setWindowTitle("Ingredient Inventory");
    IngredientInventoryW->setFixedSize(1280, 800);
    IngredientInventoryW->setLayout(MainLayout);
    IngredientInventoryW->setStyleSheet("QWidget {background-color: #FFFFFF }");
    setTitle();
    setMain();
    IngredientInventoryW->show();


}


/**
 * @brief This method sets the title of this window
 *
 */
void IngredientInventoryWindow::setTitle(){

    Title->setLayout(TitleLayout);
    Title->setFixedHeight(90);
    Title->setStyleSheet(
            "QGroupBox { background-color: #FFFFFF; padding: 0 64px; border: 0} "
            "QLabel { font-size: 40px; font-weight: bold; background-color: transparent; color:#C37000} "
            "QPushButton { font-size: 20px; background-color: transparent; color: #C37000;} ");

    auto *Titletxt = new QLabel("Ingredient Inventory");
    auto *BackButton = new QPushButton("  Back");
    BackButton->setIcon(QIcon("assets/icons/left-brown.svg"));
    BackButton->setStyleSheet(" ");
    BackButton->setIconSize(QSize(32,32));
    auto *AddButton = new QPushButton("  Add");
    AddButton->setIcon(QIcon("assets/icons/add.svg"));
    AddButton->setStyleSheet(" ");
    AddButton->setIconSize(QSize(32, 32));

    connect(AddButton, SIGNAL(clicked()), SLOT(LinkAddWindow()));
    connect(BackButton, SIGNAL(clicked()), SLOT(OpenMainMenu()));
    TitleLayout->addWidget(BackButton, 0, 0, 1, 1, {Qt::AlignLeft});
    TitleLayout->addWidget(Titletxt, 0, 1, 1, 1, {Qt::AlignCenter});
    TitleLayout->addWidget(AddButton, 0,2,1,1, {Qt::AlignRight});

    MainLayout->addWidget(Title);
    MainLayout->addWidget(Main);

}

/**
 * @brief This method sets the main body of the window, including showing all ingredient name
 * and make them as a button to access its detailed window
 *
 */
void IngredientInventoryWindow::setMain(){

    Main->setStyleSheet("QGroupBox { background-image:url(\"assets/img/background.png\"); border: 0; padding: 0 64px}");
    unordered_map<std::string, int> IngInv = DataB->getIngredientInventory();
    unordered_map<std::string, int>::iterator iter = IngInv.begin();


    int row = 0;
    int col = 0;
    while (iter != IngInv.end()){
        string IngredientID = iter->first;
        std::cout << IngredientID << std::endl;
        Ingredient *ING = DataB->getIngredientByID(IngredientID);
        QPushButton *IngredientButton = new QPushButton(QString::fromStdString(ING->get_ingredient_name()));
        IngredientButton->setStyleSheet("border-radius:10px; background-color: white; color: #5F3600; font-size: 20px;height: 100px; ");
        IngredientButton->setObjectName(QString::fromStdString(IngredientID));
        connect(IngredientButton, SIGNAL(clicked()), this, SLOT(LinkDetailWindow()));
        InventoryLayout->addWidget(IngredientButton, row, col, 1, 1);
        col += 1;
        if (col == 4){
            col =  0;
            row += 1;
        }
        iter++;
    }


    InventoryLayout->setMargin(0);
    MainLayout->addStretch();
    Main->setLayout(InventoryLayout);

    MainBodyScroll->setStyleSheet("QScrollArea { border: 0; }");
    MainBodyScroll->verticalScrollBar()->setStyleSheet("QScrollBar {width:0px;}");
    MainBodyScroll->setWidgetResizable(true);
    MainBodyScroll->setMinimumHeight(IngredientInventoryW->height() - 90);
    MainBodyScroll->setWidget(Main);
    MainLayout->addWidget(MainBodyScroll);
}


/**
 * @brief This method links the ingredient button to its corresponding Detail window
 *
 */
void IngredientInventoryWindow::LinkDetailWindow(){
    QWidget *w = qobject_cast<QWidget *>(sender());
    IngredientDetail *W = new IngredientDetail(w->objectName().toStdString(), DataB);

};

/**
 * @brief This method links the add button to the add window
 *
 */
void IngredientInventoryWindow::LinkAddWindow() {
    IngredientInventoryW->close();
    IngredientAdd *W = new IngredientAdd(DataB);
}

/**
 * @brief This is the destructor of the class
 *
 */
IngredientInventoryWindow::~IngredientInventoryWindow(){}

/**
 * @brief This method refeshes the ingredient window if any ingredient is destroied
 *
 */
void IngredientInventoryWindow::widgetDestroyed(QObject *q) {
    IngredientInventoryW->show();
}

/**
 * @brief This method links the back button to the main menu
 */
void IngredientInventoryWindow::OpenMainMenu() {
    IngredientInventoryW->close();
    auto *main = new mainMenu(DataB);
};