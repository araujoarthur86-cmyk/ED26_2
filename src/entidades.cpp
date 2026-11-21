#include "entidades.h"

//Atendimento Prioritário

bool Atendimento::operator>(const Atendimento &outro) const
{
    return 
    (
    prioridade > outro.prioridade 
    || 
    (prioridade == outro.prioridade && idCliente < outro.idCliente)
    );
}

bool Atendimento::operator==(const Atendimento& outro) const
{
    return idCliente == outro.idCliente;
}