#include "Mapa.h"

int Mapa::cadastrarRegiao(const std::string &nome)
{
    int id = regioes.size();
    regioes.push_back(Regiao{id, nome});
    grafo.adicionarVertice();
    conectividade.adicionarConjunto();
    return id;
}

void Mapa::cadastrarRota(int idRegiaoA, int idRegiaoB, int custo)
{
    grafo.adicionarRota(idRegiaoA, idRegiaoB, custo);
    conectividade.unir(idRegiaoA, idRegiaoB);
}

bool Mapa::areConnected(int idRegiaoA, int idRegiaoB)
{
    return conectividade.estaoConectados(idRegiaoA, idRegiaoB);
}

std::string Mapa::getNomeRegiao(int idRegiao) const
{
    return regioes.at(idRegiao).nome;
}
