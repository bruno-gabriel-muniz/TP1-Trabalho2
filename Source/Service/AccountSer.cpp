#include "Service/Service.hpp"

PresentationInte* AccountCommandManageWallet::execute(Nome nome){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();
    char *errorMsg = nullptr;
    Ncpf cpf = contexto->getUser()->getNcpf();
    // Procura as carteiras na tabela de carteiras.
    string findWalletS = "SELECT NOME, CODIGO, PERFIL, CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() +
                        "\" AND NOME = \"" + nome.getValor() +"\"";
    
    db->exec(findWalletS, resultSql, "Erro ao procurar a carteira: ");
    // Retorna erro caso a carteira em questão não exista.
    if(resultSql->size() == 0) throw runtime_error("Erro: carteira não encontrada.");
    else if (resultSql->size() > 1) throw runtime_error("Erro: carteiras conflitantes.");

    // Atualiza os dados
    Codigo codigo;
    TipoPerfil perfil;
    Carteira *carteira = new Carteira();


    codigo.setValor(resultSql[0][0]["CODIGO"]);
    perfil.setValor(resultSql[0][0]["PERFIL"]);

    carteira->setNome(nome);
    carteira->setCodigo(codigo);
    carteira->setTipoPerfil(perfil);

    contexto->setCarteira(carteira);

    // Entra na cartiera
    delete resultSql;
    return new InvestmentPre(contexto);
}

void AccountCommandMakeWallet::execute(Nome nome, TipoPerfil perfil){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();
    char *errorMsg = nullptr;
    Ncpf cpf = contexto->getUser()->getNcpf();

    // Procura as carteiras na tabela de carteiras.
    string findWalletS = "SELECT NOME, CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() + "\";";
    db->exec(findWalletS, resultSql, "Erro ao procurar a carteira: ");
    
    // Retorna erro caso o limite de carteiras tenha sido atingido.
    if(resultSql->size() >= 5) throw runtime_error("Erro: limite de Carteiras atingido.");
    for(Linha &linha : resultSql[0]){
        if(linha["NOME"] == nome.getValor()) throw runtime_error("Erro: outra carteira já possui esse nome.");
    }

    Codigo codigo;
    codigo.setValor(gerarCodigo());

    //Atualiza os dados na tabela de carteiras;
    string insertWalletS = "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"" +
                            nome.getValor() + "\", \"" + codigo.getValor() + "\", \"" + perfil.getValor() +
                            "\", \"" + cpf.getValor() +
                            "\")";
    db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");
    delete resultSql;
}

// TODO: 
void AccountCommandRemoveWallet::execute(Nome nome){
    // Inica o DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Seleciona a carteira;
    string findWallet = "SELCET CODIGO FROM Carteiras WHERE CPF = \"" +
        contexto->getUser()->getNcpf().getValor() +
        "\" AND NOME = \"" + nome.getValor() + "\""
        ";";
    db->exec(findWallet, resultSql, "Erro ao procurar a carteira: ");

    // Devolve erro caso não ache a carteira.
    if(resultSql->size() != 1) throw runtime_error("Carteira não encontrada.");

    // Defini o valor do código da carteira.
    string codigo = resultSql[0][0]["CODIGO"];

    db->exec(findWallet, resultSql, "Erro ao verificar se a carteira possui ordens: ");

    // Verfica se a carteira possui ordens;
    string findOrders = "SELCET * FROM Ordens WHERE CODIGO = " + codigo +
        ";";
    db->exec(findOrders, resultSql, "Erro ao verificar se a carteira possui ordens: ");

    // Devolve erro caso a carteira tiver alguma ordem
    if(resultSql->size() >= 1) throw runtime_error("A carteira ainda possui ordens, não pode ser deletada.");

    // Deleta a carteira caso ela não possua ordens
    string deleteWallet = "DELETE * FROM Carteiras WHERE CODIGO = " + codigo + ";";
    db->exec(deleteWallet, resultSql, "Erro ao deletar a carteira do DB: ");

    return;
}

vector<Carteira> AccountCommandListWallets::execute(){
    // Configura os dados do DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Procura as carteiras no DB;
    db->exec(
        "SELECT NOME, CODIGO, PERFIL FROM Carteiras WHERE CPF = \""
        + contexto->getUser()->getNcpf().getValor() + "\";",
        resultSql,
        "Erro ao procurar as carteiras da conta: "
    );

    // Formata a saída.
    vector<Carteira> result;

    for(Linha a : resultSql[0]){
        Carteira carteira = Carteira();
        Nome nome = Nome();
        Codigo codigo = Codigo();
        TipoPerfil perfil = TipoPerfil();

        nome.setValor(a["NOME"]);
        codigo.setValor(a["CODIGO"]);
        perfil.setValor(a["PERFIL"]);
        
        carteira.setNome(nome);
        carteira.setCodigo(codigo);
        carteira.setTipoPerfil(perfil);

        result.push_back(carteira);
    }
    delete resultSql;
    return result;
}

void AccountCommandChangeSenha::execute(Senha senha){
    // Dados do DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    Ncpf cpfUser = contexto->getUser()->getNcpf();

    // Altera a senha no DB.
    db->exec(
        "UPDATE Contas SET SENHA = \"" + senha.getValor() +
        "\" WHERE CPF = \"" + cpfUser.getValor() + 
        "\";",
        resultSql,
        "Erro ao Atualizar a senha no DB: "
    );

    delete resultSql;
    return;
}

void AccountCommandChangeName::execute(Nome nome){
    // Dados do DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    Ncpf cpfUser = contexto->getUser()->getNcpf();

    // Altera o nome no DB.
    db->exec(
        "UPDATE Contas SET NOME = \"" + nome.getValor() +
        "\" WHERE CPF = \"" + cpfUser.getValor() + 
        "\";",
        resultSql,
        "Erro ao Atualizar o nome no DB: "
    );

    delete resultSql;
    return;
}

PresentationInte* AccountCommandRemoveAccount::execute(){
    // Inicia os dados do DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Remove a conta do DB;
    db->exec(
        "DELETE FROM Contas WHERE CPF = \"" +
        contexto->getUser()->getNcpf().getValor() +
        "\";",
        resultSql,
        "Erro ao deletar o Usuário do DB: "
    );

    contexto->setUser(nullptr);
    contexto->setCarteira(nullptr);
    
    delete resultSql;
    return new AuthenticationPre(contexto);
}

PresentationInte* AccountCommandLogOut::execute(){
    contexto->setUser(nullptr);
    contexto->setCarteira(nullptr);
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
