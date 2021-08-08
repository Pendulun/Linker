#include "montador.hpp"
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {

    if (argc > 1){

        for (int i=1; i<argc; i++){

            std::string prefixoSaida = (std::string)(argv[i]);
            prefixoSaida = prefixoSaida.substr(0, prefixoSaida.length()-4);

            std::string nomeSaida = prefixoSaida+".txt";

            std::ifstream entrada = std::ifstream();
            std::ofstream saida = std::ofstream(nomeSaida);

            entrada.open(argv[i]);

            if (entrada.is_open() && saida.is_open()){

                Montador montador(entrada, saida);      
                //montador.montar();
                std::cout<<"Montando modulo "<<i<<std::endl;

                entrada.close();
                saida.close();
            }
            else{
                std::cout<<"Nao foi possivel abrir o arquivo.\n";
            }

        }

    }
    else{
        std::cout<<"Nenhum arquivo informado.\n";
        exit(1);
    }

    return 0;
}
