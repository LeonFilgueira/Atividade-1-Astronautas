//
// Created by leon on 09/05/2026.
//

#include <iostream>
#include "Controle.h"

using namespace std;

int Controle::buscar_astronauta(string cpf) {
    for (int ii = 0; ii < astronautas.size(); ii++) {
        if (astronautas[ii].cpf == cpf) {
            return ii;
        }
    }
    return -1;
}

int Controle::buscar_voo(int codigo) {
    for (int ii = 0; ii < voos.size(); ++ii) {
        if (voos[ii].codigo == codigo) {
            return ii;
        }
    }
    return -1;
}

void Controle::cadastrar_astronauta(string cpf, int idade, string nome) {
    if (buscar_astronauta(cpf) != -1) {
        cout << "Erro: Já existe um astronauta com o cpf " << cpf << " cadastrado" << endl;
    } else {
        astronautas.push_back(Astronauta(cpf, nome, idade));
        cout << "Astronauta de cpf " << cpf << "cadastrado com sucesso" << endl;
    }
}

void Controle::cadastrar_voo(int codigo) {
    if (buscar_voo(codigo) != -1) {
        cout << "Erro: Já existe um voo com o código " << codigo << endl;
    } else {
        voos.push_back(Voo(codigo));
        cout << "Voo de código " << codigo << "cadastrado com sucesso" << endl;
    }
}

void Controle::adicionar_astronauta(string cpf, int codigo) {
    int indice_astronauta = buscar_astronauta(cpf);
    int indice_voo = buscar_voo(codigo);

    if (indice_astronauta != -1) {
        if (indice_voo != -1) {
            if (voos[indice_voo].estado == Estado::Planejado) {
                if (astronautas[indice_astronauta].vida) {
                    if (voos[indice_voo].passageiros.empty()) {
                        voos[indice_voo].passageiros.push_back(cpf);
                        cout << "O astronauta de cpf " << cpf << " foi adicionado ao voo de código " << codigo << endl;
                    }else {
                        for (int ii = 0; ii < voos[indice_voo].passageiros.size(); ++ii) {
                            if (voos[indice_voo].passageiros[ii] == cpf) {
                                cout << "Erro: o astronauta de cpf " << cpf << " já está cadastrado nesse voo";
                                return;
                            }
                        }
                        voos[indice_voo].passageiros.push_back(cpf);
                        cout << "O astronauta de cpf " << cpf << " foi adicionado ao voo de código " << codigo << endl;
                    }
                } else {
                    cout << "Erro: o astronauta cadastado com o cpf " << cpf << " está morto" << endl;
                }
            } else {
                cout << "Erro: o voo de código " << codigo << " não está em curso" << endl;
            }
        } else {
            cout << "Erro: não existe um voo cadastado com o código " << codigo << endl;
        }
    } else {
        cout << "Erro: não existe um astronauta cadastado com o cpf " << cpf << endl;
    }
}

void Controle::remover_astronauta(string cpf, int codigo) {
    int indice_astronauta = buscar_astronauta(cpf);
    int indice_voo = buscar_voo(codigo);

    if (indice_astronauta != -1) {
        if (indice_voo != -1) {
            if (voos[indice_voo].estado == Estado::Planejado) {
                for (int ii = 0; ii < voos[indice_voo].passageiros.size(); ++ii) {
                    if (voos[indice_voo].passageiros[ii] == cpf) {
                        voos[indice_voo].passageiros[ii].erase(voos[indice_voo].passageiros[ii].begin() + ii);
                        cout << "O astronauta de cpf " << cpf << "foi removido do voo de código " << codigo << endl;
                        return;
                    }
                }
                cout << "Erro: o astronauta de cpf " << cpf << " não está no voo de codigo " << codigo << endl;
            } else {
                cout << "Erro: só é possível remover astronautas de voos planejados" << endl;
            }
        } else {
            cout << "Erro: não existe um voo cadastado com o código " << codigo << endl;
        }
    } else {
        cout << "Erro: não existe um astronauta cadastado com o cpf " << cpf << endl;
    }
}

void Controle::lancar_voo(int codigo) {
    int indice_voo = buscar_voo(codigo);
    if (indice_voo != -1) {
        if (voos[indice_voo].estado == Estado::Planejado) {
            if (voos[indice_voo].passageiros.size() > 0) {
                for (int ii = 0; ii < voos[indice_voo].passageiros.size(); ++ii) {
                    if (astronautas[buscar_astronauta(voos[indice_voo].passageiros[ii])].ocupado) {
                        cout << "Erro: há pelo menos um astronauta morto no voo" << endl;
                        return;
                    }
                    if (not astronautas[buscar_astronauta(voos[indice_voo].passageiros[ii])].vida) {
                        cout << "Erro: há pelo menos um astronauta ocupado no voo" << endl;
                        return;
                    }
                }
                voos[indice_voo].alterar_estado(Estado::EmCurso);
                for (int ii = 0; ii < voos[indice_voo].passageiros.size(); ++ii) {
                    astronautas[buscar_astronauta(voos[indice_voo].passageiros[ii])].ocupar();
                }
                cout << "O voo de código " << codigo << " foi lançado com sucesso" << endl;
            }
        } else {
            cout << "Erro: o voo de código " << codigo << " não está planejado" << endl;
        }
    } else {
        cout << "Erro: não existe um voo cadastado com o código " << codigo << endl;
    }
}

