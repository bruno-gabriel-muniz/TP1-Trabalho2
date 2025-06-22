#include <iostream>

#include "InterfacePresentation.hpp"
#include "Libs/entidades.hpp"

using namespace std;

/**
 * @class CtrState
 * @brief Gerencia o usuário, carteiras e o estado da interface.
*/
class CtrState{
    private:
        Conta user;
        array<Carteira, 5> carteiras;
        PresentationInte *state, *request;
    public:
        /**
         * @brief Altera internamente estado da UI.
         * @param request Instacia do novo estado da UI.
         * @return void
         */
        void setState(PresentationInte *request);
        /**
         * @brief Usa o estado da UI para validar a alteração.
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return void
         */
        void change();
        /**
         * @brief Roda as trocas de estado e chama os outros métodos.
         * @return void
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