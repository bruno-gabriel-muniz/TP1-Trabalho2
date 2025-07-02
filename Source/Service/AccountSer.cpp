#include "Source/Service/Service.hpp"



PresentationInte* AccountSer::manageWallet(Nome nome) {
    return cmdManageWallet.execute(nome);
};
void AccountSer::removeWallet(Nome nome) {
    return cmdRemoveWallet.execute(nome);
};
void AccountSer::makeWallet(Nome nome, TipoPerfil perfil) {
    return cmdMakeWallet.execute(nome, perfil);
};
vector<Carteira> AccountSer::listWallets() {
    return cmdListWallets.execute();
};
void AccountSer::changeSenha(Senha senha) {
    return cmdChangeSenha.execute(senha);
};
void AccountSer::changeName(Nome nome) {
    return cmdChangeName.execute(nome);
};
PresentationInte* AccountSer::removeAccount() {
    return cmdRemoveAccount.execute();
};
PresentationInte* AccountSer::logOut() {
    return cmdLogOut.execute();
};
