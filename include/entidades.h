#ifndef ENTIDADES_H
#define ENTIDADES_H
#include <string>
#include <Build.h>

// Entidades relacionadas a clientes
struct Atributo
{
    int id;
    std::string nome;
};

class Cliente
{
    private:
    int id;
    std::string nome;
    Build build;
    bool ativo;

    public:
    Cliente(int id, const std::string &nome, const Build &build);
    int getId() const;
    std::string getNome() const;
    int getPoder() const;
    bool isAtivo() const;
    void desativar();
};

//Entidades relacionadas ao mapa
struct Regiao
{
    int id;
    std::string nome;
};

struct Rota{
    int RegiaoA;
    int RegiaoB;
    int custo;
}

struct Atendimento
{
    int idCliente;
    int prioridade;
};
#endif // ENTIDADES_H