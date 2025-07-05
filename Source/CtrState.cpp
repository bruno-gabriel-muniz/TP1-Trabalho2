/**
 * @file CtrState.cpp
 * @brief Arquivo que define a classe CtrState, responsável pelo controle de estado da UI.
 */



/** 
 * @defgroup CamadaControleEstado Camada do Controle do Estado
 * @{
 */


#pragma once

#include <iostream>

#include "Source/InterfacePresentation.hpp"
#include "Source/Libs/entidades.hpp"

using namespace std;

/**
 * @class CtrState
 * @brief Gerencia o usuário, as carteiras e o estado da interface por meio da interface @ref PresentationInte "PresentationInte".
 */
class CtrState {
private:
    Conta *user;
    Carteira *carteira;
    PresentationInte *state = nullptr, *request;

public:
    CtrState() {};

    void setUser(Conta *usr) {user = usr;}
    void setCarteira(Carteira *carts) {carteira = carts;}

    Conta* getUser() {return user;}
    Carteira* getCarteira() {return carteira;}

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

/** @} */
