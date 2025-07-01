/**
 * @file Service.hpp
 * @brief Define as classes que implementam as interfaces de serviço: @ref InterfacesService.hpp "InterfacesService"
 */

#pragma once

#include "Source/InterfacesService.hpp"
#include "Source/Presentation/Presentation.hpp"
#include "Source/DB.cpp"

// Command

/** 
 * @defgroup ComandosService Comandos de Serviço
 * @{
 */

/**
 * @class Command
 * @brief Classe base e template que encapsula a execução dos comandos da interface @ref InterfacesService.hpp "InterfacesService".
 */
class Command {
protected:
    CtrState *contexto;

public:
    /**
     * @brief Construtor base.
     * @param ctx Ponteiro para @ref CtrState "CtrState", permitindo acesso aos dados do app.
     */
    Command(CtrState *ctx) : contexto(ctx) {}

    ~Command() = default;
};

/** @} */

//---------

/**
 * @class AuthentCommandLogin
 * @ingroup ComandosService
 * @brief Executa o login.
 */
class AuthentCommandLogin : public Command {
public:
    AuthentCommandLogin(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de login.
     */
    PresentationInte* execute(Ncpf cpf, Senha senha);
};

/**
 * @class AuthentCommandMakeAccount
 * @ingroup ComandosService
 * @brief Cria uma nova conta.
 */
class AuthentCommandMakeAccount : public Command {
public:
    AuthentCommandMakeAccount(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de criação de conta.
     */
    PresentationInte* execute(Ncpf cpf, Senha senha, Nome nome);
};

/**
 * @class AuthenticationSer
 * @brief Implementa a interface @ref AuthenticationServiceInte "AuthenticationServiceInte" utilizando o padrão Command.
 */
class AuthenticationSer : public AuthenticationServiceInte {
private:
    AuthentCommandLogin cmdLogin;
    AuthentCommandMakeAccount cmdMakeAccount;

public:
    AuthenticationSer(CtrState *ctx) : cmdLogin(ctx), cmdMakeAccount(ctx) {
        context = ctx;
    };
    PresentationInte* login(Ncpf cpf, Senha senha);
    PresentationInte* makeAccount(Ncpf cpf, Senha senha, Nome nome);
};

//---------

/**
 * @class AccountCommandLogOut
 * @ingroup ComandosService
 * @brief Executa o logout da conta.
 */
class AccountCommandLogOut : public Command {
public:
    AccountCommandLogOut(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de logout.
     */
    PresentationInte* execute();
};

/**
 * @class AccountCommandRemoveAccount
 * @ingroup ComandosService
 * @brief Remove a conta ativa.
 */
class AccountCommandRemoveAccount : public Command {
public:
    AccountCommandRemoveAccount(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de remoção de conta.
     */
    PresentationInte* execute();
};

/**
 * @class AccountCommandChangeName
 * @ingroup ComandosService
 * @brief Altera o nome da conta.
 */
class AccountCommandChangeName : public Command {
public:
    AccountCommandChangeName(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de alteração de nome.
     */
    void execute(Nome nome);
};

/**
 * @class AccountCommandChangeSenha
 * @ingroup ComandosService
 * @brief Altera a senha da conta.
 */
class AccountCommandChangeSenha : public Command{
public:
    AccountCommandChangeSenha(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de alteração de senha.
     */
    void execute(Senha senha);
};

/**
 * @class AccountCommandListWallets
 * @ingroup ComandosService
 * @brief Lista as carteiras da conta.
 */
class AccountCommandListWallets : public Command {
public:
    AccountCommandListWallets(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de listagem das carteiras.
     */
    vector<Carteira> execute();
};

/**
 * @class AccountCommandMakeWallet
 * @ingroup ComandosService
 * @brief Cria uma nova carteira.
 */
class AccountCommandMakeWallet : public Command {
public:
    AccountCommandMakeWallet(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de criação de carteira.
     */
    void execute(Nome nome, TipoPerfil perfil);
};

/**
 * @class AccountCommandRemoveWallet
 * @ingroup ComandosService
 * @brief Remove uma carteira existente.
 */
class AccountCommandRemoveWallet : public Command {
public:
    AccountCommandRemoveWallet(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de remoção de carteira.
     */
    void execute(Nome nome);
};

/**
 * @class AccountCommandManageWallet
 * @ingroup ComandosService
 * @brief Acessa o gerenciamento de uma carteira.
 */
class AccountCommandManageWallet : public Command {
public:
    AccountCommandManageWallet(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de gerenciamento de carteira.
     */
    PresentationInte* execute(Nome nome);
};

/**
 * @class AccountSer
 * @brief Implementa a interface @ref AccountServiceInte "AccountServiceInte" utilizando o padrão Command.
 */
class AccountSer : public AccountServiceInte {
private:
    AccountCommandLogOut cmdLogOut;
    AccountCommandRemoveAccount cmdRemoveAccount;
    AccountCommandChangeName cmdChangeName;
    AccountCommandChangeSenha cmdChangeSenha;
    AccountCommandListWallets cmdListWallets;
    AccountCommandMakeWallet cmdMakeWallet;
    AccountCommandRemoveWallet cmdRemoveWallet;
    AccountCommandManageWallet cmdManageWallet;

public:
    AccountSer(CtrState *ctx);

