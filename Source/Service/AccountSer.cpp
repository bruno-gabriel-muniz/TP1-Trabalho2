#include "Source/Service/Service.hpp"

PresentationInte* AccountCommandManageWallet::execute(Nome nome){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela result;
    char *errorMsg = nullptr;
    Ncpf cpf = contexto->getUser()->getNcpf();

    // Procura as carteiras no DB.
    string find_cpf_s = "SELECT NOME CODIGO PERFIL CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() +
                        "\" AND NOME = \"" + nome.getValor() +"\"";
    const char *find_cpf = find_cpf_s.c_str();

    bool exc_result = sqlite3_exec(db->getDB(), find_cpf, callback, &result, &errorMsg);
    // Retorna erro caso o SQLite falhe.
    if(exc_result != SQLITE_OK){
        sqlite3_free(errorMsg);
        throw runtime_error("Erro ao procurar a carteira: " + string(errorMsg));
    }
    // Retorna erro caso a carteira em questão não exista.
    if(result.size() == 0) throw runtime_error("Erro: carteira não encontrada.");
    else if (result.size() > 1) throw runtime_error("Erro: carteiras conflitantes.");

    // Atualiza os dados
    Codigo codigo;
    TipoPerfil perfil;
    Carteira *carteira = new Carteira();

    codigo.setValor(result[0]["CODIGO"]);
    perfil.setValor(result[0]["PERFIL"]);

    carteira->setNome(nome);
    carteira->setCodigo(codigo);
    carteira->setTipoPerfil(perfil);

    contexto->setCarteira(carteira);

    // Entra na cartiera
    return new InvestmentPre(contexto);
}

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
