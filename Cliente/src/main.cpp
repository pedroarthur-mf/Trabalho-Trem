#include "BlackGPIO.h"

#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>
#include <iomanip>
#include <time.h>
#include <sys/types.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>      //memset
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close

#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"


#define MAXMSG 1024
#define MAXNAME 100
#define PORTNUM 4325


class Mensagem {
public:
	int func;
	int id;
	int speed;
	Mensagem() {}
};

int readAnalog(int number) {
	std::stringstream ss;
	ss << PATH_ADC << number << "_raw";
	std::fstream fs;
	fs.open(ss.str().c_str(), std::fstream::in);
	fs >> number;
	fs.close();
	return number;
}

int main(int argc, char * argv[]){
	// Button to confirm the player's try.
	BlackLib::BlackGPIO   btnMain(BlackLib::GPIO_115,BlackLib::input);

	struct sockaddr_in endereco;
	int socketId;

	Mensagem mensagem;
	int bytesenviados;

	memset(&endereco, 0, sizeof(endereco));
	endereco.sin_family = AF_INET;
	endereco.sin_port = htons(PORTNUM);

	endereco.sin_addr.s_addr = inet_addr("192.168.7.1");

	socketId = socket(AF_INET, SOCK_STREAM, 0);

	if (socketId == -1){
		printf("Falha ao executar socket()\n");
		exit(EXIT_FAILURE);
	}

    //Conectando o socket cliente ao socket servidor
	if ( connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ){
		printf("Falha ao executar connect()\n");
		exit(EXIT_FAILURE);
	}

	printf ("Cliente conectado ao servidor\n");
	sleep(1);
	system("clear");


	while(1){
		//func == 1-Parar todos os trens 2-Parar trem especifico, 3- mudar velocidade de um trem espefifico.
		std::cout << "Escolha o número da função escolhida" << std::endl;
		std::cout << "\t1- Iniciar/Parar todos os trens.\n\t2- Parar trem especifico.\n\t3- Mudar velocidade de um trem espefifico." << std::endl;
		std::cin >> mensagem.func;
		if(mensagem.func != 1){
			std::cout << "\nEscolha o número do trem que se deseja alterar" << std::endl;
			std::cout << "\t1- Trem Laranja\n\t2-Trem Vermelho\n\t3- Trem Azul\n\t4- trem Preto" << std::endl;
			int a;
			std::cin >> a;
			if(a == 1){
				mensagem.id = 2;
			}
			else if(a == 2){
				mensagem.id = 1;
			}
			else{
				mensagem.id = a;
			}
		} 
		if(mensagem.func == 3){
			std::cout << "Gire o k-nob para escolher a velocidade do trem." << std::endl;
		}
		std::cout << "Aperte o botão para confirmar"<<std::endl;
		while(1){
			if(btnMain.getNumericValue()){
				if(mensagem.func == 3){
					mensagem.speed = readAnalog(1);
					mensagem.speed = ((mensagem.speed*300)/4096) + 1;
				}
				//Enviar uma msg para o cliente que se conectou
				printf("Cliente vai enviar uma mensagem\n");
				bytesenviados = send(socketId,&mensagem,sizeof(mensagem),0);
				if (bytesenviados == -1){
					printf("Falha ao executar send()");
					exit(EXIT_FAILURE);
				}	
				break;
			}
		}
		break;
	}

	close(socketId);
	return EXIT_SUCCESS;
}
