#ifndef ASTRONAUTAS_CONTROLE_H
#define ASTRONAUTAS_CONTROLE_H

#include <vector>
#include <string>
#include "Astronauta.h"
#include "Voo.h"

class Controle {
public:
    std::vector<Astronauta> astronautas;
    std::vector<Voo> voos;

    int buscar_astronauta(std::string cpf);
    int buscar_voo(int codigo);

    void cadastrar_astronauta(std::string cpf, int idade, std::string nome);
    void cadastrar_voo(int codigo);
    void adicionar_astronauta(std::string cpf, int codigo);
    void remover_astronauta(std::string cpf, int codigo);
    void lancar_voo(int codigo);
    void explodir_voo(int codigo);
    void finalizar_voo(int codigo);
    void listar_voos();
    void listar_mortos();

};

#endif
