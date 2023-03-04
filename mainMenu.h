/**
 * @author: Bo Yuan Shi
 * @brief: The header file for the main menu class
 * Header file for the main menu class that contains all needed libraries
 */

#ifndef GROUP23_MAINMENU_H
#define GROUP23_MAINMENU_H

#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QGroupBox>
#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QObject>
#include <QTime>
#include <QTimer>
#include "main.h"
#include "DataBase.h"

/**
 * @brief Mainmenu class, responsible for the main menu.
 */
class mainMenu : public QMainWindow {
    Q_OBJECT
public:
    mainMenu(DataBase *DB);
    ~mainMenu();
private slots:
    void HandleRecipeButtonPress();
    void HandleIngredientButtonPress();
    void HandleKitchenwareButtonPress();
private:
    DataBase *db;

    QWidget *window;
    QGridLayout *layout;

    QGridLayout *timeDateLayout;
    QWidget *timeDateWidget;
    QLabel *currentDateLabel;
    QLabel *currentTimeLabel;
    QTimer *timer;

    QWidget *recipeWidget;
    QGridLayout *recipeLayout;
    QPushButton *recipeButton;
    QLabel *recipeLayoutTitle;
    QLabel *recipeLayoutText;

    QWidget *ingredientWidget;
    QGridLayout *ingredientLayout;
    QPushButton *ingredientButton;
    QLabel *ingredientLayoutTitle;
    QLabel *ingredientLayoutText;

    QWidget *kitchenwareWidget;
    QGridLayout *kitchenwareLayout;
    QPushButton *kitchenwareButton;
    QLabel *kitchenwareLayoutTitle;
    QLabel *kitchenwareLayoutText;
};

#endif //GROUP23_MAINMENU_H
