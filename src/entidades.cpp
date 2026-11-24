#include "entidades.h"

Build::Build() : poder(0) {}

int Build::getPoder() const
{
    return poder;
}

void Build::modificarAtributo(int idAtributo, int valor)
{
    int inicio = 0;
    int fim = modificadores.size();

    while (inicio < fim)
    {
        int meio = inicio + (fim - inicio) / 2;
        if (modificadores.at(meio).idAtributo < idAtributo)
            inicio = meio + 1;
        else
            fim = meio;
    }

    int valorAntigo = 0;
    bool existe = inicio < modificadores.size()
        && modificadores.at(inicio).idAtributo == idAtributo;

    if (existe)
    {
        valorAntigo = modificadores.at(inicio).valor;
        if (valor == 0)
            modificadores.erase(inicio);
        else
            modificadores.at(inicio).valor = valor;
    }
    else if (valor != 0)
    {
        modificadores.insert(inicio, {idAtributo, valor});
    }

    poder += valor - valorAntigo;
}

Cliente::Cliente() : id(0), nome(), build() {}

Cliente::Cliente(int id, const std::string &nome, const Build &build)
    : id(id), nome(nome), build(build)
{}

int Cliente::getId() const
{
    return id;
}

std::string Cliente::getNome() const
{
    return nome;
}

int Cliente::getPoder() const
{
    return build.getPoder();
}

bool Atendimento::operator>(const Atendimento &outro) const
{
    return prioridade > outro.prioridade
        || (prioridade == outro.prioridade && idCliente < outro.idCliente);
}

bool Atendimento::operator==(const Atendimento &outro) const
{
    return idCliente == outro.idCliente;
}
