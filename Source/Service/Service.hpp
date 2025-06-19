#include "InterfacesService.hpp"

// command

template<typename TypeReturn>
class Command {
    protected:
        CtrState *contexto;
    public:
        Command(CtrState *ctx) : contexto(ctx) {}
        virtual TypeReturn execute() = 0;
        ~Command() = default;
};

//---------

class AuthentCommandExit : public Command<nullptr_t>{
    public:
        AuthentCommandExit(CtrState *ctx) : Command(ctx) {}
        nullptr_t execute();
};

class AuthentCommandLogin : public Command<PresentationInte*>{
    public:
        AuthentCommandLogin(CtrState *ctx) : Command(ctx) {}
        PresentationInte* execute();
};

class AuthentCommandMakeAccount : public Command<PresentationInte*>{
    public:
        AuthentCommandMakeAccount(CtrState *ctx) : Command(ctx) {}
        PresentationInte* execute();
};

class AuthenticationSer : public AuthenticationServiceInte{
    private:
        AuthentCommandExit cmdExit;
        AuthentCommandLogin cmdLogin;
        AuthentCommandMakeAccount cmdMakeAccount;
    public:
        AuthenticationSer(CtrState *ctx);
};

//---------

class AccountCommandLogOut : public Command<PresentationInte*>{
    public:
        AccountCommandLogOut(CtrState *ctx) : Command(ctx) {}
        PresentationInte* execute();
};

class AccountCommandRemoveAccount : public Command<PresentationInte*>{
    public:
        AccountCommandRemoveAccount(CtrState *ctx) : Command(ctx) {}
        PresentationInte* execute();
};

class AccountCommandChangeName : public Command<void>{
    public:
        AccountCommandChangeName(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class AccountCommandListWallets : public Command<array<Carteira, 5>>{
    public:
        AccountCommandListWallets(CtrState *ctx) : Command(ctx) {}
        array<Carteira, 5> execute();
};

class AccountCommandMakeWallet : public Command<void>{
    public:
        AccountCommandMakeWallet(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class AccountCommandRemoveWallet : public Command<void>{
    public:
        AccountCommandRemoveWallet(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class AccountCommandManageWallet : public Command<PresentationInte*>{
    public:
        AccountCommandManageWallet(CtrState *ctx) : Command(ctx) {}
        PresentationInte* execute();
};

class AccountSer : public AccountServiceInte{
    private:
        AccountCommandLogOut cmdLogOut;
        AccountCommandRemoveAccount cmdRemoveAccount;
        AccountCommandChangeName cmdChangeName;
        AccountCommandListWallets cmdListWallets;
        AccountCommandMakeWallet cmdMakeWallet;
        AccountCommandRemoveWallet cmdRemoveWallet;
        AccountCommandManageWallet cmdManageWallet;
    public:
        AccountSer(CtrState *ctx);
};

//---------------

class InvestmentCommandEditWallet : public Command<void>{
    public:
        InvestmentCommandEditWallet(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class InvestmentCommandListOrders : public Command<vector<Ordem>>{
    public:
        InvestmentCommandListOrders(CtrState *ctx) : Command(ctx) {}
        vector<Ordem> execute();
};

class InvestmentCommandMakeOrder : public Command<void>{
    public:
        InvestmentCommandMakeOrder(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class InvestmentCommandRemoveOrder : public Command<void>{
    public:
        InvestmentCommandRemoveOrder(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class InvestmentCommandCancelOrder : public Command<void>{
    public:
        InvestmentCommandCancelOrder(CtrState *ctx) : Command(ctx) {}
        void execute();
};

class InvestmentSer : public InvestmentServiceInte{
    private:
        InvestmentCommandEditWallet cmdEditWallet;
        InvestmentCommandListOrders cmdListOrders;
        InvestmentCommandMakeOrder cmdMakeOrder;
        InvestmentCommandRemoveOrder cmdRemoveOrder;
        InvestmentCommandCancelOrder cmdCancelOrder;
    public:
        InvestmentSer(CtrState *ctx);
};