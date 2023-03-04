/**
 * main.cpp
 * @authors Jiaao Cai, Jingxing Li, Xingjian Mao, Bo Yuan Shi, Donald Cheng Hong Zou
 */
#include "main.h"

int main(int argc, char *argv[]) {
    auto *DB = new DataBase();
    QApplication app(argc, argv);
    auto *main = new mainMenu(DB);
    QApplication::setQuitOnLastWindowClosed(false);
    QApplication::exec();
}