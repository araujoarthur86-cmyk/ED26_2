#ifndef ENTIDADES_H
#define ENTIDADES_H
#include <string>

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
    // Valores de cada atributo na Build;
    // Implementar os métodos necessários para manipular os atributos da Build
    ArrayDinamico<Modificador> modificadores;
};

class Cliente
{
    private:
    int id;
    std::string nome;
    Build build;

    public:
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
    bool operator==(const Atendimento& outro) const;

};
#endif // ENTIDADES_H