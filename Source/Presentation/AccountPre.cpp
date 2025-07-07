#include "Presentation/Presentation.hpp"
#include "Service/Service.hpp"

using namespace std;

string AccountPre::telaMain =
    string(80, '=') + "\n" + string(33, ' ') + "|Conta|\n" + string(80, '-') + "\n\n\n" +
    " ManageWallets: 1\n EditAccount: 2\n Exit: 3\n input -> ";

string AccountPre::telaManageWallets1 =
    string(80, '-') + "\n" + string(33, ' ') + "|Manage|\n\n";

string AccountPre::telaManageWallets2 =
    " Acesser Carteira: 1\n Remover Carteira: 2\n Criar Carteira: 3\n Voltar: 4\n input -> ";

PresentationInte* AccountPre::run(){
    PresentationInte *request;
    string resp;
    cout << telaMain;
    while (true) {
        cin >> resp;
        if (resp == "1"){
            request = showWallets();
            if (request) break;
            cout << "\n\n\n\n\n" << telaMain;
        } else if (resp == "2"){

        } else if (resp == "3"){
            request = exit();
            break;
        } else cout << "\n\n\n\n\n" << "Entrada não reconhecida.\n" << telaMain;
    }
    
    return request;
}

string AccountPre::getWallets(){
    vector<Carteira> carteiras = ctrService->listWallets();
    string out = "";
    for(Carteira carteira : carteiras){
        out += "Nome: " + carteira.getNome().getValor() + "\n\t";
        out += "Codigo: " + carteira.getCodigo().getValor();
        out += " | Perfil: " + carteira.getTipoPerfil().getValor();
        out += "\n\n";
    }
    return out;
}

void AccountPre::getDataManageWallet(){
    string resp;
    cout << "\n\n\tDigite o Nome da Carteira: ";
    cin >> resp;
    nomeManageWallet.setValor(resp);
}

void AccountPre::getDataRemoveWallet(){
    string resp;
    cout << "\n\n\tDigite o Nome da Carteira: ";
    cin >> resp;
    nomeRemoveWallet.setValor(resp);
}

void AccountPre::getDataMakeWallet(){
    string resp;
    cout << "\n\n\tDigite o Nome da Carteira: ";
    cin >> resp;
    nomeMakeWallet.setValor(resp);
    
    cout << "\n\n\tDigite o Perfil da Carteira: ";
    cin >> resp;
    perfilMakeWallet.setValor(resp);
}

PresentationInte* AccountPre::showWallets(){
    // Configura os dados da UI
    PresentationInte *request;
    string resp, telaRetorno = telaManageWallets1 + getWallets() + telaManageWallets2;
    cout << telaRetorno;
    while (true) {
        cin >> resp;

        // Tenta acessar a carteira;
        if (resp == "1"){
            try{
                getDataManageWallet();
                request = ctrService->manageWallet(nomeManageWallet);
                break;
            } catch (exception &e){
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaRetorno;
                continue;
            }
    
        // Tenta remover a carteira;
        } else if (resp == "2"){
            try{
                getDataRemoveWallet();
                ctrService->removeWallet(nomeRemoveWallet);
                telaRetorno = telaManageWallets1 + getWallets() + telaManageWallets2;
            } catch (exception &e){
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaRetorno;
                continue;
            }
            telaRetorno = telaManageWallets1 + getWallets() + telaManageWallets2;
            cout << "\n\n\n\n\n" << telaRetorno;

        // Tenta criar a carteira;
        } else if (resp == "3"){
            try{
                getDataMakeWallet();
                ctrService->makeWallet(nomeMakeWallet, perfilMakeWallet);
            } catch (exception &e){
                cout << "\n\n\n\n\n" << e.what() << "\n" << telaRetorno;
                continue;
            }
            telaRetorno = telaManageWallets1 + getWallets() + telaManageWallets2;
            cout << "\n\n\n\n\n" << telaRetorno;

        // Volta para a tela anterior;
        } else if (resp == "4"){
            request = nullptr;
            break;
        } else cout << "\n\n\n\n\n" << "Entrada não reconhecida.\n" << telaRetorno;
    }
    
    return request;
};
