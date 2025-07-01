/**
 * @file InterfacesService.hpp
 * @brief Interfaces da camada de serviço do aplicativo, utilizadas pelo módulo de apresentação: @ref Presentation.hpp "Presentation".
 */

#pragma once

#include <array>
#include <memory>

#include "Source/CtrState.cpp"
#include "Source/Libs/entidades.hpp"

using namespace std;

class CtrState; // declaração antecipada

// Interfaces / Invokers

/**
 * @class ServiceInte
 * @brief Classe base para as interfaces de serviço.
 */
class ServiceInte {
protected:
    CtrState *context;
};

/**
 * @class AuthenticationServiceInte
 * @brief Interface de serviço para a área de autenticação do aplicativo.
 */
class AuthenticationServiceInte : public ServiceInte {
public:
    /**
     * @brief Efetua o login e retorna a próxima UI, @ref AccountPre "AccountPre".
     * @param cpf Número de CPF do titular da conta.
     * @param senha Senha da conta.
     * @throws std::runtime_error Caso ocorra falha na operação.
     * @return Próxima interface do aplicativo.
     */
    virtual PresentationInte* login(Ncpf cpf, Senha senha) = 0;

    /**
     * @brief Cria uma nova conta e retorna a próxima UI, @ref AccountPre "AccountPre".
     * @param cpf Número de CPF do titular da nova conta.
     * @param senha Senha da nova conta.
     * @param nome Nome do titular ou da conta.
     * @throws std::runtime_error Caso ocorra falha na operação.
     * @return Próxima interface do aplicativo.
     */
    virtual PresentationInte* makeAccount(Ncpf cpf, Senha senha, Nome nome) = 0;

    ~AuthenticationServiceInte() = default;
};

/**
 * @class AccountServiceInte
 * @brief Interface de serviço para a área de gerenciamento de conta do aplicativo.
 */
class AccountServiceInte : public ServiceInte {
public:
    /**
     * @brief Realiza logout da conta atual e retorna a próxima UI, @ref AuthenticationPre "AuthenticationPre".
     * @throws std::runtime_error Caso ocorra falha na operação.
     * @return Próxima interface do aplicativo.
     */
    virtual PresentationInte* logOut() = 0;

    /**
     * @brief Remove a conta dos dados do aplicativo e retorna a próxima UI, @ref AuthenticationPre "AuthenticationPre".
     * @throws std::runtime_error Caso ocorra falha na operação.
     * @return Próxima interface do aplicativo.
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
     * @return Lista das carteiras da conta.
     */
    virtual vector<Carteira> listWallets() = 0;

    /**
     * @brief Cria uma nova carteira para a conta ativa.
     * @param nome Nome de exibição da nova carteira.
     * @param perfil Tipo de investimento da nova carteira.
     * @throws std::runtime_error Caso ocorra falha na operação.
     */
    virtual void makeWallet(Nome nome, TipoPerfil perfil) = 0;

    /**
     * @brief Remove uma carteira da conta ativa.
     * @param nome Nome da carteira que será excluída.
     * @throws std::runtime_error Caso ocorra falha na operação.
     */
    virtual void removeWallet(Nome nome) = 0;

    /**
     * @brief Acessa a próxima UI, @ref InvestmentPre "InvestmentPre", para gerenciar uma carteira.
     * @param nome Nome da carteira a ser gerenciada.
     * @throws std::runtime_error Caso ocorra falha na operação.
     * @return Próxima interface do aplicativo.
     */
    virtual PresentationInte* manageWallet(Nome nome) = 0;

    ~AccountServiceInte() = default;
};

/**
 * @class InvestmentServiceInte
 * @brief Interface de serviço para a área de investimentos do aplicativo.
 */
class InvestmentServiceInte : public ServiceInte {
public:
    /**
     * @brief Edita a carteira ativa.
     * @param nome Novo nome da carteira, se for alterado.
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
     * @brief Cria uma nova ordem para a carteira ativa.
     * @param codNeg Código da ação comprada.
     * @param quantidade Quantidade de ações compradas.
     * @param data Data da compra.
     * @throws std::runtime_error Caso ocorra falha na operação.
     */
    virtual void makeOrder(CodigoNeg codNeg, Quantidade quantidade, Data data) = 0;

    /**
     * @brief Remove uma ordem do histórico.
     * @param codNeg Código da negociação a ser removida.
     * @throws std::runtime_error Caso ocorra falha na operação.
     */
    virtual void removeOrder(CodigoNeg codNeg) = 0;

    /**
     * @brief Cancela e remove uma ordem dos dados do aplicativo.
     * @param codNeg Código da negociação a ser cancelada.
     * @throws std::runtime_error Caso ocorra falha na operação.
     */
    virtual void cancelOrder(CodigoNeg codNeg) = 0;

    virtual ~InvestmentServiceInte() = default;
};
