#include "mainwindow.h"
#include "ui_mainwindow.h"
class Mensagem {
public:
    int func;
    int id;
    int speed;
    Mensagem(){}
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->fstTime = true;

    semaforo1 = new Semaforo(1234,1,IPC_CREAT|0600);
    semaforo2 = new Semaforo(1245,1,IPC_CREAT|0600);
    semaforo3 = new Semaforo(1256,1,IPC_CREAT|0600);

    std::pair<int, int> p1;
    p1.first = 111;
    p1.second = 30;
    tremLar = new Trem(2,111,30, p1, semaforo1, semaforo2, semaforo3, 100);

    std::pair<int, int> p2;
    p2.first = 111;
    p2.second = 130;
    tremVer = new Trem(1,141,230, p2,semaforo1, semaforo2, semaforo3, 120);

    std::pair<int, int> p3;
    p3.first = 251;
    p3.second = 130;
    tremAzul = new Trem(3,391,130, p3, semaforo1, semaforo2, semaforo3, 110);

    std::pair<int, int> p4;
    p4.first = 251;
    p4.second = 230;
    tremPreto = new Trem(4,391,330, p4, semaforo1, semaforo2, semaforo3, 155);

    connect(tremLar,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremLar(int,int,int)));
    connect(tremVer,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremVer(int,int,int)));
    connect(tremAzul,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremAzul(int,int,int)));
    connect(tremPreto,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterfaceTremPreto(int,int,int)));

    tremVer->start();
    tremLar->start();
    tremPreto->start();
    tremAzul->start();

    run();

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

void MainWindow::socketServidor(){
    //variáveis do servidor
    struct sockaddr_in endereco;
    int socketId;

    //variáveis relacionadas com as conexões clientes
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    int conexaoClienteId;

    /*
     * Configurações do endereço
     */
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    //endereco.sin_addr.s_addr = INADDR_ANY;
    endereco.sin_addr.s_addr = inet_addr("192.168.7.1");

    socketId = socket(AF_INET, SOCK_STREAM, 0);

    Mensagem mensagem;
    int byteslidos;

    //Verificar erros
    if (socketId == -1)
    {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }

    //Conectando o socket a uma porta. Executado apenas no lado servidor
    if ( bind (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 )
    {
        printf("Falha ao executar bind()\n");
        exit(EXIT_FAILURE);
    }

    //Habilitando o servidor a receber conexoes do cliente
    if ( listen( socketId, 10 ) == -1)
    {
        printf("Falha ao executar listen()\n");
        exit(EXIT_FAILURE);
    }

    //servidor ficar em um loop infinito
    while(1)
    {

        printf("Servidor: esperando conexões clientes\n");

        //Servidor fica bloqueado esperando uma conexão do cliente
        conexaoClienteId = accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );

        printf("Servidor: recebeu conexão de %s\n", inet_ntoa(enderecoCliente.sin_addr));

        //Verificando erros
        if ( conexaoClienteId == -1)
        {
            printf("Falha ao executar accept()");
            exit(EXIT_FAILURE);
        }

        //receber uma msg do cliente
        printf("Servidor vai ficar esperando uma mensagem\n");
        byteslidos = recv(conexaoClienteId,&mensagem,sizeof(mensagem),0);

        if (byteslidos == -1)
        {
            printf("Falha ao executar recv()");
            exit(EXIT_FAILURE);
        }
        else if (byteslidos == 0)
        {
            printf("Cliente finalizou a conexão\n");
            exit(EXIT_SUCCESS);
        }
        if(mensagem.func == 1){
            if(tremVer->getEnable() && tremLar->getEnable() && tremAzul->getEnable() && tremPreto->getEnable()){
                tremVer->setEnable(false);
                tremLar->setEnable(false);
                tremAzul->setEnable(false);
                tremPreto->setEnable(false);
            }
            else{
                tremVer->setEnable(true);
                tremLar->setEnable(true);
                tremAzul->setEnable(true);
                tremPreto->setEnable(true);
            }
        }
        else if(mensagem.func == 2){
            if(mensagem.id == 1){
                if(tremVer->getEnable())
                    tremVer->setEnable(false);
                else tremVer->setEnable(true);
            }
            else if(mensagem.id == 2){
                if(tremLar->getEnable())
                    tremLar->setEnable(false);
                else tremLar->setEnable(true);
            }
            else if(mensagem.id == 3){
                if(tremAzul->getEnable())
                    tremAzul->setEnable(false);
                else tremAzul->setEnable(true);
            }
            else if(mensagem.id == 4){
                if(tremPreto->getEnable())
                    tremPreto->setEnable(false);
                else tremPreto->setEnable(true);
            }
        }
        else if(mensagem.func == 3){
            std::cout << "Velocidade: " << mensagem.speed << std::endl;
            if(mensagem.id == 1){
                tremVer->setVelocidade(mensagem.speed);
            }
            else if(mensagem.id == 2){
                tremLar->setVelocidade(mensagem.speed);
            }
            else if(mensagem.id == 3){
               tremAzul->setVelocidade(mensagem.speed);
            }
            else if(mensagem.id == 4){
                tremPreto->setVelocidade(mensagem.speed);
            }
        }
    }
    ::close(conexaoClienteId);
}

void MainWindow::guiSem(){
    while(true){
        QString s1Value = QString::number(semaforo1->getContador());
        QString s2Value = QString::number(semaforo2->getContador());
        QString s3Value = QString::number(semaforo3->getContador());
        this->ui->s1Value->setText(s1Value);
        this->ui->s2Value->setText(s2Value);
        this->ui->s3Value->setText(s3Value);

        if(tremAzul->isInS1()){
            ui->tremInS1->setText("Trem Azul");
        }else if(tremPreto->isInS1()){
            ui->tremInS1->setText("Trem Preto");
        }else{
            ui->tremInS1->setText("Nenhum Trem");
        }

        if(tremLar->isInS3()){
            ui->tremInS3->setText("Trem Laranja");
        }else if(tremVer->isInS3()){
            ui->tremInS3->setText("Trem Vermelho");
        }else{
            ui->tremInS3->setText("Nenhum trem");
        }

        if(tremVer->isInS2()){
            ui->tremInS2->setText("Trem Vermelho");
        }else if(tremAzul->isInS2()){
            ui->tremInS2->setText("Trem Azul");
        }else{
            ui->tremInS2->setText("Nenhum trem");
        }
    }
}

void MainWindow::run(){
    if(this->fstTime){
        this->thSocket = std::thread(&MainWindow::socketServidor,this);
        this->thGuiSem = std::thread(&MainWindow::guiSem, this);
        this->fstTime = false;
    }
}


