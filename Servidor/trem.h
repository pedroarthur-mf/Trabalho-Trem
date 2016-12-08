#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <iostream>
#include <thread>
#include <chrono>
#include "semaforo.h"

using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int, std::pair<int,int>, Semaforo *, Semaforo *, Semaforo *, int);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);
    bool getEnable();
    bool isInS1();
    bool isInS2();
    bool isInS3();

signals:
    void updateGUI(int,int,int);

private:
   std::thread threadTrem;
   int largura;
   int altura;
   std::pair<int,int> ponto;
   int id;
   int x;
   int y;
   int velocidade;
   bool enable;
   Semaforo* s1;
   Semaforo* s2;
   Semaforo* s3;
   bool inS1;
   bool inS2;
   bool inS3;
};

#endif // TREM_H



