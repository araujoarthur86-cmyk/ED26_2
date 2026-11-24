#ifndef INDICE_HASH_H
#define INDICE_HASH_H

#include "RepresentacaoIndice.h"

class IndiceHash : public RepresentacaoIndice
{
    // Uma cadeia por balde e um grupo por poder distinto.
    struct Grupo
    {
        int poder;
        ArrayDinamico<int> ids;
        Grupo *proximo;
    };
    int capacidade;
    int grupos;
    Grupo **baldes;
    static int baldeDe(int poder, int capacidade);
    void expandir();

public:
    // EXP: long long bytesReservados(int) const override;
    void copiarPara(RepresentacaoIndice &destino) const override;
    IndiceHash();
    ~IndiceHash();

    void cadastrarCliente(int idCliente, int poder) override;
    void encerrarAtendimento(int idCliente, int poder) override;
    void buscarPorPoder(int poder, ResultadoBuscaIndice &resultados) override;
    void buscarPorFaixaPoder(
        int poderMin,
        int poderMax,
        ResultadoBuscaIndice &resultados) override;
};

#endif // INDICE_HASH_H
