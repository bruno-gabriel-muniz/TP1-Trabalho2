#include "Tests/TestCtrState.cpp"
#include "Tests/TestAuthenticationSer.cpp"
#include "Tests/TestAccount.cpp"
#include "Tests/TestInvestment.cpp"

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
    cout << "\n\n";
    TestManageWallet().run();
    TestManageWalletNotFound().run();
    cout << "\n\n";
    TestListWallet().run();
    TestListWalletEmpty().run();
    cout << "\n\n";
    TestChangeSenha().run();
    cout << "\n\n";
    TestChangeNome().run();
    cout << "\n\n";
    TestRemoveAccount().run();
    cout << "\n\n";
    TestRemoveAccount().run();
    cout << "\n\n";
    cout << "\t\t\t\t\t__Investment__";
    cout << "\n\n";
    TestMakeOrder().run();
    cout << "\n\n";
    TestRemoveOrder().run();
    cout << "\n\n";
    TestListOrders().run();
    cout << "\n\n";
    TestEdidWallet().run();
}