#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include <QMainWindow>
#include <iostream>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void updateInterfaceTremLar(int,int,int);
    void updateInterfaceTremPreto(int,int,int);
    void updateInterfaceTremVer(int,int,int);
    void updateInterfaceTremAzul(int,int,int);

private:
    Ui::MainWindow *ui;
    Trem *tremVer;
    Trem *tremPreto;
    Trem *tremAzul;
    Trem *tremLar;
};

#endif // MAINWINDOW_H
