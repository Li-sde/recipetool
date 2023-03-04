//
// Created by Jerry Mao on 2021-11-27.
//

#ifndef GROUP23_INGREDIENTADD_H
#define GROUP23_INGREDIENTADD_H
#include <QPushButton>
#include <QGridLayout>
#include <QStackedLayout>
#include <QLabel>
#include <QTextBlock>
#include <QLineEdit>
#include <QObject>
#include <QMainWindow>
#include <QTextEdit>
#include <QGroupBox>
#include <QListWidget>
#include <QScrollBar>
#include <QColor>
#include <string>
#include <QStyle>
#include <QFont>
#include <QScrollArea>
#include <QComboBox>
#include <QMessageBox>
#include "IngredientInventory.h"
#include "DataBase.h"
#include "main.h"

/**
 *  @brief This class creates the ingredient add window allows user add new ingredient into the database
 */
class IngredientAdd : public QWidget{
Q_OBJECT
private:
    DataBase *DB;
    IngredientInventory *Inv;
    QWidget *IngredientAddW = new QWidget();
    QVBoxLayout *IngredientAddLayout = new QVBoxLayout();
    QGroupBox *IngredientList = new QGroupBox();
    QGroupBox *Body = new QGroupBox();
    QVBoxLayout *BodyLayout = new QVBoxLayout();
    std::unordered_map<QComboBox*, QLineEdit*> Ingredient_map;
    void SelectIngredient();
    QGroupBox *IngredientAddRow();

    private slots:
        void IngredientNewSubmit();
        void showIngredientWindow();

public:
    IngredientAdd(DataBase *db);
    ~IngredientAdd();

};


#endif //GROUP23_INGREDIENTADD_H
