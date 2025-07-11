#include "Presentation/Presentation.hpp"

using namespace std;

string InvestmentPre::telaMain = string(80, '=') + "\n" +
    string(33, ' ') + "|Investments|\n" + string(80, '-') + "\n\n\n" +
    " EditWallet: 1\n ManageOrders: 2\n Back: 3\n input -> ";

string InvestmentPre::telaEditCarteira = "Tela de Edição de Carteira";
string InvestmentPre::telaManageOrders = "Tela de Gerenciamento de Ordens";

void InvestmentPre::showEditCarteira() {}; // TODO
void InvestmentPre::showManageOrders() {}; // TODO

PresentationInte* InvestmentPre::backInterface(){
    return ctrService->back();
}

PresentationInte* InvestmentPre::showMain(){
    string resp;
    PresentationInte *request;
    cout << telaMain;
    while(true){
        cin >> resp;
        if (resp == "1") {
            showEditCarteira();
            cout << "\n\n\n\n\n" << telaMain;
        } else if (resp == "2") {
            showManageOrders();
            cout << "\n\n\n\n\n" << telaMain;
        } else if (resp == "3") {
            request = backInterface();
            break;
        } else {
            cout << "\n\n\n\n\nOpção inválida, tente novamente.\n" << telaMain;
        }
    }
    return request;
}
