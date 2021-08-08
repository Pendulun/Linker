#include "ligador.hpp"

Ligador::Ligador(std::ofstream& saida){
    this->saida = &saida;
    this->posAP=0;
    this->tamanhoPrograma=0;
    this->entryPoint=0;
    this->definiuEntryPoint = false;
    this->endCarregamento=0;
}

void Ligador::escreveCabecalhoArquivoSaida(){
    (*this->saida)<<"MV-EXE";
    (*this->saida)<<std::endl;
    (*this->saida)<<std::endl;
}

void Ligador::verificaEDefineEntryPoint(){
    if(!this->definiuEntryPoint){
        //this->entryPoint = this->LC;
        this->definiuEntryPoint=true;
    }
}

void Ligador::escreveInformacoesArquivoSaida(){
    *this->saida<<std::to_string(this->tamanhoPrograma).append(" ");
    *this->saida<<std::to_string(this->endCarregamento).append(" ");
    *this->saida<<std::to_string(this->posAP).append(" ");
    *this->saida<<std::to_string(this->entryPoint);
    *this->saida<<std::endl;
    *this->saida<<std::endl;
}

void Ligador::escreveInstrucaoNoArquivoSaida(const std::string codigoOperacao, const std::list<std::string> operandos){
    *this->saida<<codigoOperacao<<" ";
    for(std::string operando : operandos){
        *this->saida<<operando.append(" ");
    }
}

void Ligador::defineInformacoesArquivoSaida(){
    //this->tamanhoPrograma = this->LC;
    this->endCarregamento=0;
    this->posAP = this->endCarregamento + this->tamanhoPrograma + this->TAMANHOPILHA;

}

void Ligador::passo1(){

}

void Ligador::passo2(){

}


int Ligador::calculaEnderecoRelativo(unsigned int LC, unsigned int endereco){
    int enderecoRelativo = endereco - (LC);
    return enderecoRelativo;
}
