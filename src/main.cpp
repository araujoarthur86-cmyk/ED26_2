#include <iostream>
#include <string>

#include "ArrayDinamico.h"
#include "FilaAtendimento.h"
#include "Indice.h"
#include "Mapa.h"
#include "entidades.h"

enum class TipoComando
{
    E,
    A,
    C,
    D,
    BP,
    BF,
    R,
    T,
    CC,
    F,
    Z,
    INVALIDO
};

TipoComando identificarComando(const std::string &comando);

void imprimirBuscaPorPoder(
    int poder,
    const ResultadoBuscaIndice &resultados)
{
    std::cout << "BP " << poder;
    if (resultados.size() == 0)
    {
        std::cout << " VAZIO\n";
        return;
    }

    for (int i = 0; i < resultados.size(); ++i)
    {
        const Celula &cliente = resultados.at(i);
        std::cout << " cliente_" << (i + 1) << " " << cliente.idCliente;
    }
    std::cout << '\n';
}

void imprimirBuscaPorFaixa(
    int poderMin,
    int poderMax,
    const ResultadoBuscaIndice &resultados)
{
    std::cout << "BF " << poderMin << " " << poderMax;
    if (resultados.size() == 0)
    {
        std::cout << " VAZIO\n";
        return;
    }

    for (int i = 0; i < resultados.size(); ++i)
    {
        const Celula &cliente = resultados.at(i);
        std::cout << " cliente_" << (i + 1) << " "
            << cliente.idCliente << " " << cliente.poder;
    }
    std::cout << '\n';
}

int main()
{
    ArrayDinamico<Atributo> atributos;
    ArrayDinamico<Cliente> clientes;
    Indice indice;
    Mapa mapa;
    FilaAtendimento fila;
    ResultadoBuscaIndice resultadosBusca;

    std::string comando;
    while (std::cin >> comando)
    {
        TipoComando tipo = identificarComando(comando);
        switch (tipo)
        {
        case TipoComando::E:
        {
            char modo;
            std::cin >> modo;
            indice.mudarModo(modo);
            std::cout << "E " << modo << '\n';
            break;
        }
        case TipoComando::A:
        {
            std::string nomeAtributo;
            std::cin >> nomeAtributo;

            int idAtributo = atributos.size();
            Atributo novoAtributo{idAtributo, nomeAtributo};
            atributos.push_back(novoAtributo);

            std::cout << "A " << idAtributo << '\n';
            break;
        }
        case TipoComando::C:
        {
            std::string nomeCliente;
            std::cin >> nomeCliente;

            int idCliente = clientes.size();
            int quantidadeAtributos;
            std::cin >> quantidadeAtributos;

            Build build;
            for (int i = 0; i < quantidadeAtributos; ++i)
            {
                int idAtributo;
                int valor;
                std::cin >> idAtributo >> valor;
                build.modificarAtributo(idAtributo, valor);
            }

            clientes.push_back({idCliente, nomeCliente, build});
            const Cliente &cliente = clientes.at(idCliente);
            indice.cadastrarCliente(cliente.getId(), cliente.getPoder());

            std::cout << "C " << idCliente << " " << cliente.getPoder()
                << '\n';
            break;
        }
        case TipoComando::D:
        {
            int idCliente;
            std::cin >> idCliente;

            const Cliente &cliente = clientes.at(idCliente);
            indice.encerrarAtendimento(idCliente, cliente.getPoder());
            std::cout << "D " << cliente.getNome() << " "
                << cliente.getPoder() << '\n';
            break;
        }
        case TipoComando::BP:
        {
            int poder;
            std::cin >> poder;
            indice.buscarPorPoder(poder, resultadosBusca);
            imprimirBuscaPorPoder(poder, resultadosBusca);
            break;
        }
        case TipoComando::BF:
        {
            int poderMin;
            int poderMax;
            std::cin >> poderMin >> poderMax;
            indice.buscarPorFaixaPoder(poderMin, poderMax, resultadosBusca);
            imprimirBuscaPorFaixa(poderMin, poderMax, resultadosBusca);
            break;
        }
        case TipoComando::R:
        {
            std::string nomeRegiao;
            std::cin >> nomeRegiao;
            int idRegiao = mapa.cadastrarRegiao(nomeRegiao);
            std::cout << "R " << idRegiao << '\n';
            break;
        }
        case TipoComando::T:
        {
            int idRegiaoA;
            int idRegiaoB;
            int custo;
            std::cin >> idRegiaoA >> idRegiaoB >> custo;
            mapa.cadastrarRota(idRegiaoA, idRegiaoB, custo);

            std::cout << "T " << mapa.getNomeRegiao(idRegiaoA) << " "
                << mapa.getNomeRegiao(idRegiaoB) << " " << custo << '\n';
            break;
        }
        case TipoComando::CC:
        {
            int idRegiaoA;
            int idRegiaoB;
            std::cin >> idRegiaoA >> idRegiaoB;

            bool conectado = mapa.areConnected(idRegiaoA, idRegiaoB);
            std::cout << "CC " << mapa.getNomeRegiao(idRegiaoA) << " "
                << mapa.getNomeRegiao(idRegiaoB) << " "
                << (conectado ? "SIM" : "NAO") << '\n';
            break;
        }
        case TipoComando::F:
        {
            int idCliente;
            int prioridade;
            std::cin >> idCliente >> prioridade;
            fila.inserirCliente(idCliente, prioridade);
            std::cout << "F " << fila.size() << '\n';
            break;
        }
        case TipoComando::Z:
        {
            int limite;
            std::cin >> limite;

            ArrayDinamico<Atendimento> atendimentos;
            fila.atenderClientes(limite, atendimentos);
            int quantidadeAtendida = atendimentos.size();
            std::cout << "Z " << quantidadeAtendida << '\n';

            if (quantidadeAtendida > 0)
            {
                for (int i = 0; i < quantidadeAtendida; ++i)
                {
                    const Atendimento &atendimento = atendimentos.at(i);
                    if (i > 0)
                    {
                        std::cout << ' ';
                    }
                    std::cout << "atendimento_" << (i + 1) << " "
                        << atendimento.idCliente << " "
                        << atendimento.prioridade;
                }
                std::cout << '\n';
            }
            break;
        }
        case TipoComando::INVALIDO:
            break;
        }
    }

    return 0;
}

TipoComando identificarComando(const std::string &comando)
{
    if (comando == "E") return TipoComando::E;
    if (comando == "A") return TipoComando::A;
    if (comando == "C") return TipoComando::C;
    if (comando == "D") return TipoComando::D;
    if (comando == "BP") return TipoComando::BP;
    if (comando == "BF") return TipoComando::BF;
    if (comando == "R") return TipoComando::R;
    if (comando == "T") return TipoComando::T;
    if (comando == "CC") return TipoComando::CC;
    if (comando == "F") return TipoComando::F;
    if (comando == "Z") return TipoComando::Z;
    return TipoComando::INVALIDO;
}
