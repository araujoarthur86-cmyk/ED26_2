#ifndef INDICE_A_H
#define INDICE_A_H
#include "RepresentacaoIndice.h"

class IndiceA : public RepresentacaoIndice
{
    struct No
    {
        Celula cliente;
        int altura;
        No *esq;
        No *dir;
    };
    No *raiz;
    static int altura(const No *no);
    static void atualizarAltura(No *no);
    static No *girarDireita(No *no);
    static No *girarEsquerda(No *no);
    static No *balancear(No *no);
    static No *inserir(No *no, Celula cliente);
    static No *remover(No *no, Celula cliente);
    static void coletar(const No *no, int minimo, int maximo, ResultadoBuscaIndice &saida);
    static void copiar(const No *no, RepresentacaoIndice &destino);
    static void liberar(No *no);

public:
    // EXP: long long bytesReservados(int ativos) const override { return sizeof(*this) + ativos * sizeof(No); }
    // EXP: int alturaMedida() const override { return altura(raiz); }
    void copiarPara(RepresentacaoIndice &destino) const override;
    IndiceA();
    ~IndiceA();

    void cadastrarCliente(int idCliente, int poder) override;
    void encerrarAtendimento(int idCliente, int poder) override;
    void buscarPorPoder(int poder, ResultadoBuscaIndice &resultados) override;
    void buscarPorFaixaPoder(
        int poderMin,
        int poderMax,
        ResultadoBuscaIndice &resultados) override;
};
#endif // INDICE_A_H
