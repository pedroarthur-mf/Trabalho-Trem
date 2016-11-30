#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::pair<int, int> p1;
    p1.first = 111;
    p1.second = 30;
    tremLar = new Trem(2,111,30, p1);

    std::pair<int, int> p2;
    p2.first = 111;
    p2.second = 130;
    tremVer = new Trem(1,111,230, p2);

    std::pair<int, int> p3;
    p3.first = 251;
    p3.second = 130;
    tremAzul = new Trem(1,391,130, p3);

    std::pair<int, int> p4;
    p4.first = 251;
    p4.second = 230;
    tremPreto = new Trem(1,391,330, p4);

    connect(tremLar,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremLar(int,int,int)));
    connect(tremVer,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremVer(int,int,int)));
    connect(tremAzul,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremAzul(int,int,int)));
    connect(tremPreto,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremPreto(int,int,int)));

    tremVer->start();
    tremLar->start();
    tremPreto->start();
    tremAzul->start();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::updateInterfaceTremLar(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->TremLaranja->setGeometry(x,y,20,20);
            break;
        case 2:
            break;
        default:
            break;
    }
}

void MainWindow::updateInterfaceTremVer(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->TremVermelho->setGeometry(x,y,20,20);
            break;
        case 2:
            break;
        default:
            break;
    }
}

void MainWindow::updateInterfaceTremAzul(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->TremAzul->setGeometry(x,y,20,20);
            break;
        case 2:
            break;
        default:
            break;
    }
}

void MainWindow::updateInterfaceTremPreto(int id, int x, int y)
{
    switch(id){
        case 1:
            ui->TremPreto->setGeometry(x,y,20,20);
            break;
        case 2:
            break;
        default:
            break;
    }
}


