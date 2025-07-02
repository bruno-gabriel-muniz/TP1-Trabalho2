#include "Source/Service/Service.hpp"

using namespace std;

PresentationInte* AuthentCommandMakeAccount::execute(Ncpf cpf, Senha senha, Nome nome){
    // Inicia os dados do DB.
    DB *db = DB::getInstance();
    Tabela result;
    char *errorMsg = nullptr;

    // Procura cpf no DB.
    string find_cpf_s = "SELECT CPF FROM Contas WHERE CPF = \"" + cpf.getValor() + '"';
    const char *find_cpf = find_cpf_s.c_str();

    bool exc_result = sqlite3_exec(db->getDB(), find_cpf, callback, &result, &errorMsg);
    if(exc_result != SQLITE_OK){
        throw runtime_error("Erro ao validar a disponibilidade do CPF: " + string(errorMsg));
        sqlite3_free(errorMsg);
    }

    // Retorna erro caso o cpf já esteja em uso.
    if(result.size() != 0){
        result.clear();
        throw runtime_error("O CPF já está sendo utilizado.");
    }
    result.clear();

    // Insere a conta no DB.
    string insertNewAccount_s = "INSERT INTO Contas (CPF, SENHA, NOME) VALUES (\""
                             + cpf.getValor() + "\", \"" + senha.getValor() + "\", \"" + nome.getValor() + "\")";
    const char *insertNewAccount = insertNewAccount_s.c_str();

    exc_result = sqlite3_exec(db->getDB(), insertNewAccount, nullptr, 0, &errorMsg);
    if(exc_result != SQLITE_OK){
        throw runtime_error("Erro ao inserir a nova conta no DB: " + string(errorMsg));
        sqlite3_free(errorMsg);
    }

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
    Tabela result;
    char *errorMsg = nullptr;

    // Procura cpf no DB.
    string find_cpf_s = "SELECT CPF, SENHA, NOME FROM Contas WHERE CPF = \"" + cpf.getValor() + "\"";
    const char *find_cpf = find_cpf_s.c_str();

    bool exc_result = sqlite3_exec(db->getDB(), find_cpf, callback, &result, &errorMsg);
    if(exc_result != SQLITE_OK){
        throw runtime_error("Erro ao validar a disponibilidade do CPF: " + string(errorMsg));
        sqlite3_free(errorMsg);
    }

    // Valida a senha e o cpf.
    if(result.size() != 1){
        result.clear();
        throw runtime_error("CPF não encontrado.");
    }
    if(result[0]["SENHA"] != senha.getValor().c_str()){
        result.clear();
        throw runtime_error("Senha incorreta.");
    }
    
    // Atualiza os dados do CtrState.
    Conta *user = new Conta();
    user->setNcpf(cpf);
    user->setSenha(senha);
    Nome nome = Nome();
    nome.setValor(result[0]["NOME"]);
    user->setNome(nome);
    contexto->setUser(user);

    result.clear();
    return new AccountPre(contexto);

}

PresentationInte* AuthenticationSer::makeAccount(Ncpf cpf, Senha senha, Nome nome){
    return cmdMakeAccount.execute(cpf, senha, nome);
}

PresentationInte* AuthenticationSer::login(Ncpf cpf, Senha senha){
    return cmdLogin.execute(cpf, senha);
}
