/**
 * @file InterfacesService.hpp
 * @brief Interfaces da camada de serviço do app.
 */

#include <array>
#include <memory>

#include "InterfacePresentation.hpp"
#include "Libs/entidades.hpp"

using namespace std;

class CtrState; // declaração antecipada

// interfaces / invokers

/**
 * @class AuthenticationServiceInte
 * @brief Interface de serviço para a área de autenticação do app.
 */
class AuthenticationServiceInte{
    private:
        CtrState *context;
    public:
        /**
         * @brief Efetua o login e chama a próxima UI, @ref AccountPre "AccountPre".
         * @param cpf Número de CPF do titular da conta.
         * @param senha Senha da conta.
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Proxima interface do app.
         */
        virtual PresentationInte* login(Ncpf cpf, Senha senha) = 0;
        /**
         * @brief Cria uma nova conta e chama a próxima UI, @ref AccountPre "AccountPre".
         * @param cpf Número de CPF do titular da nova conta.
         * @param senha Senha da nova conta.
         * @param nome Nome do titular ou o nome da conta.
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Proxima interface do app.
         */
        virtual PresentationInte* makeAccount(Ncpf cpf, Senha senha, Nome nome) = 0;
        ~AuthenticationServiceInte() = default;
};

/**
 * @class AccountServiceInte
 * @brief Interface de serviço para a área de gerenciamento da conta do app.
 */
class AccountServiceInte{
    private:
        CtrState *context;
    public:
        /**
         * @brief Desloga da conta atual e chama a próxima UI, @ref AuthenticationPre "AuthenticationPre".
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Proxima interface do app.
         */
        virtual PresentationInte* logOut() = 0;
        /**
         * @brief Remove a conta dos dados do app, e chama a próxima UI, @ref AuthenticationPre "AuthenticationPre".
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Proxima interface do app.
         */
        virtual PresentationInte* removeAccount() = 0;
        /**
         * @brief Altera o nome da conta.
         * @param nome Novo nome da conta.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void changeName(Nome nome) = 0;
        /**
         * @brief Altera a senha da conta.
         * @param senha Nova senha da conta.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void changeSenha(Senha senha) = 0;
        /**
         * @brief Lista as carteiras da conta ativa.
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Lista das carteira das contas.
         */
        virtual array<Carteira, 5> listWallets() = 0;
        /**
         * @brief Cria uma carteira para a conta ativa.
         * @param nome Nome de exibição da nova carteira.
         * @param perfil Tipo de investimento da nova carteira.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void makeWallet(Nome nome, TipoPerfil perfil) = 0;
        /**
         * @brief Remove uma carteira da conta ativa.
         * @param nome Nome da carteira que será excluida.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void removeWallet(Nome nome) = 0;
        /**
         * @brief Chama a próxima UI, @ref InvestmentPre "InvestmentPre".
         * @param nome Nome da carteira que será gerenciada.
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Proxima interface do app.
         */
        virtual PresentationInte* manageWallet(Nome nome) = 0;
        ~AccountServiceInte() = default;
};

/**
 * @class InvestmentServiceInte
 * @brief Interface de serviço para a área de investimento do app.
 */
class InvestmentServiceInte{
    private:
        CtrState *context;
    public:
        /**
         * @brief Edita a carteira ativa.
         * @param nome Novo nome, se for alterado. 
         * @param perfil Novo tipo de investimento, se for alterado.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void editWallet(Nome* nome = nullptr, TipoPerfil* perfil = nullptr) = 0;
        /**
         * @brief Lista as ordens da carteira ativa.
         * @throws std::runtime_error Caso ocorra falha na operação.
         * @return Lista das ordens da carteira.
         */
        virtual vector<Ordem> listOrders() = 0;
        /**
         * @brief Faz uma ordem para carteira ativa.
         * @param codNeg Código da ação que está sendo comprada.
         * @param quantidade Quantidade de ações compradas.
         * @param data Data da compra da ação.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void makeOrder(CodigoNeg codNeg, Quantidade quantidade, Data data) = 0;
        /**
         * @brief Remove uma ordem do histórico.
         * @param codNeg Código da negociação que será removida.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void removeOrder(CodigoNeg codNeg) = 0;
        /**
         * @brief Cancela e remove uma ordem dos dados do app.
         * @param codNeg Código da negociação que será cancelada.
         * @throws std::runtime_error Caso ocorra falha na operação.
         */
        virtual void cancelOrder(CodigoNeg codNeg) = 0;
        virtual ~InvestmentServiceInte() = default;
};
