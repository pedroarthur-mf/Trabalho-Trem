#include "trilho.h"

Trilho::Trilho(int x, int y, int altura, int largura){
    this->x = x;
    this->y = y;
    this->altura = altura;
    this->largura = largura;
}

int Trilho::getAltura(){
    return altura;
}

int Trilho::getLargura(){
    return largura;
}

int Trilho::getX(){
    return x;
}

int Trilho::getY(){
    return y;
}

std::pair<int,int> Trilho::getPSE(){
    std::pair<int, int> pse;
    pse.first = x;
    pse.second = y;
    return pse;
}

std::pair<int,int> Trilho::getPSD(){
    std::pair<int, int> psd;
    psd.first = x+largura;
    psd.second = y;
    return psd;
}

std::pair<int,int> Trilho::getPIE(){
    std::pair<int,int> pie;
    pie.first = x;
    pie.second = y+altura;
    return pie;
}

std::pair<int,int> Trilho::getPID(){
    std::pair<int,int> pid;
    pid.first = x+largura;
    pid.second = y+altura;
    return pid;
}
