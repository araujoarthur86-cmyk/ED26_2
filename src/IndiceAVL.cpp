#include "IndiceAVL.h"

IndiceA::IndiceA() : raiz(nullptr) {}

IndiceA::~IndiceA()
{
    liberar(raiz);
}

void IndiceA::liberar(No *no)
{
    if (!no) return;
    liberar(no->esq);
    liberar(no->dir);
    delete no;
}

int IndiceA::altura(const No *no)
{
    return no ? no->altura : 0;
}

void IndiceA::atualizarAltura(No *no)
{
    int esquerda = altura(no->esq);
    int direita = altura(no->dir);
    no->altura = 1 + (esquerda > direita ? esquerda : direita);
}

IndiceA::No *IndiceA::girarDireita(No *no)
{
    // EXP: ++rotacoes;
    No *topo = no->esq;
    no->esq = topo->dir;
    topo->dir = no;
    atualizarAltura(no);
    atualizarAltura(topo);
    return topo;
}

IndiceA::No *IndiceA::girarEsquerda(No *no)
{
    // EXP: ++rotacoes;
    No *topo = no->dir;
    no->dir = topo->esq;
    topo->esq = no;
    atualizarAltura(no);
    atualizarAltura(topo);
    return topo;
}

IndiceA::No *IndiceA::balancear(No *no)
{
    atualizarAltura(no);
    int diferenca = altura(no->esq) - altura(no->dir);
    if (diferenca > 1)
    {
        if (altura(no->esq->dir) > altura(no->esq->esq))
            no->esq = girarEsquerda(no->esq);
        return girarDireita(no);
    }
    if (diferenca < -1)
    {
        if (altura(no->dir->esq) > altura(no->dir->dir))
            no->dir = girarDireita(no->dir);
        return girarEsquerda(no);
    }
    return no;
}

IndiceA::No *IndiceA::inserir(No *no, Celula cliente)
{
    if (!no) return new No{cliente, 1, nullptr, nullptr};
    // EXP: ++visitas;
    if (cliente < no->cliente)
        no->esq = inserir(no->esq, cliente);
    else
        no->dir = inserir(no->dir, cliente);
    return balancear(no);
}

IndiceA::No *IndiceA::remover(No *no, Celula cliente)
{
    if (!no) return nullptr;
    // EXP: ++visitas;
    if (cliente < no->cliente)
        no->esq = remover(no->esq, cliente);
    else if (no->cliente < cliente)
        no->dir = remover(no->dir, cliente);
    else
    {
        if (!no->esq || !no->dir)
        {
            No *filho = no->esq ? no->esq : no->dir;
            delete no;
            return filho;
        }
        No *sucessor = no->dir;
        while (sucessor->esq) sucessor = sucessor->esq;
        no->cliente = sucessor->cliente;
        no->dir = remover(no->dir, no->cliente);
    }
    return balancear(no);
}

void IndiceA::cadastrarCliente(int idCliente, int poder)
{
    raiz = inserir(raiz, {idCliente, poder});
}

void IndiceA::encerrarAtendimento(int idCliente, int poder)
{
    raiz = remover(raiz, {idCliente, poder});
}

void IndiceA::coletar(const No *no, int minimo, int maximo, ResultadoBuscaIndice &saida)
{
    if (!no) return;
    // EXP: ++visitas;
    int poder = no->cliente.poder;
    if (poder >= minimo) coletar(no->esq, minimo, maximo, saida);
    if (minimo <= poder && poder <= maximo) saida.push_back(no->cliente);
    if (poder <= maximo) coletar(no->dir, minimo, maximo, saida);
}

void IndiceA::buscarPorPoder(int poder, ResultadoBuscaIndice &saida)
{
    coletar(raiz, poder, poder, saida);
}

void IndiceA::buscarPorFaixaPoder(int minimo, int maximo, ResultadoBuscaIndice &saida)
{
    coletar(raiz, minimo, maximo, saida);
}

void IndiceA::copiar(const No *no, RepresentacaoIndice &destino)
{
    if (!no) return;
    copiar(no->esq, destino);
    destino.cadastrarCliente(no->cliente.idCliente, no->cliente.poder);
    copiar(no->dir, destino);
}

void IndiceA::copiarPara(RepresentacaoIndice &destino) const
{
    copiar(raiz, destino);
}