void Controle::explodir_voo(int codigo) {
    int indice_voo = buscar_voo(codigo);

    if (indice_voo != -1) {
        if (voos[indice_voo].estado == Estado::EmCurso) {
            for (int ii = 0; ii < voos[indice_voo].passageiros.size(); ++ii) {
                astronautas[buscar_astronauta(voos[indice_voo].passageiros[ii])].morrer();
            }
            voos[indice_voo].alterar_estado(Estado::FinalizadoExplosão);
            cout << "O voo de código " << codigo << " sofreu uma explosão" << endl;
        } else {
            cout << "Erro: o voo de código " << codigo << " não está em curso" << endl;
        }
    } else {
        cout << "Erro: não existe um voo cadastado com o código " << codigo << endl;
    }
}

void Controle::finalizar_voo(int codigo) {
    int indice_voo = buscar_voo(codigo);

    if (indice_voo != -1) {
        if (voos[indice_voo].estado == Estado::EmCurso) {
            voos[indice_voo].alterar_estado(Estado::FinalizadoSucesso);
            for (int ii = 0; ii < voos[indice_voo].passageiros.size(); ++ii) {
                astronautas[buscar_astronauta(voos[indice_voo].passageiros[ii])].desocupar();
            }
            cout << "O voo de código " << codigo << " foi finalizado com sucesso" << endl;
        } else {
            cout << "Erro: o voo de código " << codigo << " não está em curso" << endl;
        }
    } else {
        cout << "Erro: não existe um voo cadastado com o código " << codigo << endl;
    }
}

void Controle::listar_voos() {
    cout << "\n===LISTANDO VOOS CADASTRADOS===\n" << endl;
    for (int ii = 0; ii < voos.size(); ++ii) {
        if (voos[ii].estado == Estado::Planejado) {
            cout << "Código de voo: " << voos[ii].codigo << endl;
            cout << "Estado de voo: planejado" << endl;
            cout << "Passageiros: " << endl;
            for (int jj = 0; jj < voos[ii].passageiros.size(); ++jj) {
                cout << "\n     Passageiro " << jj+1 << ":" << endl;
                cout << "       CPF: " << voos[ii].passageiros[jj] << endl;
                cout << "       Nome: " << astronautas[buscar_astronauta(voos[ii].passageiros[jj])].nome << endl;
            }
            cout << "\n" << endl;
        }
    }
    for (int ii = 0; ii < voos.size(); ++ii) {
        if (voos[ii].estado == Estado::EmCurso) {
            cout << "Código de voo: " << voos[ii].codigo << endl;
            cout << "Estado de voo: em curso" << endl;
            cout << "Passageiros: " << endl;
            for (int jj = 0; jj < voos[ii].passageiros.size(); ++jj) {
                cout << "\n     Passageiro " << jj+1 << ":" << endl;
                cout << "       CPF: " << voos[ii].passageiros[jj] << endl;
                cout << "       Nome: " << astronautas[buscar_astronauta(voos[ii].passageiros[jj])].nome << endl;
            }
            cout << "\n" << endl;
        }
    }
    for (int ii = 0; ii < voos.size(); ++ii) {
        if (voos[ii].estado == Estado::FinalizadoSucesso) {
            cout << "Código de voo: " << voos[ii].codigo << endl;
            cout << "Estado de voo: finalizado com sucesso" << endl;
            cout << "Passageiros: " << endl;
            for (int jj = 0; jj < voos[ii].passageiros.size(); ++jj) {
                cout << "\n     Passageiro " << jj+1 << ":" << endl;
                cout << "       CPF: " << voos[ii].passageiros[jj] << endl;
                cout << "       Nome: " << astronautas[buscar_astronauta(voos[ii].passageiros[jj])].nome << endl;
            }
            cout << "\n" << endl;
        }
    }
    for (int ii = 0; ii < voos.size(); ++ii) {
        if (voos[ii].estado == Estado::FinalizadoExplosão) {
            cout << "Código de voo: " << voos[ii].codigo << endl;
            cout << "Estado de voo: finalizado com explosão" << endl;
            cout << "Passageiros: " << endl;
            for (int jj = 0; jj < voos[ii].passageiros.size(); ++jj) {
                cout << "\n     Passageiro " << jj+1 << ":" << endl;
                cout << "       CPF: " << voos[ii].passageiros[jj] << endl;
                cout << "       Nome: " << astronautas[buscar_astronauta(voos[ii].passageiros[jj])].nome << endl;
            }
            cout << "\n" << endl;
        }
    }
    cout << "====FIM DA LISTAGEM DE VOOS====\n" << endl;
}

void Controle::listar_mortos() {
    cout << "\n========LISTANDO MORTOS========\n" << endl;
    for (int ii = 0; ii < astronautas.size(); ++ii) {
        if (not astronautas[ii].vida) {
            cout << "CPF: " << astronautas[ii].cpf << endl;
            cout << "   Nome: " << astronautas[ii].nome << endl;
            cout << "   Voos que participou:" << endl;
            for (int jj = 0; jj < voos.size(); ++jj) {
                for (int kk = 0; kk < voos[jj].passageiros.size(); ++kk) {
                    if (voos[jj].estado != Estado::Planejado && voos[jj].passageiros[kk] == astronautas[ii].cpf) {
                        cout << "       Código: " << voos[jj].codigo << endl;
                    }
                }

            }
            cout << "\n" << endl;
        }
    }
    cout << "\n===FIM DA LISTAGEM DE MORTOS===\n" << endl;
}
