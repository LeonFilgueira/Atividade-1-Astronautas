#ifndef ASTRONAUTAS_VOO_H
#define ASTRONAUTAS_VOO_H

#include <string>
#include <vector>


enum class Estado {
    Planejado,
    EmCurso,
    FinalizadoSucesso,
    FinalizadoExplosão
};

class Voo {
public:
    int codigo;
    std::vector<std::string> passageiros;
    Estado estado;

    void alterar_estado(Estado estado);
    Voo(int cod);

};


#endif //ASTRONAUTAS_VOO_H
