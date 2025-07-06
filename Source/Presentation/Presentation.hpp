/**
 * @file Presentation.hpp
 * @brief Define as classe que implementam a interface @ref PresentationInte "PresentationInte".
 */



/** 
 * @defgroup CamadaDeApresentação Camada de Apresentação
 * @{
 */


#pragma once

#include "Source/InterfacePresentation.hpp"
#include "Source/InterfacesService.hpp"
#include "Source/CtrState.hpp"

using namespace std;

/**
 * @class AuthenticationPre
 * @brief Gerencia a UI de Autenticação/Login e usa a interface @ref AuthenticationServiceInte "AuthenticationServiceInte" para validações internas.
 */
class AuthenticationPre: public PresentationInte{
    private:
        Ncpf cpfLogin, cpfMakeAccount;
        Senha senhaLogin, senhaMakeAccount;
        Nome nomeMakeAccount;
        AuthenticationServiceInte *ctrService;
    public:
        
        AuthenticationPre(CtrState *ctx){context = ctx;};

        void setService(AuthenticationServiceInte *service);
    
        /**
         * @brief Define a saída do app.
         * @return nullptr.
         */
        PresentationInte* exit();
        /**
         * @brief Exibe o menu de login com validação via serviço.
         * @return Próxima UI.
         */
        PresentationInte* showMainMenu();

        void getDataLogin();

        void getDataMakeAccount();

        static string telaMain;
        PresentationInte* run();
        void change(PresentationInte *request);
};


inline void AuthenticationPre::setService(AuthenticationServiceInte *service) {ctrService = service;}

inline void AuthenticationPre::change(PresentationInte *request) {context->setState(request);}


/**
 * @class AccountPre
 * @brief Gerencia a UI do gerenciamento da conta e usa a interface @ref AccountServiceInte "AccountServiceInte" para validações internas.
 */
class AccountPre: public PresentationInte{
    public:

        AccountPre(CtrState *ctx){context = ctx;};

        /**
         * @brief Define a saída do app.
         */
        nullptr_t exit();
        /**
         * @brief Exibe o menu de edição da conta com validação via serviço.
         * @return Próxima UI.
         */
        PresentationInte* showEditAccount();
        /**
         * @brief Exibe as carteiras dando a opção de entrar nelas com validação via serviço.
         * @return Próxima UI.
         */
        PresentationInte* showWallets();
        PresentationInte* run() {return this;};
        void change(PresentationInte *request) {};
};

/**
 * @class PersAccountPre
 * @brief Representa uma UI estática para contas, indicando que a instância de @ref AccountPre "AccountPre" não deve ser substituída.
 */
class PersAccountPre: public PresentationInte{
    //Classe que indica que a AccountPre não precisa ser alterada.
    public:

        PersAccountPre(CtrState *ctx){context = ctx;};

        PresentationInte* run() {return this;};
        void change(PresentationInte *request) {};
};

/**
 * @class InvestmentPre
 * @brief Gerencia a parte de investimentos e usa a interface @ref InvestmentServiceInte "InvestmentServiceInte" para validações internas.
 */
class InvestmentPre: public PresentationInte{
    public:

        InvestmentPre(CtrState *ctx){context = ctx;};

        /**
         * @brief Define a volta para a UI anterior.
         * @return UI anterior.
         */
        PresentationInte* backInterface();
        /**
         * @brief Exibe o menu de edição da carteircom validação via serviço.
         */
        void showEditCarteira();
        /**
         * @brief Exibe o menu de gerenciamento das ordencom validação via serviço.
         */
        void showManageOrders();
        /**
         * @brief Exibe a opção de acessar o menu de @ref showManageOrders "ManageOrders" e showEditCarteira "EditCarteira".
         */
        void showMain();
        PresentationInte* run() {return this;};
        void change(PresentationInte *request) {};
};

/** @} */
