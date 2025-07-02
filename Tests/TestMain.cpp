#include "Tests/TestCtrState.cpp"
#include "Tests/TestAuthenticationSer.cpp"

int main(){
    TestCtrStateRun().run();
    cout << "\n\n";
    TestMakeAccount().run();
    TestMakeAccountF().run();
    cout << "\n\n";
    TestMakeLogin().run();
    TestMakeLoginF().run();
}