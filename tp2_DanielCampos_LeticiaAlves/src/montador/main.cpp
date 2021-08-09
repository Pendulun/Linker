#include "montador.hpp"
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
    if (argc > 1){
        for (int i=1; i<argc; i++){
            std::ifstream entrada = std::ifstream();
            entrada.open(argv[i]);

            if (entrada.is_open() ){
                Montador montador(entrada);      
                montador.montar();
                //std::cout<<"Montando modulo "<<i<<std::endl;
                entrada.close();
            }else{
                std::cout<<"Nao foi possivel abrir o arquivo: "<<argv[i]<<".\n";
            }
        }
    }else{
        std::cout<<"Nenhum arquivo informado.\n";
        exit(1);
    }
    return 0;
}