    PresentationInte* manageWallet(Nome nome);
    void removeWallet(Nome nome);
    void makeWallet(Nome nome, TipoPerfil perfil);
    vector<Carteira> listWallets();
    void changeSenha(Senha senha);
    void changeName(Nome nome);
    PresentationInte* removeAccount();
    PresentationInte* logOut();
};

//---------------

/**
 * @class InvestmentCommandEditWallet
 * @ingroup ComandosService
 * @brief Edita a carteira ativa.
 */
class InvestmentCommandEditWallet : public Command {
public:
    InvestmentCommandEditWallet(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de edição da carteira.
     */
    void execute(Nome* nome = nullptr, TipoPerfil* perfil = nullptr);
};

/**
 * @class InvestmentCommandListOrders
 * @ingroup ComandosService
 * @brief Lista as ordens da carteira ativa.
 */
class InvestmentCommandListOrders : public Command {
public:
    InvestmentCommandListOrders(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de listagem das ordens.
     */
    vector<Ordem> execute();
};

/**
 * @class InvestmentCommandMakeOrder
 * @ingroup ComandosService
 * @brief Cria uma nova ordem de compra.
 */
class InvestmentCommandMakeOrder : public Command {
public:
    InvestmentCommandMakeOrder(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de criação de ordem.
     */
    void execute(CodigoNeg codNeg, Quantidade quantidade, Data data);
};

/**
 * @class InvestmentCommandRemoveOrder
 * @ingroup ComandosService
 * @brief Remove uma ordem do histórico.
 */
class InvestmentCommandRemoveOrder : public Command {
public:
    InvestmentCommandRemoveOrder(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de remoção de ordem.
     */
    void execute(CodigoNeg codNeg);
};

/**
 * @class InvestmentCommandCancelOrder
 * @ingroup ComandosService
 * @brief Cancela uma ordem da carteira, caso ainda esteja no prazo.
 */
class InvestmentCommandCancelOrder : public Command {
public:
    InvestmentCommandCancelOrder(CtrState *ctx) : Command(ctx) {}

    /**
     * @brief Executa o comando de cancelamento de ordem.
     */
    void execute(CodigoNeg codNeg);
};

/**
 * @class InvestmentSer
 * @brief Implementa a interface @ref InvestmentServiceInte "InvestmentServiceInte" utilizando o padrão Command.
 */
class InvestmentSer : public InvestmentServiceInte {
private:
    InvestmentCommandEditWallet cmdEditWallet;
    InvestmentCommandListOrders cmdListOrders;
    InvestmentCommandMakeOrder cmdMakeOrder;
    InvestmentCommandRemoveOrder cmdRemoveOrder;
    InvestmentCommandCancelOrder cmdCancelOrder;

public:
    InvestmentSer(CtrState *ctx);

    void cancelOrder(CodigoNeg codNeg);
    void removeOrder(CodigoNeg codNeg);
    void makeOrder(CodigoNeg codNeg, Quantidade quantidade, Data data);
    vector<Ordem> listOrders();
    void editWallet(Nome* nome = nullptr, TipoPerfil* perfil = nullptr);
};
