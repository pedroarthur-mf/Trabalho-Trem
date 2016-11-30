#ifndef TRILHO_H
#define TRILHO_H

#include <iostream>

class Trilho{
private:
    int x;
    int y;
    int largura;
    int altura;
public:
    Trilho(int x, int y, int altura, int largura);
    int getLargura();
    int getAltura();
    int getX();
    int getY();
    std::pair<int,int> getPSE();
    std::pair<int,int> getPSD();
    std::pair<int,int> getPIE();
    std::pair<int,int> getPID();
};

#endif // TRILHO_H
