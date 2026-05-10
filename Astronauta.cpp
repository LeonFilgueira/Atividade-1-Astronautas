#include "Astronauta.h"

Astronauta::Astronauta(std::string cpf, std::string nome, int idade) {
    this->cpf = cpf;
    this->nome = nome;
    this->idade = idade;
    this->vida = true;
    this->ocupado = false;
}

void Astronauta::morrer() {
    this->vida = false;
    this->ocupado = true;
}

void Astronauta::ocupar() {
    this->ocupado = true;
}

void Astronauta::desocupar() {
    this->ocupado = false;
}
