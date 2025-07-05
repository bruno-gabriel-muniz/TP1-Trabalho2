#include "Source/Service/Service.hpp"

// TODO:
void InvestmentCommandCancelOrder::execute(CodigoNeg codNeg){
    return ;
}

// TODO:
void InvestmentCommandRemoveOrder::execute(CodigoNeg codNeg){
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
    return ;
}

// TODO:
vector<Ordem> InvestmentCommandListOrders::execute(){
    vector<Ordem> a;
    return a;
}

// TODO:
void InvestmentCommandEditWallet::execute(Nome* nome, TipoPerfil* perfil){
    return ;
}


void InvestmentSer::cancelOrder(CodigoNeg codNeg){
    return cmdCancelOrder.execute(codNeg);
};
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