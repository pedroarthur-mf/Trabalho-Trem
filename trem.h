#ifndef TREM_H
#define TREM_H

#include <QObject>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Trem : public QObject
{
    Q_OBJECT
public:
    Trem(int,int,int, std::pair<int,int>);
    ~Trem();
    void start();
    void run();
    void setVelocidade(int);
    void setEnable(bool);

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
};

#endif // TREM_H



