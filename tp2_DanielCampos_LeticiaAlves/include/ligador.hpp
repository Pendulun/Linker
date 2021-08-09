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
        unsigned int getTamanhoTotalArquivo(std::ifstream&);
        void leEGravaTabelaDeSimbolos(std::ifstream& arquivoEntrada);
        void adicionaLabelEValorNaTabelaDeSimbolos(const std::string linha, const std::string SEPARADOR);
        unsigned int calculaEnderecoAbsoluto(const unsigned int valor);

        void navegaAteSecaoDoIdentificador(std::ifstream& arquivoEntrada, const std::string IDENTIFICADOR);

        void escreveInstrucoesNaSaidaTratandoReferenciasExternas(std::ifstream& arquivoEntrada, const std::string nomeArquivo);
        bool instrucaoTemReferenciaExterna(const std::string instrucao);
        const std::string getInstrucoesArquivo(std::ifstream& arquivoEntrada);
        int getEnderecoRelativo(const std::string instrucao, const unsigned int enderecoAtual);
    public:
        Ligador(std::ofstream& saida);
        ~Ligador();

        void lerTamanhoETabelaDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void completarComInstrucoesDoArquivo(std::ifstream& arquivoEntrada, const std::string nomeArquivo);
        void escreveTabelaDeSimbolos();
        void escreveInformacoesArquivoSaida();
};
#endif
