#include "Voo.h"

void Voo::alterar_estado(Estado estado) {
    this ->estado = estado;
}

Voo::Voo(int cod) {
    this->codigo = cod;
    this->estado = Estado::Planejado;
}


