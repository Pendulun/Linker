#include "ligador.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>

int main(int argc, char *argv[]) {

    if (argc > 1){
            bool abriuTodos = true;

            Ligador linker;

            //Passo 1 
            for(int i = 1; i<argc; i++){
                std::ifstream entrada = std::ifstream(argv[i]);
                if (entrada.is_open()){
                    linker.lerTamanhoETabelaDoArquivo(entrada, argv[i]);

                    entrada.close();
                }else{
                    std::cout<<"Nao foi possivel abrir o arquivo: "<<argv[i]<<"\n";
                    abriuTodos=false;
                    break;
                }
            }

            //Passo 2
            if(abriuTodos){
                linker.escreveInformacoesArquivoSaida();
                for(int i = 1; i<argc; i++){
                    std::ifstream entrada = std::ifstream(argv[i]);
                    if (entrada.is_open()){
                        linker.completarComInstrucoesDoArquivo(entrada, argv[i]);
                        entrada.close();
                    }else{
                        std::cout<<"Nao foi possivel abrir o arquivo: "<<argv[i]<<"\n";
                        abriuTodos=false;
                        break;
                    }
                }
            } 
    }else{
        std::cout<<"Nenhum arquivo de entrada foi informado.\n";
        return 1;
    }
    return 0;
}
