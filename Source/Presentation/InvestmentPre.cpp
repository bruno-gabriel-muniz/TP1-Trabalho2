#include "Presentation/Presentation.hpp"

using namespace std;

string InvestmentPre::telaMain = string(80, '=') + "\n" +
    string(33, ' ') + "|Investments|\n" + string(80, '-') + "\n\n\n" +
    " EditWallet: 1\n ManageOrders: 2\n Back: 3\n input -> ";

string InvestmentPre::telaEditCarteira = string(80, '-') + "\n" +
    string(33, ' ') + "|Edit Wallet|\n" + "\n\n\n" +
    " Mudar Nome: 1\n Mudar Perfil: 2\n Voltar: 3\n input -> ";

string InvestmentPre::telaManageOrders1 = string(80, '-') + "\n" +
    string(33, ' ') + "|Manage Orders|\n" + "\n";

string InvestmentPre::telaManageOrders2 = 
    " Criar Ordem: 1\n Remover Ordem: 2\n Voltar: 3\n input -> ";

void InvestmentPre::showEditCarteira() {
    string resp;
    cout << telaEditCarteira;
    while(true){
        cin >> resp;
        if (resp == "1"){
            cout << "\n\n\tDigite o novo nome da carteira: ";
            cin >> resp;
            try {
                nomeCarteira->setValor(resp);
                ctrService->editWallet(nomeCarteira, nullptr);
                cout << "\n\n\n\n\n" << telaEditCarteira;
            } catch (exception &e) {
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaEditCarteira;
            }
        } else if (resp == "2"){
            cout << "\n\n\tDigite o novo perfil da carteira: ";
            cin >> resp;
            try {
                perfilCarteira->setValor(resp);
                ctrService->editWallet(nullptr, perfilCarteira);
                cout << "\n\n\n\n\n" << telaEditCarteira;
            } catch (exception &e) {
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaEditCarteira;
            }
        } else if (resp == "3"){
            return;
        } else {
           cout << "\n\n\n\n\nOpção inválida, tente novamente.\n" << telaEditCarteira;
        }
    }
};

string InvestmentPre::listOrders() {
    vector<Ordem> ordens = ctrService->listOrders();
    string out = string(33, '-') + "\n";
    for (Ordem& ordem : ordens) {
        out += ordem.getCodigoNeg().getValor() + " -> Data: " + ordem.getData().getValor() + "\n";
        out += "\t Preço: " + ordem.getDinheiro().getValor() + " | Quantidade: " + ordem.getQuantidade().getValor();
        out += "\n";
    }
    out += string(33, '-') + "\n\n";
    return out;
}


void InvestmentPre::showManageOrders() {
    string resp, telaManageOrders;
    telaManageOrders = telaManageOrders1 + listOrders() + telaManageOrders2;
    cout << telaManageOrders;
    while(true){
        cin >> resp;
        if (resp == "1"){
            
        } else if (resp == "2"){
            
        } else if (resp == "3"){
            return;
        } else {
           cout << "\n\n\n\n\nOpção inválida, tente novamente.\n" << telaManageOrders;
        }
    }
};

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
