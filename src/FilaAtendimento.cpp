#include "FilaAtendimento.h"

void FilaAtendimento::inserirCliente(int idCliente, int prioridade)
{
    Atendimento newAtendimento{idCliente, prioridade};
    int i = size(); 
    heap.push_back(newAtendimento);

    subir(i);
}

void FilaAtendimento::atendeRaiz()
{
    int last = size() - 1; 
    heap.at(0) = heap.at(last);
    heap.erase(last);
    last = 0;

    descer(last);
}

int FilaAtendimento::atenderClientes(int k, ArrayDinamico<Atendimento> &atendimentos)
{
    atendimentos.clear();
    int n = size();

    if(n > k)
    {
        n = k;
    }

    for(int i = 0; i < n; ++i)
    {
        Atendimento raiz = heap.at(0);
        atendimentos.push_back(raiz);

        atendeRaiz();
    }

    return n;
}

int FilaAtendimento::size() const
{
    return heap.size();
}

void FilaAtendimento::subir(int indice)
{
    int pai = getAncestral(indice);

    while(indice > 0 && heap.at(indice) > heap.at(pai))
    {
        heap.swap(pai, indice);

        indice = pai;
        pai = getAncestral(indice);
    }
}

void FilaAtendimento::descer(int indice)
{
    int n = heap.size();

    while (true)
    {
        int maior = indice;
        int esq = 2 * indice + 1;
        int dir = 2 * indice + 2;

        if (esq < n && heap.at(esq) > heap.at(maior))
            maior = esq;

        if (dir < n && heap.at(dir) > heap.at(maior))
            maior = dir;

        if (maior != indice)
        {
            heap.swap(indice, maior);
            indice = maior;
        }
        else
        {
            break;
        }
    }
}

int FilaAtendimento::getAncestral(int indice) 
{
    return (indice - 1)/2;
}

int FilaAtendimento::getSucessorEsq(int indice) { return 2*indice + 1; }
int FilaAtendimento::getSucessorDir(int indice) { return 2*indice + 2; }

