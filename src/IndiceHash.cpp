#include "IndiceHash.h"

namespace
{
// Primeira posição com ID maior ou igual ao procurado.
int posicaoId(const ArrayDinamico<int> &ids, int id)
{
    int inicio = 0, fim = ids.size();
    while (inicio < fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        if (ids.at(meio) < id) inicio = meio + 1;
        else fim = meio;
    }
    return inicio;
}

// Heapsort próprio para ordenar somente os registros selecionados por BF.
void descer(ResultadoBuscaIndice &dados, int pai, int tamanho)
{
    while (pai < tamanho / 2)
    {
        int maior = 2 * pai + 1;
        if (maior + 1 < tamanho && dados.at(maior) < dados.at(maior + 1))
            ++maior;
        if (!(dados.at(pai) < dados.at(maior))) break;
        dados.swap(pai, maior);
        pai = maior;
    }
}
}

IndiceHash::IndiceHash() : capacidade(17), grupos(0), baldes(new Grupo*[capacidade]()) {}

IndiceHash::~IndiceHash()
{
    for (int i = 0; i < capacidade; ++i)
    {
        Grupo *grupo = baldes[i];
        while (grupo)
        {
            Grupo *proximo = grupo->proximo;
            delete grupo;
            grupo = proximo;
        }
    }
    delete[] baldes;
}

int IndiceHash::baldeDe(int poder, int capacidade)
{
    int resto = poder % capacidade;
    return resto < 0 ? resto + capacidade : resto;
}

void IndiceHash::expandir()
{
    int novaCapacidade = 2 * capacidade + 1;
    Grupo **novos = new Grupo*[novaCapacidade]();
    for (int i = 0; i < capacidade; ++i)
    {
        Grupo *grupo = baldes[i];
        while (grupo)
        {
            Grupo *proximo = grupo->proximo;
            int balde = baldeDe(grupo->poder, novaCapacidade);
            grupo->proximo = novos[balde];
            novos[balde] = grupo;
            grupo = proximo;
        }
    }
    delete[] baldes;
    baldes = novos;
    capacidade = novaCapacidade;
}

void IndiceHash::cadastrarCliente(int idCliente, int poder)
{
    int balde = baldeDe(poder, capacidade);
    for (Grupo *grupo = baldes[balde]; grupo; grupo = grupo->proximo)
    {
        // EXP: ++visitas;
        if (grupo->poder != poder) continue;
        ArrayDinamico<int> &ids = grupo->ids;
        if (ids.at(ids.size() - 1) < idCliente)
            ids.push_back(idCliente);
        else
            ids.insert(posicaoId(ids, idCliente), idCliente);
        return;
    }
    // Mantém no máximo um grupo por balde em média.
    if (grupos == capacidade)
    {
        expandir();
        balde = baldeDe(poder, capacidade);
    }
    Grupo *novo = new Grupo{poder, {}, baldes[balde]};
    novo->ids.push_back(idCliente);
    baldes[balde] = novo;
    ++grupos;
}

void IndiceHash::encerrarAtendimento(int idCliente, int poder)
{
    int balde = baldeDe(poder, capacidade);
    Grupo *anterior = nullptr;
    Grupo *grupo = baldes[balde];
    while (grupo && grupo->poder != poder)
    {
        // EXP: ++visitas;
        anterior = grupo;
        grupo = grupo->proximo;
    }
    if (!grupo) return;
    // EXP: ++visitas;
    int posicao = posicaoId(grupo->ids, idCliente);
    if (posicao == grupo->ids.size() || grupo->ids.at(posicao) != idCliente) return;
    // EXP: deslocamentos += grupo->ids.size() - posicao - 1;
    grupo->ids.erase(posicao);
    if (grupo->ids.size() == 0)
    {
        if (anterior) anterior->proximo = grupo->proximo;
        else baldes[balde] = grupo->proximo;
        delete grupo;
        --grupos;
    }
}

void IndiceHash::buscarPorPoder(int poder, ResultadoBuscaIndice &saida)
{
    for (const Grupo *grupo = baldes[baldeDe(poder, capacidade)]; grupo; grupo = grupo->proximo)
    {
        // EXP: ++visitas;
        if (grupo->poder != poder) continue;
        for (int i = 0; i < grupo->ids.size(); ++i)
            saida.push_back({grupo->ids.at(i), poder});
        return;
    }
}

void IndiceHash::buscarPorFaixaPoder(int minimo, int maximo, ResultadoBuscaIndice &saida)
{
    // EXP: baldesLidos += capacidade;
    for (int i = 0; i < capacidade; ++i)
        for (const Grupo *grupo = baldes[i]; grupo; grupo = grupo->proximo)
        {
            // EXP: ++visitas;
            if (grupo->poder < minimo || grupo->poder > maximo) continue;
            for (int j = 0; j < grupo->ids.size(); ++j)
                saida.push_back({grupo->ids.at(j), grupo->poder});
        }

    for (int i = saida.size() / 2 - 1; i >= 0; --i)
        descer(saida, i, saida.size());
    for (int fim = saida.size() - 1; fim > 0; --fim)
    {
        saida.swap(0, fim);
        descer(saida, 0, fim);
    }
}

// EXP: long long IndiceHash::bytesReservados(int) const
// EXP: {
// EXP:     long long bytes = sizeof(*this) + capacidade * sizeof(Grupo*);
// EXP:     for (int i = 0; i < capacidade; ++i)
// EXP:         for (const Grupo *g = baldes[i]; g; g = g->proximo)
// EXP:             bytes += sizeof(Grupo) + g->ids.capacidadeReservada() * sizeof(int);
// EXP:     return bytes;
// EXP: }

void IndiceHash::copiarPara(RepresentacaoIndice &destino) const
{
    for (int i = 0; i < capacidade; ++i)
        for (const Grupo *grupo = baldes[i]; grupo; grupo = grupo->proximo)
            for (int j = 0; j < grupo->ids.size(); ++j)
                destino.cadastrarCliente(grupo->ids.at(j), grupo->poder);
}
