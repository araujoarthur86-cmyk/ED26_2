#ifndef MAPA_H
#define MAPA_H

#include <string>

#include "ArrayDinamico.h"
#include "ConjuntosDisjuntos.h"
#include "ListaAdjascencia.h"

struct Regiao
{
    int id;
    std::string nome;
};

class Mapa
{
private:
    ArrayDinamico<Regiao> regioes;
    ListaAdjascencia grafo;
    Conjuntos conectividade;

public:
    int cadastrarRegiao(const std::string& nome);
    void cadastrarRota(int idRegiaoA, int idRegiaoB, int custo);

    // Mantem a conectividade atualizada durante o cadastro das rotas.
    bool areConnected(int idRegiaoA, int idRegiaoB);

    std::string getNomeRegiao(int idRegiao) const;
};

#endif // MAPA_H
