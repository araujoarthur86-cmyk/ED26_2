#ifndef ARRAY_DINAMICO_H
#define ARRAY_DINAMICO_H

#include <stdexcept>

template <typename T>
class ArrayDinamico
{
private:
    T *array;
    int quantidade;
    int capacidade;

    void expandir();

public:
    ArrayDinamico(int capacidadeInicial = 5);

    // Realiza copia profunda para que cada ArrayDinamico possua seu proprio vetor.
    ArrayDinamico(const ArrayDinamico<T> &outro);
    // Aloca e copia antes de liberar o vetor atual.
    ArrayDinamico<T> &operator=(const ArrayDinamico<T> &outro);
    ~ArrayDinamico();

    void push_back(const T &elemento);

    void insert(int posicao, const T &elemento);

    void erase(int posicao);

    // Garante a capacidade solicitada sem alterar o tamanho logico.
    void reserve(int novaCapacidade);

    // Esvazia logicamente o array, preservando a memoria para reutilizacao.
    void clear();

    void swap(int a, int b);

    T &at(int indice);
    const T &at(int indice) const;

    int size() const;
    // EXP: int capacidadeReservada() const { return capacidade; }
};

template <typename T>
ArrayDinamico<T>::ArrayDinamico(int capacidadeInicial)
    : quantidade(0), capacidade(capacidadeInicial > 0 ? capacidadeInicial : 1)
{
    array = new T[capacidade];
}

template <typename T>
ArrayDinamico<T>::ArrayDinamico(const ArrayDinamico<T> &outro)
    : quantidade(outro.quantidade), capacidade(outro.capacidade)
{
    array = new T[capacidade];
    for (int i = 0; i < quantidade; ++i)
    {
        array[i] = outro.array[i];
    }
}

template <typename T>
ArrayDinamico<T> &ArrayDinamico<T>::operator=(const ArrayDinamico<T> &outro)
{
    if (this == &outro)
    {
        return *this;
    }

    T *novoArray = new T[outro.capacidade];
    for (int i = 0; i < outro.quantidade; ++i)
    {
        novoArray[i] = outro.array[i];
    }

    delete[] array;
    array = novoArray;
    quantidade = outro.quantidade;
    capacidade = outro.capacidade;

    return *this;
}

template <typename T>
ArrayDinamico<T>::~ArrayDinamico()
{
    delete[] array;
}

template <typename T>
void ArrayDinamico<T>::expandir()
{
    int novaCapacidade = capacidade * 2;
    T *novoArray = new T[novaCapacidade];

    for (int i = 0; i < quantidade; ++i)
    {
        novoArray[i] = array[i];
    }

    delete[] array;
    array = novoArray;
    capacidade = novaCapacidade;
}

template <typename T>
void ArrayDinamico<T>::push_back(const T &elemento)
{
    if (quantidade == capacidade)
    {
        expandir();
    }

    array[quantidade] = elemento;
    quantidade++;
}

template <typename T>
void ArrayDinamico<T>::insert(int posicao, const T &elemento)
{
    if (posicao < 0 || posicao > quantidade)
    {
        throw std::out_of_range("Indice fora dos limites");
    }

    // Preserva o valor quando elemento referencia uma posicao deste array.
    T copia = elemento;

    if (quantidade == capacidade)
    {
        expandir();
    }

    for (int i = quantidade; i > posicao; --i)
    {
        array[i] = array[i - 1];
    }

    array[posicao] = copia;
    ++quantidade;
}

template <typename T>
void ArrayDinamico<T>::erase(int posicao)
{
    if (posicao < 0 || posicao >= quantidade)
    {
        throw std::out_of_range("Indice fora dos limites");
    }

    for (int i = posicao; i < quantidade - 1; ++i)
    {
        array[i] = array[i + 1];
    }

    --quantidade;
}

template <typename T>
void ArrayDinamico<T>::reserve(int novaCapacidade)
{
    if (novaCapacidade <= capacidade)
    {
        return;
    }

    T *novoArray = new T[novaCapacidade];
    for (int i = 0; i < quantidade; ++i)
    {
        novoArray[i] = array[i];
    }

    delete[] array;
    array = novoArray;
    capacidade = novaCapacidade;
}

template <typename T>
void ArrayDinamico<T>::clear()
{
    quantidade = 0;
}

template <typename T>
void ArrayDinamico<T>::swap(int a, int b)
{
    if (a < 0 || a >= quantidade || b < 0 || b >= quantidade)
    {
        throw std::out_of_range("Indice fora dos limites");
    }

    T temp = this->at(a);

    this->at(a) = this->at(b);
    this->at(b) = temp;
}

template <typename T>
T &ArrayDinamico<T>::at(int indice)
{
    if (indice < 0 || indice >= quantidade)
    {
        throw std::out_of_range("Indice fora dos limites");
    }

    return array[indice];
}

template <typename T>
const T &ArrayDinamico<T>::at(int indice) const
{
    if (indice < 0 || indice >= quantidade)
    {
        throw std::out_of_range("Indice fora dos limites");
    }

    return array[indice];
}

template <typename T>
int ArrayDinamico<T>::size() const
{
    return quantidade;
}

#endif
