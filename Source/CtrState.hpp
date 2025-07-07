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

#include "InterfacePresentation.hpp"
#include "Libs/entidades.hpp"

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

    inline void setUser(Conta *usr) {user = usr;}
    inline void setCarteira(Carteira *carts) {carteira = carts;}

    inline Conta* getUser() {return user;}
    inline Carteira* getCarteira() {return carteira;}

    /**
     * @brief Altera internamente o estado da UI.
     * @param request Instância do novo estado da UI.
     */
    void setState(PresentationInte *);

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

inline void CtrState::setState(PresentationInte *rqst){
    state = rqst;
}

inline void CtrState::change(){
    try{
        state->change(request);
    }
    catch(runtime_error &x){
        cout << x.what() << "\n";
    }
}

inline void CtrState::run(){
    request = state->run();
    while(request != nullptr){
        change();
        request = state->run();
    }
}

/** @} */
