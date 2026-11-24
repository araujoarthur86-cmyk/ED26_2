#ifndef REPRESENTACAO_H
#define REPRESENTACAO_H

#include "ArrayDinamico.h"

struct Celula
{
    int idCliente;
    int poder;

    bool operator<(const Celula &outra) const
    {
        return poder < outra.poder
            || (poder == outra.poder && idCliente < outra.idCliente);
    }
};

typedef ArrayDinamico<Celula> ResultadoBuscaIndice;

class RepresentacaoIndice
{
public:
    // EXP: virtual long long bytesReservados(int ativos) const = 0;
    // EXP: virtual int alturaMedida() const { return 0; }
    // EXP: static long long visitas, rotacoes, deslocamentos, baldesLidos;
    RepresentacaoIndice() = default;
    RepresentacaoIndice(const RepresentacaoIndice &) = delete;
    RepresentacaoIndice &operator=(const RepresentacaoIndice &) = delete;
    virtual void copiarPara(RepresentacaoIndice &destino) const = 0;
    virtual ~RepresentacaoIndice() = default;

    virtual void cadastrarCliente(int idCliente, int poder) = 0;
    virtual void encerrarAtendimento(int idCliente, int poder) = 0;

    // Acrescenta ao buffer vazio resultados em ordem crescente de ID.
    virtual void buscarPorPoder(int poder, ResultadoBuscaIndice &resultados) = 0;

    // Acrescenta resultados do intervalo fechado, ordenados por (poder, ID).
    virtual void buscarPorFaixaPoder(
        int poderMin,
        int poderMax,
        ResultadoBuscaIndice &resultados) = 0;
};

#endif // REPRESENTACAO_H
