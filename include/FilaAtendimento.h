#ifndef FILA_ATENDIMENTO_H
#define FILA_ATENDIMENTO_H

struct Atendimento;

class FilaAtendimento {
    private:
    ArrayDinamico<Atendimento> heap;

    void atendeRaiz();
    void subir(int indice);
    void descer(int indice);
    int getAncestral(int indice);
    int getSucessorEsq(int indice);
    int getSucessorDir(int indice);

    public:
        FilaAtendimento();
        void inserirCliente(int idCliente, int prioridade);
        int atenderClientes(int k, ArrayDinamico<Atendimento> &atendimentos);
        int size() const;
};

#endif // FILA_ATENDIMENTO_H