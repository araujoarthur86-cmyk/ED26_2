#ifndef ENTIDADES_H
#define ENTIDADES_H
#include <string>
#include "ArrayDinamico.h"

// Entidades relacionadas a clientes
struct Atributo
{
    int id;
    std::string nome;
};

struct Modificador
{
    int idAtributo;
    int valor;
};

class Build
{
public:
    Build();
    int getPoder() const;
    void modificarAtributo(int idAtributo, int valor);

private:
    // Modificadores não nulos, ordenados pelo ID do atributo.
    ArrayDinamico<Modificador> modificadores;
    int poder;
};

class Cliente
{
private:
    int id;
    std::string nome;
    Build build;

public:
    Cliente();
    Cliente(int id, const std::string &nome, const Build &build);
    int getId() const;
    std::string getNome() const;
    int getPoder() const;
};

struct Atendimento
{
    int idCliente;
    int prioridade;

    bool operator>(const Atendimento &outro) const;
    bool operator==(const Atendimento &outro) const;
};
#endif // ENTIDADES_H
