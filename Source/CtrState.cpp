#include <iostream>

#include "InterfacePresentation.hpp"
#include "Libs/entidades.hpp"

using namespace std;

class CtrState{
    private:
        Conta user;
        array<Carteira, 5> carteiras;
        PresentationInte *state, *request;
    public:
        void setState(PresentationInte *request);
        void change();
        void run();
};

void CtrState::setState(PresentationInte *rqst){
    state = rqst;
}

void CtrState::change(){
    try{
        state->change(request, this);
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