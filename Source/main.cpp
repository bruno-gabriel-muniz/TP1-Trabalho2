#include "Source/Presentation/AuthenticationPre.cpp"
#include "Source/Service/AuthenticationSer.cpp"
#include "Source/CtrState.hpp"

int main(){
    CtrState *State = new CtrState();
    AuthenticationPre *TelaLogin = new AuthenticationPre(State);
    AuthenticationSer *SerLogin = new AuthenticationSer(State);
    
    TelaLogin->setService(SerLogin);
    State->setState(TelaLogin);

    State->run();
    return 0;
}
