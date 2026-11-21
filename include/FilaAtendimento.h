#ifndef FILA_ATENDIMENTO_H
#define FILA_ATENDIMENTO_H

struct Atendimento;

class FilaAtendimento {
    public:
        FilaAtendimento();
        ~FilaAtendimento();

        void inserirCliente(int idCliente, int prioridade);
        int atenderClientes(int k, ArrayDinamico<Atendimento> &atendimentos);
        int size() const;
};

#endif // FILA_ATENDIMENTO_H