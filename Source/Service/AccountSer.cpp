#include "Source/Service/Service.hpp"

PresentationInte* AccountCommandManageWallet::execute(Nome nome){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela *result = new Tabela();
    char *errorMsg = nullptr;
    Ncpf cpf = contexto->getUser()->getNcpf();
    // Procura as carteiras na tabela de carteiras.
    string findWalletS = "SELECT NOME, CODIGO, PERFIL, CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() +
                        "\" AND NOME = \"" + nome.getValor() +"\"";
    
    db->exec(findWalletS, result, "Erro ao procurar a carteira: ");
    // Retorna erro caso a carteira em questão não exista.
    if(result->size() == 0) throw runtime_error("Erro: carteira não encontrada.");
    else if (result->size() > 1) throw runtime_error("Erro: carteiras conflitantes.");

    // Atualiza os dados
    Codigo codigo;
    TipoPerfil perfil;
    Carteira *carteira = new Carteira();


    codigo.setValor(result[0][0]["CODIGO"]);
    perfil.setValor(result[0][0]["PERFIL"]);

    carteira->setNome(nome);
    carteira->setCodigo(codigo);
    carteira->setTipoPerfil(perfil);

    contexto->setCarteira(carteira);

    // Entra na cartiera
    return new InvestmentPre(contexto);
}

void AccountCommandMakeWallet::execute(Nome nome, TipoPerfil perfil){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela *result = new Tabela();
    char *errorMsg = nullptr;
    Ncpf cpf = contexto->getUser()->getNcpf();

    // Procura as carteiras na tabela de carteiras.
    string findWalletS = "SELECT NOME, CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() + "\";";
    db->exec(findWalletS, result, "Erro ao procurar a carteira: ");
    
    // Retorna erro caso o limite de carteiras tenha sido atingido.
    if(result->size() >= 5) throw runtime_error("Erro: limite de Carteiras atingido.");
    for(Linha &linha : result[0]){
        if(linha["NOME"] == nome.getValor()) throw runtime_error("Erro: outra carteia já possui esse nome.");
    }

    Codigo codigo;
    codigo.setValor(gerarCodigo());

    //Atualiza os dados na tabela de carteiras;
    string insertWalletS = "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"" +
                            nome.getValor() + "\", \"" + codigo.getValor() + "\", \"" + perfil.getValor() +
                            "\", \"" + cpf.getValor() +
                            "\")";
    db->exec(insertWalletS, result, "Erro ao inserir a carteira: ");
}

// TODO: 
void AccountCommandRemoveWallet::execute(Nome nome){
    return;
}

// TODO:
vector<Carteira> AccountCommandListWallets::execute(){
    vector<Carteira> a;
    return a;
}

// TODO:
void AccountCommandChangeSenha::execute(Senha){
    return;
}

// TODO:
void AccountCommandChangeName::execute(Nome){
    return;
}

// TODO:
PresentationInte* AccountCommandRemoveAccount::execute(){
    return new AuthenticationPre(contexto);
}

// TODO:
PresentationInte* AccountCommandLogOut::execute(){
    return new AuthenticationPre(contexto);
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
