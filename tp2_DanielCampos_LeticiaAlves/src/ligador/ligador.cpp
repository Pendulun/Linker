#include "ligador.hpp"

Ligador::Ligador(){
    this->posAP=0;
    this->tamanhoTotal=0;
    this->entryPoint=0;
    this->endCarregamento=0;
    this->tabelaSimbolos.clear();
}

Ligador::~Ligador(){

}



void Ligador::escreveInformacoesArquivoSaida(){
    this->escreveCabecalhoArquivoSaida();
    this->defineInformacoesArquivoSaida();
    std::cout<<std::to_string(this->tamanhoTotal).append(" ");
    std::cout<<std::to_string(this->endCarregamento).append(" ");
    std::cout<<std::to_string(this->posAP).append(" ");
    std::cout<<std::to_string(this->entryPoint);
    std::cout<<std::endl;
    std::cout<<std::endl;
}

void Ligador::escreveCabecalhoArquivoSaida(){
    std::cout<<"MV-EXE";
    std::cout<<std::endl;
    std::cout<<std::endl;
}

void Ligador::defineInformacoesArquivoSaida(){
    this->endCarregamento=0;
    this->posAP = this->endCarregamento + this->tamanhoTotal + this->TAMANHOPILHA;
    std::unordered_map<std::string,unsigned int>::const_iterator enderecoMain = this->tabelaSimbolos.find("main");
    //Assuming that "main" is a label that is always defined somewere
    this->entryPoint = enderecoMain->second;
}

void Ligador::lerTamanhoETabelaDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo){
    
    this->gravarPosInicialNaMemoriaInstrucoesArquivo(nomeArquivo);
    
    unsigned int tamanhoArquivo = this->getTamanhoTotalArquivo(arquivoEntrada); 
    
    this->leEGravaTabelaDeSimbolos(arquivoEntrada);

    this->tamanhoTotal += tamanhoArquivo; 
}


void Ligador::gravarPosInicialNaMemoriaInstrucoesArquivo(std::string nomeArquivo){
    std::pair <std::string, unsigned int> par;
    par = std::make_pair(nomeArquivo, this->tamanhoTotal);
    this->tabelaPosInicialArquivo.insert(par);
}

unsigned int Ligador::getTamanhoTotalArquivo(std::ifstream& arquivoEntrada){
    std::string tamanhoArquivoString = "";
    std::getline(arquivoEntrada, tamanhoArquivoString);
    unsigned int tamanhoArquivo = 0;
    tamanhoArquivo = std::stoul(tamanhoArquivoString, nullptr, 0);
    return tamanhoArquivo;
}


void Ligador::leEGravaTabelaDeSimbolos(std::ifstream& arquivoEntrada){
    const std::string IDENTIFICADORSECAO = "#TABELA";
    this->navegaAteSecaoDoIdentificador(arquivoEntrada, IDENTIFICADORSECAO);

    std::string linha = "";
    const std::string SEPARADOR = ":";

    //Read every key-value pair in the Table of Symbles
    while(!arquivoEntrada.eof()){
        std::getline(arquivoEntrada, linha);
        if(linha.compare("")!=0){
            this->adicionaLabelEValorNaTabelaDeSimbolos(linha, SEPARADOR);
        }
    }
}

void Ligador::navegaAteSecaoDoIdentificador(std::ifstream& arquivoEntrada, const std::string IDENTIFICADORSECAO){
    std::string linha = "";
    bool achouSecao = false;
    while(!achouSecao && !arquivoEntrada.eof()){
        std::getline(arquivoEntrada, linha);

        if (linha.compare(IDENTIFICADORSECAO)==0){
            achouSecao = true;
        }
    }
}

void Ligador::adicionaLabelEValorNaTabelaDeSimbolos(const std::string linha, const std::string SEPARADOR){
        size_t posSep = linha.find(SEPARADOR);

        std::string chave = linha.substr(0, posSep);
        std::string valorString = linha.substr(posSep+1, linha.length()-posSep-1);
        unsigned int valor = std::stoul (valorString, nullptr, 0);
        
        std::pair<std::string, unsigned int> par = std::make_pair(chave, this->calculaEnderecoAbsoluto(valor));
        this->tabelaSimbolos.insert(par);
}

unsigned int Ligador::calculaEnderecoAbsoluto(const unsigned int valor){
    return valor+this->tamanhoTotal;
}

void Ligador::escreveTabelaDeSimbolos(){
    for (std::unordered_map<std::string, unsigned int>::iterator it=this->tabelaSimbolos.begin(); it!=this->tabelaSimbolos.end(); ++it){
        std::cout<<it->first<<":"<<it->second<<"\n";
    }
    std::cout<<std::endl;
}

void Ligador::completarComInstrucoesDoArquivo(std::ifstream& arquivoEntrada, const std::string nomeArquivo){
    this->escreveInstrucoesNaSaidaTratandoReferenciasExternas(arquivoEntrada, nomeArquivo);
}

void Ligador::escreveInstrucoesNaSaidaTratandoReferenciasExternas(std::ifstream& arquivoEntrada, const std::string nomeArquivo){ 
    std::string instrucao = "";
    std::string instrucoesArquivo = this->getInstrucoesArquivo(arquivoEntrada);
    std::istringstream iss(instrucoesArquivo);
    
    std::string instrucaoASerImpressa = "";
    unsigned int indexInstrucaoNoArquivoAtual = 0;
    unsigned int posInicialInstrucoesArquivoNaMemoria = this->tabelaPosInicialArquivo.find(nomeArquivo)->second;
    //Read every instruction from the file writing it to the executavel.mv
    while(iss >> instrucao){
        instrucaoASerImpressa="";

        if(this->instrucaoTemReferenciaExterna(instrucao)){
            unsigned int enderecoAbsolutoAtual = indexInstrucaoNoArquivoAtual + posInicialInstrucoesArquivoNaMemoria;
            const std::string labelReferenciado = instrucao.substr(1, instrucao.length()-1);
            instrucaoASerImpressa = std::to_string(this->getEnderecoRelativo(labelReferenciado, enderecoAbsolutoAtual));
        }else{
            instrucaoASerImpressa = instrucao;
        }

        instrucaoASerImpressa += " ";
        std::cout<<instrucaoASerImpressa;
        indexInstrucaoNoArquivoAtual++;
    }    
}

const std::string Ligador::getInstrucoesArquivo(std::ifstream& arquivoEntrada){
    const std::string IDENTIFICADORSECAO = "#INSTRUCOES";
    this->navegaAteSecaoDoIdentificador(arquivoEntrada,IDENTIFICADORSECAO);
    std::string instrucoesArquivo;
    std::getline(arquivoEntrada, instrucoesArquivo);
    return instrucoesArquivo;
}

bool Ligador::instrucaoTemReferenciaExterna(const std::string instrucao){
    return instrucao.substr(0,1).compare("#") == 0;
}

int Ligador::getEnderecoRelativo(const std::string labelReferenciado, const unsigned int enderecoAtual){
    //Assuming that every used label was defined somewere
    unsigned int enderecoAbsolutoLabel = this->tabelaSimbolos.find(labelReferenciado)->second;
    int enderecoRelativo = enderecoAbsolutoLabel - enderecoAtual -1;
    return enderecoRelativo;
}