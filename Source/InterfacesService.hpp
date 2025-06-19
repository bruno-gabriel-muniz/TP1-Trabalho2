#include <array>
#include <memory>

#include "InterfacePresentation.hpp"
#include "Libs/entidades.hpp"

using namespace std;

class CtrState; // declaração antecipada

// interfaces / invokers

class AuthenticationServiceInte{
    private:
        CtrState *context;
    public:
        virtual nullptr_t exit() = 0;
        virtual PresentationInte* login() = 0;
        virtual PresentationInte* makeAccount() = 0;
        ~AuthenticationServiceInte() = default;
};

class AccountServiceInte{
    private:
        CtrState *context;
    public:
        virtual PresentationInte* logOut() = 0;
        virtual PresentationInte* removeAccount() = 0;
        virtual void changeName() = 0;
        virtual array<Carteira, 5> listWallets() = 0;
        virtual void makeWallet(...) = 0;
        virtual void removeWallet(...) = 0;
        virtual PresentationInte* manageWallet() = 0;
        ~AccountServiceInte() = default;
};

class InvestmentServiceInte{
    private:
        CtrState *context;
    public:
        virtual void editWallet(...) = 0;
        virtual vector<Ordem> listOrders(...) = 0;
        virtual void makeOrder(...) = 0;
        virtual void removeOrder(...) = 0;
        virtual void cancelOrder(...) = 0;
        virtual ~InvestmentServiceInte() = default;
};
