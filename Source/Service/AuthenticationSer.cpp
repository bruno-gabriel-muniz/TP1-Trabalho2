#include "Source/Service/Service.hpp"

using namespace std;

PresentationInte* AuthentCommandMakeAccount::execute(Ncpf cpf, Senha senha, Nome nome){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela *result = new Tabela();
    char *errorMsg = nullptr;

    // Procura cpf no DB.
    string findCpfS = "SELECT CPF FROM Contas WHERE CPF = \"" + cpf.getValor() + '"';
    db->exec(findCpfS, result, "Erro ao procurar o CPF no DB de contas: ");
    // Retorna erro caso o cpf já esteja em uso.
    if(result->size() != 0){
        throw runtime_error("O CPF já está sendo utilizado.");
    }

    // Insere a conta no DB.
    string insertNewAccountS = "INSERT INTO Contas (CPF, SENHA, NOME) VALUES (\""
                             + cpf.getValor() + "\", \"" + senha.getValor() + "\", \"" + nome.getValor() + "\")";
    
    db->exec(insertNewAccountS, result, "Erro ao inserir a conta no DB: ");
    const char *insertNewAccount = insertNewAccountS.c_str();

    // Atualiza os dados do CtrState.
    Conta *user = new Conta();
    user->setNcpf(cpf);
    user->setSenha(senha);
    user->setNome(nome);
    contexto->setUser(user);

    return new AccountPre(contexto);
}

PresentationInte* AuthentCommandLogin::execute(Ncpf cpf, Senha senha){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela *result = new Tabela();
    char *errorMsg = nullptr;

    // Procura cpf no DB.
    string findCpfS = "SELECT CPF, SENHA, NOME FROM Contas WHERE CPF = \"" + cpf.getValor() + "\"";
    
    db->exec(findCpfS, result, "Erro ao procurar o CPF no DB de contas: ");

    // Valida a senha e o cpf.
    if(result->size() != 1){
        throw runtime_error("CPF não encontrado.");
    }
    if(result[0][0]["SENHA"] != senha.getValor().c_str()){
        throw runtime_error("Senha incorreta.");
    }
    
    // Atualiza os dados do CtrState.
    Conta *user = new Conta();
    user->setNcpf(cpf);
    user->setSenha(senha);
    Nome nome = Nome();
    nome.setValor(result[0][0]["NOME"]);
    user->setNome(nome);
    contexto->setUser(user);

    return new AccountPre(contexto);

}

PresentationInte* AuthenticationSer::makeAccount(Ncpf cpf, Senha senha, Nome nome){
    return cmdMakeAccount.execute(cpf, senha, nome);
}

PresentationInte* AuthenticationSer::login(Ncpf cpf, Senha senha){
    return cmdLogin.execute(cpf, senha);
}
