#include "trem.h"

Trem::Trem(int id, int x, int y, std::pair<int,int> ponto, Semaforo *s1, Semaforo *s2, Semaforo *s3, int velocidade){
    this->id = id;
    this->x = x;
    this->y = y;
    this->altura = 100;
    this->largura = 140;
    this->ponto = ponto;
    this->velocidade = velocidade;
    this->enable = false;
    this->s1 = s1;
    this->s2 = s2;
    this->s3 = s3;
    this->inS1 = false;
    this->inS2 = false;
    this->inS3 = false;
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

bool Trem::getEnable()
{
    return this->enable;
}

void Trem::start()
{
    threadTrem = std::thread(&Trem::run,this);
}

bool Trem::isInS1(){
    return this->inS1;
}

bool Trem::isInS2(){
    return this->inS2;
}


bool Trem::isInS3(){
    return this->inS3;
}
void Trem::run()
{
    while(true){
        //Sentido horário
        if(id == 1){
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
            // Entrando na região crítica de S3
            if(x == 111 && y == 140){
//                std::cout << "Trem " << id << " deu P em S3\n";
                this->s3->P();
            }
            // Entrando na região crítica S2
            if(x == 241 && y == 130){
//                std::cout << "Trem " << id << " deu P em S2\n";
                this->s2->P();
            }

            //Saindo da reigão crítica S3
            if(x == 251 && y == 140){
//                std::cout << "Trem " << id << " deu V em S3\n";
                this->s3->V();
            }


            //Saindo da reigão crítica S2
            if(x == 241 && y == 230){
//                std::cout << "Trem " << id << " deu V em S2\n";
                this->s2->V();
            }

            // Está em S2
            if(x == 251 && (y > 130 && y < 230)){
                this->inS2 = true;
            }else{
                this->inS2 = false;
            }

            // Está em S3
            if((x > 111 && x < 251) && y == 130 ){
                this->inS3 = true;
            }else{
                this->inS3 = false;
            }
        }
        // Sentindo horário:
        else if(id == 3){
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
            // Entrando na região crítica de S1
            if(x == 391 && y == 220){
//                std::cout << "Trem " << id << " deu P em S1\n";
                this->s1->P();
            }
            //Verificar que saiu
            if(x == 251 && y == 210){
//                std::cout << "Trem " << id << " deu V em S1\n";
                this->s1->V();
            }

            // Entrando na região crítica S2
            if(x == 261 && y == 230){
//                std::cout << "Trem " << id << " deu P em S2\n";
                this->s2->P();
            }

            //Saindo da reigão crítica S2
            if(x == 261 && y == 130){
//                std::cout << "Trem " << id << " deu V em S2\n";
                this->s2->V();
            }

            // Está em S2
            if(x == 251 && (y > 130 && y < 230)){
                this->inS2 = true;
            }else{
                this->inS2 = false;
            }

            // Está em S1
            if((x > 251 && x < 391 ) && y == 230){
                this->inS1 = true;
            }else{
                this->inS1 = false;
            }

        }
        //Sentido horário
        else if(id == 4){
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
            // Entrando na região crítica de S1
            if(x == 251 && y == 240){
//                std::cout << "Trem " << id << " deu P em S1\n";
                this->s1->P();
            }

            //Saindo da reigão crítica
            if(x == 391 && y == 240){
//                std::cout << "Trem " << id << " deu V em S1\n";
                this->s1->V();
            }

            // Está em S1
            if((x > 251 && x < 391 ) && y == 230){
                this->inS1 = true;
            }else{
                this->inS1 = false;
            }
        }
        // Sentido anti-horário
        else{
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

            // Entrando na região crítica de S3
            if(x == 111 && y == 120){
//                std::cout << "Trem " << id << " deu P em S3\n";
                this->s3->P();
            }

            // Saindo da região crítica
            if(x == 251 && y == 120){
//                std::cout << "Trem " << id << " deu V em S3\n";
                this->s3->V();
            }

            // Entrando na região crítica S2
            if(x == 241 && y == 130){
//                std::cout << "Trem " << id << " deu P em S2\n";
                this->s2->P();
            }

            //Saindo da reigão crítica S2
            if(x == 251 && y == 120){
//                std::cout << "Trem " << id << " deu V em S2\n";
                this->s2->V();
            }
            // Está em S3
            if((x > 111 && x < 251) && y == 130 ){
                this->inS3 = true;
            }else{
                this->inS3 = false;
            }
        }
        this_thread::sleep_for(chrono::milliseconds(velocidade));
    }
}

