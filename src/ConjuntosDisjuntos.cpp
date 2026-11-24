#include "ConjuntosDisjuntos.h"

int Conjuntos::adicionarConjunto()
{
    int elemento = pai.size();
    pai.push_back(elemento);
    tamanho.push_back(1);
    return elemento;
}

int Conjuntos::encontrarRaiz(int elemento)
{
    int raiz = elemento;
    while (pai.at(raiz) != raiz)
    {
        // EXP: ++elos;
        raiz = pai.at(raiz);
    }

    // Compressao iterativa do caminho.
    while (elemento != raiz)
    {
        int proximo = pai.at(elemento);
        pai.at(elemento) = raiz;
        elemento = proximo;
    }

    return raiz;
}

int Conjuntos::encontrar(int elemento)
{
    return encontrarRaiz(elemento);
}

bool Conjuntos::unir(int elementoA, int elementoB)
{
    int raizA = encontrarRaiz(elementoA);
    int raizB = encontrarRaiz(elementoB);

    if (raizA == raizB)
        return false;

    if (tamanho.at(raizA) < tamanho.at(raizB))
    {
        int temporaria = raizA;
        raizA = raizB;
        raizB = temporaria;
    }

    pai.at(raizB) = raizA;
    tamanho.at(raizA) += tamanho.at(raizB);
    return true;
}

bool Conjuntos::estaoConectados(int elementoA, int elementoB)
{
    return encontrarRaiz(elementoA) == encontrarRaiz(elementoB);
}

int Conjuntos::quantidade() const
{
    return pai.size();
}
