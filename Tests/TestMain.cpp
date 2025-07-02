#include "Tests/TestCtrState.cpp"
#include "Tests/TestAuthenticationSer.cpp"

int main(){
    TestCtrStateRun().run();
    TestMakeAccount().run();
    TestMakeAccountF().run();
    TestMakeLogin().run();
}