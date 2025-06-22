#include "InterfacePresentation.hpp"

using namespace std;

class AuthenticationPre: public PresentationInte{
    public:
        nullptr_t exit();
        PresentationInte* showMainMenu();
        AuthenticationPre(CtrState *ctx);
};

class AccountPre: public PresentationInte{
    public:
        nullptr_t exit();
        PresentationInte* showEditAccount();
        PresentationInte* showWallets();
        AccountPre(CtrState *ctx);
};

class PersAccountPre: public PresentationInte{
    //Classe que indica que a AccountPre não precisa ser alterada.
};

class InvestmentPre: public PresentationInte{
    public:
        PresentationInte* back();
        void showEditPortfolio();
        void showManageOrders();
        InvestmentPre(CtrState *ctx);
};
