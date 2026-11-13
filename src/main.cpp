#include <iostream>
#include <string>
#include "entidades.h"
#include "ArrayDinamico.h"
#include "ListaPrioridade.h"
#include "Indice.h"
#include "Mapa.h"

enum class TipoComando
{
  E,  // modo de Representacao Indice
  A,  // cadastra atributo
  C,  // cadastra cliente
  D,  // Encerra atendimento
  BP, // Busca por Poder exato
  BF, // Busca por Faixa de Poder
  R,  // Cadastro Regiao
  T,  // Cadastro de Rota
  CC, // Conectividade entre Regioes
  F,  // Insere na fila de atendimento
  Z,  // Atendimento
  INVALIDO
};

TipoComando identificarComando(const std::string &comando);

int main()
{
  ArrayDinamico<Atributo> atributos;
  ArrayDinamico<Cliente> clientes;
  Indice indice;
  Mapa mapa;
  FilaAtendimento fila;

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
      
      Atributo newAtributo{idAtributo, nomeAtributo};
      atributos.push_back(newAtributo);

      std::cout << "A " << idAtributo << "\n";
      break;
    }
    //Cadastra um cliente com a build especificada
    case TipoComando::C:
    {
      std::string nomeCliente;
      std::cin >> nomeCliente;
      int idCliente = clientes.size();

      int k; // numero de atributos na build
      std::cin >> k;
      int atributoId, valor;
      
      Build build;
      for(int i = 0; i < k; ++i)
      {
        std::cin >> atributoId >> valor;
        build.modificarAtributo(atributoId, valor);
      }

      clientes.push_back({idCliente, nomeCliente, build});
      indice.cadastrarCliente(idCliente, build.getPoder());
      std::cout << "C " << idCliente << "\n";
      break;
    }
    case TipoComando::D:
    {
      int idCliente;
      std::cin >> idCliente;

      indice.encerrarAtendimento(idCliente);
      Cliente &cliente = clientes.at(idCliente);
      cliente.desativar();

      std::cout << "D " << idCliente << "\n";
      break;
    }
    case TipoComando::BP:
    {
      // Lista os Clientes com determinado poder BP
      int poder;
      std::cin >> poder;

      indice.buscarPorPoder(poder);

      break;
    }
    case TipoComando::BF:
    { // Busca por faixa de Poder BF
      int poderMin, poderMax;
      std::cin >> poderMin >> poderMax;

      indice.buscarPorFaixaPoder(poderMin, poderMax);

      break;
    }
    case TipoComando::R:
    {
      std::string nomeRegiao;
      std::cin >> nomeRegiao;

      // mapa.cadastrarRegiao(nomeRegiao);
      std::cout << "R " << nomeRegiao << "\n";
      break;
    }
    case TipoComando::T:
    {
      int idRegiao1, idRegiao2, custo;
      std::cin >> idRegiao1 >> idRegiao2 >> custo;
      mapa.cadastrarRota(idRegiao1, idRegiao2, custo);

      std::cout << "T " /*<< mapa.getNomeRegiao(idRegiao1) << " " << mapa.getNomeRegiao(idRegiao2) << " " << custo*/ << "\n";
      break;
    }
    case TipoComando::CC:
    {
      int idRegiaoA, idRegiaoB;
      std::cin >> idRegiaoA >> idRegiaoB;
      std::string connected = mapa.areConnected(idRegiaoA, idRegiaoB);
      std::cout << "CC " << idRegiaoA << " " << idRegiaoB << connected << "\n";
      break;
    }
    case TipoComando::F:
    {
      int idCliente;
      char prioridade;
      std::cin >> idCliente >> prioridade;
      fila.inserirCliente(idCliente, prioridade);
      
      std::cout << "F " << fila.size() << "\n";
      break;
    }
    case TipoComando::Z:
    { // Atender até k Clientes
      int k;
      std::cin >> k;

      pendentes = fila.size();
      ArrayDinamico<Atendimento> atendimentos;
      fila.atenderClientes(k, atendimentos);
      atendidos = pendentes - fila.size();

      std::cout << "Z " << atendidos << "\n";

      if(atendidos > 0)
      {
        std::cout << "Clientes atendidos: ";
        for(int i = 0; i < atendidos; ++i)
        {
          std::cout << "atendimento_" << (i + 1) << atendimentos.at(i) << " ";
        }
        std::cout << "\n";
      }
      break;
    }
    case TipoComando::INVALIDO:
    {
      // Entrada do comando é sembre valida
      break;
    }
    }
  }
  return 0;
}

TipoComando identificarComando(const std::string &comando)
{
  if (comando == "E")
    return TipoComando::E;
  else if (comando == "A")
    return TipoComando::A;
  else if (comando == "C")
    return TipoComando::C;
  else if (comando == "D")
    return TipoComando::D;
  else if (comando == "BP")
    return TipoComando::BP;
  else if (comando == "BF")
    return TipoComando::BF;
  else if (comando == "R")
    return TipoComando::R;
  else if (comando == "T")
    return TipoComando::T;
  else if (comando == "CC")
    return TipoComando::CC;
  else if (comando == "F")
    return TipoComando::F;
  else if (comando == "Z")
    return TipoComando::Z;

  return TipoComando::INVALIDO;
}