#include "trem.h"

Trem::Trem(int id, int x, int y, std::pair<int,int> ponto){
    this->id = id;
    this->x = x;
    this->y = y;
    this->altura = 100;
    this->largura = 140;
    this->ponto = ponto;
    velocidade = 250;
    enable = true;
}

Trem::~Trem()
{
    threadTrem.join();
}

void Trem::setVelocidade(int velocidade)
{
    this->velocidade = velocidade;
}

void Trem::setEnable(bool enable)
{
    this->enable = enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

void Trem::run()
{
    while(true){
        switch(id){
        case 1:
            if (enable)
            {
                emit updateGUI(1,x,y);
                if (y == this->ponto.second && x < (this->ponto.first + largura))//direita
                    x+=10;
                else if (x == (this->ponto.first + largura) && y < (this->ponto.second + altura))//baixo
                    y+=10;
                else if (x > this->ponto.first && y == (this->ponto.second + altura))//esquerda
                    x-=10;
                else//cima
                    y-=10;
            }
            break;
        case 2:
            if (enable)
            {
                emit updateGUI(1,x,y);
                if (y == (this->ponto.second + altura) && x < (this->ponto.first + largura))//direita
                    x+=10;
                else if (x == this->ponto.first && y < (this->ponto.second + altura))//baixo
                    y+=10;
                else if (x > this->ponto.first && y == this->ponto.second)//esquerda
                    x-=10;
                else
                    y-=10;
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

