#include "Tests/TestCtrState.cpp"
#include "Tests/TestAuthenticationSer.cpp"
#include "Tests/TestAccount.cpp"

int main(){
    cout << "\n";
    cout << "\t\t\t\t\t__Controller state__";
    cout << "\n\n";
    TestCtrStateRun().run();
    cout << "\n\n";
    cout << "\t\t\t\t\t__Authentication__";
    cout << "\n\n";
    TestMakeAccount().run();
    TestMakeAccountF().run();
    cout << "\n\n";
    TestMakeLogin().run();
    TestMakeLoginF().run();
    cout << "\n\n";
    cout << "\t\t\t\t\t__Account__";
    cout << "\n\n";
    TestMakeWallet().run();
    TestMakeWalletFDuplicate().run();
    TestMakeWalletFLimitWallet().run();
}