#include "Indice.h"
#include "IndiceAVL.h"
#include "IndiceHash.h"

Indice::Indice() : representacao(nullptr), modo('\0') {}

Indice::~Indice()
{
    delete representacao;
}

void Indice::cadastrarCliente(int idCliente, int poder)
{
    representacao->cadastrarCliente(idCliente, poder);
}

void Indice::encerrarAtendimento(int idCliente, int poder)
{
    representacao->encerrarAtendimento(idCliente, poder);
}

void Indice::buscarPorPoder(int poder, ResultadoBuscaIndice &resultados)
{
    resultados.clear();
    representacao->buscarPorPoder(poder, resultados);
}

void Indice::buscarPorFaixaPoder(
    int poderMin,
    int poderMax,
    ResultadoBuscaIndice &resultados)
{
    resultados.clear();
    representacao->buscarPorFaixaPoder(poderMin, poderMax, resultados);
}

void Indice::mudarModo(char novoModo)
{
    if (novoModo == modo)
    {
        return;
    }
    RepresentacaoIndice *nova;
    if (novoModo == 'A') nova = new IndiceA();
    else nova = new IndiceHash();

    try
    {
        if (representacao) representacao->copiarPara(*nova);
    }
    catch (...)
    {
        delete nova;
        throw;
    }

    delete representacao;
    representacao = nova;
    modo = novoModo;
}
