#ifndef LIGADOR_H
#define LIGADOR_H

#include <fstream>
#include <string>
#include <list>
#include <unordered_map>

class Ligador{
    private:
        std::ofstream* saida;

        const unsigned int TAMANHOPILHA = 1000;
        unsigned int tamanhoPrograma;
        unsigned int endCarregamento;
        unsigned int posAP;
        unsigned int entryPoint;
        bool definiuEntryPoint;

        
        void escreveCabecalhoArquivoSaida();
        void escreveInformacoesArquivoSaida();
        void escreveInstrucaoNoArquivoSaida(const std::string, const  std::list<std::string>);
        void verificaEDefineEntryPoint();
        void defineInformacoesArquivoSaida();

        int calculaEnderecoRelativo(unsigned int pc, unsigned int endereco);

    public:
        Ligador(std::ofstream& saida);
        ~Ligador();

        void lerTamanhoETabelaDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void completarInstrucoesDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo);
        void passo1();
        void passo2();

};

#endif
