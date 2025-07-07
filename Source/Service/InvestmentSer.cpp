#include "Service/Service.hpp"

// Função para a formatação adequada para a classe dinheiro.
string formatDinheiro(string dinheiro){
    // Dados da função;
    string out;
    int size = dinheiro.size();

    // Valida a entrada;
    if(size > 9) throw runtime_error("Valor ultrapassa o limite permitido.");
    
    // Formata a entrada;
    for(int i = 0; i < size; i++){
        if(!isdigit(dinheiro[i]))
            // Retorna erro caso exista um caractere invalido;
            throw runtime_error("Valor possui caracteres não numéticos: " + dinheiro[i]);
        else if(size-i == 2)
            out += ",";
        else if((size-i-2)%3 == 0 and i != 0)
            out += ".";
        out += dinheiro[i];
    }
    return out;
}

void InvestmentCommandRemoveOrder::execute(CodigoNeg codNeg){
    // Inicia o DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Dados do contexto
    Carteira *userCarteira = contexto->getCarteira();

    // Deleta a ordem do Usuário;
    string deleteOrder =
        "DELETE FROM Ordens WHERE CODIGO = \"" +
        userCarteira->getCodigo().getValor() + "\" AND \"CODIGO NEG\" = \"" +
        codNeg.getValor() + "\";";
    
    db->exec(deleteOrder, resultSql, "Erro ao remover a ordem no DB: ");
    delete resultSql;
    return ;
}

void InvestmentCommandMakeOrder::execute(CodigoNeg codNeg, Quantidade quantidade, Data data){
    // Inicia o DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Dados do contexto
    Carteira *userCarteira = contexto->getCarteira();

    // Encontra a ordem no dados históricos;
    string findOrdem = 
        "SELECT PRECO FROM DadosHistoricos WHERE DATA = \"" +
        data.getValor() + "\" AND \"CODIGO NEG\" = \"" + codNeg.getValor() + "\";";
    db->exec(findOrdem, resultSql, "Erro ao procurar a folha nos dados históricos: ");

    // Valida a ordem;
    if(resultSql->size() > 1) throw runtime_error("Mais de uma folha encontrada.");
    else if(resultSql->size() == 0) throw runtime_error("Nenhuma folha encontrada.");

    // Cria a ordem;
    string makeOrder =
        "INSERT INTO Ordens (CODIGO, \"CODIGO NEG\", DATA, PRECO, QUANTIDADE) VALUES (\"" +
        userCarteira->getCodigo().getValor() + "\", \"" + codNeg.getValor() + "\", \"" +
        data.getValor() + "\", \"" + resultSql[0][0]["PRECO"] + "\", \"" + quantidade.getValor() +
        "\")";
    db->exec(makeOrder, resultSql, "Erro ao adicionar a nova ordem no DB: ");
    delete resultSql;
    return ;
}

vector<Ordem> InvestmentCommandListOrders::execute(){
    // Inicia o DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Dados do contexto
    Carteira *userCarteira = contexto->getCarteira();

    // Procura as ordens no DB
    string findOrdens =
        "SELECT * FROM Ordens WHERE CODIGO = " +
        userCarteira->getCodigo().getValor(); +
        ";";
    db->exec(findOrdens, resultSql, "Erro ao procurar as ordens da carteira: ");

    // Prepara a saida da função;
    vector<Ordem> out;
    Codigo codigo; codigo.setValor(userCarteira->getCodigo().getValor());
    for(Linha linha : resultSql[0]){
        Ordem ordem;

        CodigoNeg codigoNeg;
        codigoNeg.setValor(linha["CODIGO NEG"]);
        
        Data data;
        data.setValor(linha["DATA"]);
        
        string preco;
        preco = linha["PRECO"];
        Dinheiro dinheiro;
        dinheiro.setValor(formatDinheiro(preco));
        
        Quantidade quantidade;
        quantidade.setValor(linha["QUANTIDADE"]);

        ordem.setCodigo(codigo);
        ordem.setCodigoNeg(codigoNeg);
        ordem.setData(data);
        ordem.setDinheiro(dinheiro);
        ordem.setQuantidade(quantidade);

        out.push_back(ordem);
    }

    delete resultSql;
    return out;
}

void InvestmentCommandEditWallet::execute(Nome* nome, TipoPerfil* perfil){
    // Inicia o DB
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();
    
    if(nome){
        // Verifica se o usuário possui outra carteira com o nome novo
        string cpf = contexto->getUser()->getNcpf().getValor();
        db->exec(
            "SELECT * FROM Carteiras WHERE CPF = \"" +
            cpf + "\" AND NOME = \"" + nome->getValor() +
            "\";",
            resultSql,
            "Erro ao verificar a disponibilidade do nome: "
        );
        if(resultSql->size() != 0) {
            delete resultSql;
            throw runtime_error("Outra carteira já possui esse nome.");
        }

        // Atualiza o contexto e o DB;
        contexto->getCarteira()->setNome(*nome);
        db->exec(
           "UPDATE Carteiras SET NOME = \"" +
           nome->getValor() + "\" WHERE CODIGO = " +
           contexto->getCarteira()->getCodigo().getValor() +
           ";",
            resultSql,
            "Erro ao atualizar o nome da carteira no DB: "
        );
    }

    if(perfil){
        // Atualiza o contexto e o DB;
        contexto->getCarteira()->setTipoPerfil(*perfil);
        db->exec(
           "UPDATE Carteiras SET PERFIL = \"" +
           perfil->getValor() + "\" WHERE CODIGO = " +
           contexto->getCarteira()->getCodigo().getValor() +
           ";",
            resultSql,
            "Erro ao atualizar o Perfil da carteira no DB: "
        );
    }

    delete resultSql;
    return ;
}


void InvestmentSer::removeOrder(CodigoNeg codNeg){
    return cmdRemoveOrder.execute(codNeg);
};
void InvestmentSer::makeOrder(CodigoNeg codNeg, Quantidade quantidade, Data data){
    return cmdMakeOrder.execute(codNeg, quantidade, data);
};
vector<Ordem> InvestmentSer::listOrders(){
    return cmdListOrders.execute();
};
void InvestmentSer::editWallet(Nome* nome, TipoPerfil* perfil){
    return cmdEditWallet.execute(nome, perfil);
};