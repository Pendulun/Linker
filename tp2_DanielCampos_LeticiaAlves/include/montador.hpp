#ifndef MONTADOR_H
#define MONTADOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <list>
#include <iterator>

// TODO: structs, classes, e outras definições.
class Montador{
    private:
        std::ifstream* entrada;
        std::ofstream* saida;
        
        const unsigned int TAMANHOPILHA = 1000;
        unsigned int LC;
        unsigned int tamanhoPrograma;
        bool definiuEntryPoint;
        
        std::map<std::string, unsigned int> tabelaDeSimbolos;

        std::string removeEspacosETabs(std::string);
        std::string removeComentario(std::string instrucao);

        std::string getLabel(std::string& instrucao);
        std::string getOperacao(std::string& instrucao);
        std::string getOperando(std::string& instrucao);
        
        void inserirNaTabelaDeSimbolosSeLabelNaoVazio(std::string label, unsigned int valor);
        bool isNumber(const std::string& str);
        std::string getValorOperandoMemoriaVerificandoTabelaSimbolos(std::string instrucao);
        int getRegistrador(std::string registrador);

        void imprimeNaTelaMensagem(const std::string,const std::string);
        void escreveTabelaDeSimbolos();

        void passo1();
        void passo2();
        void resetaLeituraArquivoEntrada();

        void defineInformacoesArquivoSaida();
        void escreveInformacoesArquivoSaida();
        void escreveInstrucaoNoArquivoSaida(const std::string, const  std::list<std::string>);

    public:
        Montador(std::ifstream& entrada, std::ofstream& saida);
        ~Montador();

        void montar();
};


#endif
