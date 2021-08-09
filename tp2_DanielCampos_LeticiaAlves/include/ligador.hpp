#ifndef LIGADOR_H
#define LIGADOR_H

#include <fstream>
#include <string>
#include <list>
#include <unordered_map>
#include <utility>
#include <iostream>

class Ligador{
    private:
        std::ofstream* saida;

        const unsigned int TAMANHOPILHA = 1000;
        unsigned int tamanhoTotal;
        unsigned int endCarregamento;
        unsigned int posAP;
        unsigned int entryPoint;
        std::unordered_map<std::string, unsigned int> tabelaSimbolos;

        
        void escreveCabecalhoArquivoSaida();
        void defineInformacoesArquivoSaida();
        
        int calculaEnderecoRelativo(unsigned int pc, unsigned int endereco);

    public:
        Ligador(std::ofstream& saida);
        ~Ligador();

        void lerTamanhoETabelaDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void completarInstrucoesDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void escreveTabelaDeSimbolos();
        void escreveInformacoesArquivoSaida();
        void passo2();

};

#endif
