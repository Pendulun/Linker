#include "ligador.hpp"

Ligador::Ligador(std::ofstream& saida){
    this->saida = &saida;
    this->posAP=0;
    this->tamanhoTotal=0;
    this->entryPoint=0;
    this->endCarregamento=0;
    this->tabelaSimbolos.clear();
}

Ligador::~Ligador(){

}

void Ligador::escreveCabecalhoArquivoSaida(){
    (*this->saida)<<"MV-EXE";
    (*this->saida)<<std::endl;
    (*this->saida)<<std::endl;
}

void Ligador::escreveInformacoesArquivoSaida(){
    this->escreveCabecalhoArquivoSaida();
    this->defineInformacoesArquivoSaida();
    *this->saida<<std::to_string(this->tamanhoTotal).append(" ");
    *this->saida<<std::to_string(this->endCarregamento).append(" ");
    *this->saida<<std::to_string(this->posAP).append(" ");
    *this->saida<<std::to_string(this->entryPoint);
    *this->saida<<std::endl;
    *this->saida<<std::endl;
}

void Ligador::defineInformacoesArquivoSaida(){
    this->endCarregamento=0;
    this->posAP = this->endCarregamento + this->tamanhoTotal + this->TAMANHOPILHA;
    std::unordered_map<std::string,unsigned int>::const_iterator enderecoMain = this->tabelaSimbolos.find("main");
    //Assuming that "main" is a label that is always defined somewere
    this->entryPoint = enderecoMain->second;
}

void Ligador::lerTamanhoETabelaDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo){
    unsigned int tamanhoArquivo = 0;
    std::string tamanhoArquivoString = "";

    std::getline(arquivoEntrada, tamanhoArquivoString);
    tamanhoArquivo = std::stoul (tamanhoArquivoString, nullptr, 0);

    bool achouParteTabela = false;
    std::string linha = "";

    while(!achouParteTabela && !arquivoEntrada.eof()){
        std::getline(arquivoEntrada, linha);

        if (linha.compare("#TABELA")==0){
            achouParteTabela = true;
        }
    }

    linha = "";

    std::string separador = ":";
    std::string chave = "";
    unsigned int valor = 0;
    std::string valorString = "";

    size_t posSep = 0; 

    while(!arquivoEntrada.eof()){
        posSep = 0;
        std::getline(arquivoEntrada, linha);
        
        if(linha.compare("")!=0){
            posSep = linha.find(separador);

            chave = linha.substr(0, posSep);
            valorString = linha.substr(posSep+1, linha.length()-posSep-1);
            valor = std::stoul (valorString, nullptr, 0);

            std::pair <std::string, unsigned int> par;
            par = std::make_pair(chave, valor+this->tamanhoTotal);
            this->tabelaSimbolos.insert(par);
        }
    }

    this->tamanhoTotal += tamanhoArquivo; 

}

void Ligador::escreveTabelaDeSimbolos(){
    for (std::unordered_map<std::string, unsigned int>::iterator it=this->tabelaSimbolos.begin(); it!=this->tabelaSimbolos.end(); ++it){
        std::cout<<it->first<<":"<<it->second<<"\n";
    }
    std::cout<<std::endl;
}

int Ligador::calculaEnderecoRelativo(unsigned int LC, unsigned int endereco){
    int enderecoRelativo = endereco - (LC);
    return enderecoRelativo;
}
