#include "montador.hpp"
#include <string>

int main(int argc, char *argv[]) {

    if (argc > 1){

        for (int i=1; i<argc; i++){

            std::string nomeSaida = (std::string)(argv[i])+".txt";

            std::ifstream entrada = std::ifstream();
            std::ofstream saida = std::ofstream(nomeSaida);

            entrada.open(argv[i]);

            if (entrada.is_open() && saida.is_open()){

                Montador montador(entrada, saida);      
                montador.montar();

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
