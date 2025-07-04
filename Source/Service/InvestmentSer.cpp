#include "Source/Service/Service.hpp"

// TODO:
void InvestmentCommandCancelOrder::execute(CodigoNeg codNeg){
    return ;
}

// TODO:
void InvestmentCommandRemoveOrder::execute(CodigoNeg codNeg){
    return ;
}

// TODO:
void InvestmentCommandMakeOrder::execute(CodigoNeg codNeg, Quantidade quantidade, Data data){
    return ;
}

// TODO:
vector<Ordem> InvestmentCommandListOrders::execute(){
    vector<Ordem> a;
    return a;
}

// TODO:
void InvestmentCommandEditWallet::execute(Nome* nome = nullptr, TipoPerfil* perfil = nullptr){
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
void InvestmentSer::editWallet(Nome* nome = nullptr, TipoPerfil* perfil = nullptr){
    return cmdEditWallet.execute(nome, perfil);
};