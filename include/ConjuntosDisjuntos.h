#ifndef DSU_H
#define DSU_H

#include "ArrayDinamico.h"

class Conjuntos
{
private:
    ArrayDinamico<int> pai;
    ArrayDinamico<int> tamanho;

    int encontrarRaiz(int elemento);

public:
    // EXP: static long long elos;
    int adicionarConjunto();
    int encontrar(int elemento);
    bool unir(int elementoA, int elementoB);
    bool estaoConectados(int elementoA, int elementoB);
    int quantidade() const;
};

#endif // DSU_H
