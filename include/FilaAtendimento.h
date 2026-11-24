#ifndef FILA_ATENDIMENTO_H
#define FILA_ATENDIMENTO_H
#include "entidades.h"
#include "ArrayDinamico.h"

class FilaAtendimento
{
private:
    ArrayDinamico<Atendimento> heap;

    void atendeRaiz();
    void subir(int indice);
    void descer(int indice);
    int getAncestral(int indice);

public:
    void inserirCliente(int idCliente, int prioridade);
    int atenderClientes(int k, ArrayDinamico<Atendimento> &atendimentos);
    int size() const;
};

#endif // FILA_ATENDIMENTO_H
