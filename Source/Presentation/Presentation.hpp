/**
 * @file Presentation.hpp
 * @brief Define as classe que implementam a interface @ref PresentationInte "PresentationInte".
 */



/** 
 * @defgroup CamadaDeApresentação Camada de Apresentação
 * @{
 */


#pragma once

#include "Interfaces/InterfacePresentation.hpp"
#include "Interfaces/InterfacesService.hpp"
#include "CtrState.hpp"

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
        static string telaMain;
    public:
        
        inline AuthenticationPre(CtrState *ctx, AuthenticationServiceInte *service){context = ctx; ctrService = service;}

    
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

        PresentationInte* run();
        inline void change(PresentationInte *request){context->setState(request);}
};


/**
 * @class AccountPre
 * @brief Gerencia a UI do gerenciamento da conta e usa a interface @ref AccountServiceInte "AccountServiceInte" para validações internas.
 */
class AccountPre: public PresentationInte{
    private:
        AccountServiceInte *ctrService;
        Nome
            nomeManageWallet, nomeRemoveWallet, nomeMakeWallet,
            nomeChangeUser;
        TipoPerfil
            perfilMakeWallet;
        Senha
            senhaChangeUser;
        static string telaMain, telaManageWallets1, telaManageWallets2, telaEdit;
    public:

        inline AccountPre(CtrState *ctx, AccountServiceInte * ser){
            context = ctx;
            ctrService = ser;
        }

        string getWallets();

        void getDataManageWallet();
        void getDataRemoveWallet();
        void getDataMakeWallet();

        void getDataSenha();
        void getDataName();

        /**
         * @brief Define a saída do app.
         */
        inline nullptr_t exit() {return nullptr;}
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
        PresentationInte* run();
        inline void change(PresentationInte *request) {context->setState(request);}
};

/**
 * @class InvestmentPre
 * @brief Gerencia a parte de investimentos e usa a interface @ref InvestmentServiceInte "InvestmentServiceInte" para validações internas.
 */
class InvestmentPre: public PresentationInte{
    private:
        InvestmentServiceInte *ctrService;

        Nome *nomeCarteira = new Nome();
        TipoPerfil *perfilCarteira = new TipoPerfil();
        CodigoNeg codigoNovaOrdem, codigoRemoveOrdem;
        Data dataNovaOrdem;
        Quantidade qntNovaOrdem;

        static string telaMain, telaEditCarteira, telaManageOrders1, telaManageOrders2;
    public:

        InvestmentPre(CtrState *ctx, InvestmentServiceInte *service){context = ctx; ctrService = service;};

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
         * @brief Formata as ordens da carteira.
         */
        string listOrders();

        /**
         * @brief Exibe a opção de acessar o menu de @ref showManageOrders "ManageOrders" e showEditCarteira "EditCarteira".
         */
        PresentationInte* showMain();
        inline PresentationInte* run() {return showMain();};
        inline void change(PresentationInte *request) {context->setState(request);};
};

/** @} */
