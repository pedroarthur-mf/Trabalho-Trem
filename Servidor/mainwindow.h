#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "trem.h"
#include "semaforo.h"
#include <thread>
#include <QMainWindow>
#include <iostream>
#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close

#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325

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
    void socketServidor();
    void guiSem();

public slots:
    void updateInterfaceTremLar(int,int,int);
    void updateInterfaceTremPreto(int,int,int);
    void updateInterfaceTremVer(int,int,int);
    void updateInterfaceTremAzul(int,int,int);

signals:
    void signalThSocket();
    void signalThGuiSem();
private:
    Ui::MainWindow *ui;
    Trem *tremVer;
    Trem *tremPreto;
    Trem *tremAzul;
    Trem *tremLar;
    std::thread thSocket;
    std::thread thGuiSem;
    bool fstTime;

    Semaforo *semaforo1;
    Semaforo *semaforo2;
    Semaforo *semaforo3;
    void run();
};

#endif // MAINWINDOW_H
