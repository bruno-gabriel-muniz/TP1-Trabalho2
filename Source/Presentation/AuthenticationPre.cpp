#include "Presentation/Presentation.hpp"

string AuthenticationPre::telaMain =
    string(80, '=') + "\n" + string(33, ' ') + "|Login|\n" + string(80, '-') + "\n\n\n" +
    " MakeAcount: 1\n Login: 2\n Exit: 3\n input -> ";

void AuthenticationPre::getDataMakeAccount() {
    string resp;
    cout << "\n\n\tDigite o seu CPF -> ";
    cin >> resp;
    cpfMakeAccount.setValor(resp);
    cout << "\n\n\tDigite a Senha da conta -> ";
    cin >> resp;
    senhaMakeAccount.setValor(resp);
    cout << "\n\n\tDigite o Nome da conta -> ";
    cin >> resp;
    nomeMakeAccount.setValor(resp);
    return ;
}

void AuthenticationPre::getDataLogin() {
    string resp;
    cout << "\n\n\tDigite o seu CPF -> ";
    cin >> resp;
    cpfLogin.setValor(resp);
    cout << "\n\n\tDigite a sua Senha -> ";
    cin >> resp;
    senhaLogin.setValor(resp);
    return ;
};

PresentationInte* AuthenticationPre::exit() {
    return nullptr;
};

PresentationInte* AuthenticationPre::showMainMenu() {
    PresentationInte* request;
    string resp;
    cout << telaMain;
    while(true){
        cin >> resp;
        if (resp == "1") {
            try{
                getDataMakeAccount();
                request = ctrService->makeAccount(cpfMakeAccount, senhaMakeAccount, nomeMakeAccount);
            } catch (exception &e){
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaMain;
                continue;
            }
            return request;
        } else if (resp == "2") {
            try{
                getDataLogin();
                request = ctrService->login(cpfLogin, senhaLogin);
            } catch (exception &e){
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaMain;
                continue;
            }
            return request;
        } else if (resp == "3") {
            return exit();
        } else cout << "\n\n\n\n\n" << "Entrada não reconhecida.\n" << telaMain;
    }
};

PresentationInte* AuthenticationPre::run() {return showMainMenu();}
