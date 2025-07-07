#include "Presentation/Presentation.hpp"
#include "Service/Service.hpp"
#include "CtrState.hpp"

int main(){
    CtrState *State = new CtrState();
    AuthenticationSer *SerLogin = new AuthenticationSer(State);
    AuthenticationPre *TelaLogin = new AuthenticationPre(State, SerLogin);
    State->setState(TelaLogin);

    State->run();
    return 0;
}
