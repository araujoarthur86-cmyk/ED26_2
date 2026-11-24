#include "ListaAdjascencia.h"

void ListaAdjascencia::adicionarVertice()
{
    primeiraAresta.push_back(-1);
}

void ListaAdjascencia::adicionarRota(int origem, int destino, int custo)
{
    arestas.push_back(Aresta{destino, custo, primeiraAresta.at(origem)});
    primeiraAresta.at(origem) = arestas.size() - 1;

    arestas.push_back(Aresta{origem, custo, primeiraAresta.at(destino)});
    primeiraAresta.at(destino) = arestas.size() - 1;
}
