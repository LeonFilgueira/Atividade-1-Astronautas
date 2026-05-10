#include <iostream>
#include <string>
#include <vector>
#include "Controle.h"
using namespace std;

int main() {
    string comando;
    Controle controle;

    while (cin >> comando) {
        if (comando == "FIM") {
            break;
        }
        if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;

            cin >> cpf >> idade;
            getline(cin >> ws, nome);
            controle.cadastrar_astronauta(cpf, idade, nome);
        }
        if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            controle.cadastrar_voo(codigo);
        }
        if (comando == "ADICIONAR_ASTRONAUTA") {
            int codigo;
            string cpf;

            cin >> cpf;
            cin >> codigo;

            controle.adicionar_astronauta(cpf, codigo);
        }
        if (comando == "REMOVER_ASTRONAUTA") {
            int codigo;
            string cpf;

            cin >> cpf;
            cin >> codigo;
            
            controle.remover_astronauta(cpf, codigo);
        }
        if (comando == "LANCAR_VOO") {
            int codigo;

            cin >> codigo;
            controle.lancar_voo(codigo);
        }
        if (comando == "EXPLODIR_VOO") {
            int codigo;

            cin >> codigo;
            controle.explodir_voo(codigo);

        }
        if (comando == "FINALIZAR_VOO") {
            int codigo;

            cin >> codigo;
            controle.finalizar_voo(codigo);
        }
        if (comando == "LISTAR_VOOS") {
            controle.listar_voos();
        }
        if (comando == "LISTAR_MORTOS") {
            controle.listar_mortos();
        }
    }


    return 0;

}