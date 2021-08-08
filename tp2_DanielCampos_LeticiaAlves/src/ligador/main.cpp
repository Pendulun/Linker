#include "ligador.hpp"
#include <iostream>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ofstream saida = std::ofstream("executavel.mv");

    if (argc > 1){
        if(saida.is_open()){
            for(int i = 1; i<argc; i++){
                std::ifstream entrada = std::ifstream(argv[i]);
                if (entrada.is_open()){

                    /*
                    Montador montador(entrada, saida);      
                    montador.montar();
                    */
                   std::cout<<"Abriu arquivo : "<<argv[i]<<"\n";
                    entrada.close();
                }else{
                    std::cout<<"Nao foi possivel abrir o arquivo: "<<argv[i]<<"\n";
                    break;
                }
            }
            saida.close();
        }else{
            std::cout<<"Nao foi possivel abrir o arquivo de saida\n";
        }   
    }else{
        std::cout<<"Nenhum arquivo de entrada foi informado.\n";
        return 1;
    }
    return 0;
}
