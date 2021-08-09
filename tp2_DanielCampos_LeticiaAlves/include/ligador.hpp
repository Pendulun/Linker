#ifndef LIGADOR_H
#define LIGADOR_H

#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <unordered_map>
#include <utility>
#include <iostream>
#include <sstream>

class Ligador{
    private:
        std::ofstream* saida;

        const unsigned int TAMANHOPILHA = 1000;
        unsigned int tamanhoTotal;
        unsigned int endCarregamento;
        unsigned int posAP;
        unsigned int entryPoint;
        std::unordered_map<std::string, unsigned int> tabelaSimbolos;
        std::unordered_map<std::string, unsigned int> tabelaPosInicialArquivo;

        void escreveCabecalhoArquivoSaida();
        void defineInformacoesArquivoSaida();

        void gravarPosInicialNaMemoriaInstrucoesArquivo(std::string);
        void navegarAteSecaoDaTabelaSimbolos(std::ifstream& arquivoEntrada);
    public:
        Ligador(std::ofstream& saida);
        ~Ligador();

        void lerTamanhoETabelaDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void completarComInstrucoesDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void escreveTabelaDeSimbolos();
        void escreveInformacoesArquivoSaida();
};
#endif
