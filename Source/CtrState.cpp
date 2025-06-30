/**
 * @file CtrState.cpp
 * @brief Arquivo que define a classe CtrState, responsável pelo controle de estado da UI.
 */

#pragma once

#include <iostream>

#include "InterfacePresentation.hpp"
#include "Libs/entidades.hpp"

using namespace std;

/**
 * @class CtrState
 * @brief Gerencia o usuário, as carteiras e o estado da interface por meio da interface @ref PresentationInte "PresentationInte".
 */
class CtrState {
private:
    Conta user;
    array<Carteira, 5> carteiras;
    PresentationInte *state = nullptr, *request;

public:
    CtrState() {};
    /**
     * @brief Altera internamente o estado da UI.
     * @param request Instância do novo estado da UI.
     */
    void setState(PresentationInte *request);

    /**
     * @brief Utiliza o estado atual da UI para validar a transição de estado.
     * @throws std::runtime_error Caso ocorra falha na operação.
     */
    void change();

    /**
     * @brief Executa as trocas de estado e chama os métodos correspondentes.
     */
    void run();
};

void CtrState::setState(PresentationInte *rqst){
    state = rqst;
}

void CtrState::change(){
    try{
        state->change(request);
    }
    catch(runtime_error &x){
        cout << x.what() << "\n";
    }
}

void CtrState::run(){
    request = state->run();
    while(request != nullptr){
        change();
        request = state->run();
    }
}