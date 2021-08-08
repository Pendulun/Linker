#include "ligador.hpp"
#include <iostream>
#include <fstream>
#include <list>
#include <iterator>

int main(int argc, char *argv[]) {
    std::ofstream saida = std::ofstream("executavel.mv");

    if (argc > 1){
        if(saida.is_open()){
            bool abriuTodos = true;

            Ligador linker(saida);

            //Passo 1 
            for(int i = 1; i<argc; i++){
                std::ifstream entrada = std::ifstream(argv[i]);
                if (entrada.is_open()){
                    std::cout<<"Abriu arquivo : "<<argv[i]<<" no passo 1\n";

                    linker.lerTamanhoETabelaDoArquivo(entrada, argv[i]);

                    entrada.close();
                }else{
                    std::cout<<"Nao foi possivel abrir o arquivo: "<<argv[i]<<"\n";
                    abriuTodos=false;
                    break;
                }
            }

            linker.escreveTabelaDeSimbolos();

            //Passo 2
            if(abriuTodos){
                for(int i = 1; i<argc; i++){
                    std::ifstream entrada = std::ifstream(argv[i]);
                    if (entrada.is_open()){
                        std::cout<<"Abriu arquivo : "<<argv[i]<<" no passo 2\n";
                        //Envia o arquivo para o passo 2 do Ligador 
                        entrada.close();
                    }else{
                        std::cout<<"Nao foi possivel abrir o arquivo: "<<argv[i]<<"\n";
                        abriuTodos=false;
                        break;
                    }
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
