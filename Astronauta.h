#ifndef ASTRONAUTAS_FUNCOES_H
#define ASTRONAUTAS_FUNCOES_H

#include <string>

class Astronauta {
    public:
    std::string cpf;
    std::string nome;
    int idade;
    bool vida;
    bool ocupado;

    Astronauta(std::string cpf, std::string nome, int idade);
    void morrer();
    void ocupar();
    void desocupar();
};


#endif //ASTRONAUTAS_FUNCOES_H
