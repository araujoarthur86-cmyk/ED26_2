#ifndef INDICE_H
#define INDICE_H

#include "RepresentacaoIndice.h"

class Indice
{
private:
    RepresentacaoIndice *representacao;
    char modo;

public:
    // EXP: long long bytesReservados(int ativos) const { return representacao->bytesReservados(ativos); }
    // EXP: int alturaMedida() const { return representacao->alturaMedida(); }

    Indice();
    ~Indice();

    Indice(const Indice &) = delete;
    Indice &operator=(const Indice &) = delete;

    void cadastrarCliente(int idCliente, int poder);
    void encerrarAtendimento(int idCliente, int poder);

    // Limpa e reutiliza o buffer antes de delegar a busca à representação.
    void buscarPorPoder(int poder, ResultadoBuscaIndice &resultados);
    void buscarPorFaixaPoder(
        int poderMin,
        int poderMax,
        ResultadoBuscaIndice &resultados);

    void mudarModo(char novoModo);
};

#endif // INDICE_H
