#ifndef LISTA_ADJASCENCIA_H
#define LISTA_ADJASCENCIA_H
#include "ArrayDinamico.h"

struct Aresta
{
    int destino;
    int custo;
    int proxima;
};

class ListaAdjascencia
{
private:
    ArrayDinamico<int> primeiraAresta;
    ArrayDinamico<Aresta> arestas;

public:
    void adicionarVertice();
    void adicionarRota(int origem, int destino, int custo);
};

#endif // LISTA_ADJASCENCIA_H
