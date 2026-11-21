#include "Indice.h"
Indice::Indice() : representacao(nullptr), modo('') {}

Indice::~Indice()
{
    delete representacao;
}

void Indice::cadastrarCliente(int idCliente, int poder)
{
    // Implementar controle de clientes ativos

    representacao->cadastrarCliente(idCliente, poder);
}

void Indice::encerrarAtendimento(int idCliente)
{
    // Implementar controle de clientes ativos
    representacao->encerrarAtendimento(idCliente);
}

void Indice::buscarPorPoder(int poder)
{
    representacao->buscarPorPoder(poder);
}

void Indice::buscarPorFaixaPoder(int poderMin, int poderMax)
{
    representacao->buscarPorFaixaPoder(poderMin, poderMax);
}

void Indice::mudarModo(char novoModo)
{
    
    if (novoModo == modo)
    {
        return;
    }
    RepresentacaoIndice* novaRepresentacao = nullptr;

    /*
    Implementação
    */


    delete representacao;
    representacao = novaRepresentacao;
    modo = novoModo;
}