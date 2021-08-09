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

    std::pair <std::string, unsigned int> par;
    par = std::make_pair(nomeArquivo, this->tamanhoTotal);
    this->tabelaPosInicialArquivo.insert(par);

    std::getline(arquivoEntrada, tamanhoArquivoString);
    tamanhoArquivo = std::stoul (tamanhoArquivoString, nullptr, 0);

    bool achouParteTabela = false;
    std::string linha = "";


    //Find the Table of Symbles part
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

    //Read every key-value pair in the Table of Symbles
    while(!arquivoEntrada.eof()){
        posSep = 0;
        std::getline(arquivoEntrada, linha);
        
        if(linha.compare("")!=0){
            posSep = linha.find(separador);

            chave = linha.substr(0, posSep);
            valorString = linha.substr(posSep+1, linha.length()-posSep-1);
            valor = std::stoul (valorString, nullptr, 0);

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

void Ligador::completarComInstrucoesDoArquivo(std::ifstream& arquivoEntrada, std::string nomeArquivo){
    std::string linha = "";
    bool achouParteInstrucoes = false;
    //Procurar a parte das intruções
    while(!achouParteInstrucoes && !arquivoEntrada.eof()){
        std::getline(arquivoEntrada, linha);

        if (linha.compare("#INSTRUCOES")==0){
            achouParteInstrucoes = true;
        }
    }

    std::getline(arquivoEntrada, linha);
    unsigned int indexInstrucao = 0;
    std::string instrucao = "";
    std::istringstream iss(linha);
    unsigned int posInicialInstrucoesArquivoNaMemoria = this->tabelaPosInicialArquivo.find(nomeArquivo)->second;

    //Read every instruction writing it to the saida.mv
    while(iss >> instrucao){
        std::cout<<"Instrucao lida: ."<<instrucao<<".\n";
        std::string primeiraLetra = instrucao.substr(0,1);

        if(primeiraLetra.compare("#") == 0){
            //Assuming that every used label was defined somewere
            std::unordered_map<std::string,unsigned int>::const_iterator par = this->tabelaSimbolos.find(instrucao.substr(1, instrucao.length()-1));
            unsigned int enderecoAbsolutoLabel = par->second;
            std::cout<<"Endereco absoluto do label: "<<enderecoAbsolutoLabel<<"\n";
            unsigned int enderecoAtual = indexInstrucao + posInicialInstrucoesArquivoNaMemoria;
            std::cout<<"Endereco atual: "<<enderecoAtual<<"\n";
            int enderecoRelativo = enderecoAbsolutoLabel - enderecoAtual -1;
            std::cout<<"Imprimindo Endereco relativo calculado: "<<enderecoRelativo<<"\n";
            (*this->saida)<< std::to_string(enderecoRelativo);
            (*this->saida)<< " ";
        }else{
            std::cout<<"Imprimindo: "<<instrucao<<"\n";
            (*this->saida)<< instrucao.append(" ");
        }
        indexInstrucao++;
    }    
}

int Ligador::calculaEnderecoRelativo(unsigned int LC, unsigned int endereco){
    int enderecoRelativo = endereco - (LC);
    return enderecoRelativo;
}
