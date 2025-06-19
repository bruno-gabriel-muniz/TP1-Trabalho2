/**
 * @file entidades.hpp
 * @brief Biblioteca de entidades do sistema de investimentos financeiros.
 *
 * Este arquivo contem a definição das entidades principais utilizadas
 * na modelagem do sistema, que representam os objetos de negócio como
 * Conta, Carteira e Ordem.
 *
 * As entidades encapsulam domínios especificos que garantem a integridade
 * dos dados através de regras de validação rigorosas. São responsáveis por
 * organizar e manter os dados estruturados no sistema, atuando como elo entre
 * a camada de domínio e as funcionalidades da aplicacao.
 *
 * @details
 * Cada entidade é formada por atributos privados representados por domínios,
 * e métodos públicos de acesso (getters e setters). As validacoes são garantidas
 * pela definição de cada domínio, promovendo seguranca e padronizacao.
 *
 * Entidades disponíveis:
 * - @ref Conta
 * - @ref Carteira
 * - @ref Ordem
 *
 * @see dominios.hpp
 */
//---------------------------------------------------------------------
#ifndef ENTIDADES_HPP_INCLUDED
#define ENTIDADES_HPP_INCLUDED

//---------------------------------------------------------------------
#include "dominios.hpp"

using namespace std;

///---------------------------------------------------------------------
// Entidade: Conta   (Responsável: Maria 231021431)
/**
 * @class Conta
 * @brief Classe que representa um conjunto de dados que identifica um usuário no sistema de investimentos financeiros.
 *
 * A classe "Conta" é utilizada para armazenar as informações essenciais de um usuário
 * autenticado no sistema, permitindo seu acesso, personalizacao e controle de permissões
 * protegidas por credenciais.
 * Cada conta esta associada a um CPF único, um nome e uma senha segura.
 *
 * Esta entidade é fundamental para a gestao de acessos e identificação dos usuários
 * no sistema de investimentos. Ela utiliza os domínios previamente definidos para garantir
 * que os valores atribuidos a seus atributos obedecam as regras de negócio.
 *
 * Atributos:
 * - `cpf`: Número do CPF do usuário, encapsulado pelo domínio `Ncpf`.
 * - `nome`: Nome completo do usuário, encapsulado pelo domínio `Nome`.
 * - `senha`: Senha de acesso do usuário, encapsulada pelo domínio `Senha`.
 *
 * Métodos públicos:
 * - `setNcpf(Ncpf)`: Define o CPF do usuário apos validação.
 * - `getNcpf()`: Retorna o CPF armazenado.
 * - `setNome(Nome)`: Define o nome do usuário apos validação.
 * - `getNome()`: Retorna o nome armazenado.
 * - `setSenha(Senha)`: Define a senha do usuário apos validação.
 * - `getSenha()`: Retorna a senha armazenada.
 */
class Conta
{
  private:
    /**
     * @brief Objeto do domínio `Ncpf` representando o CPF do usuário.
     */
    Ncpf cpf;

    /**
     * @brief Objeto do domínio `Nome` representando o nome do usuário.
     */
    Nome nome;

    /**
     * @brief Objeto do domínio `Senha` representando a senha do usuário.
     */
    Senha senha;

  public:
    /**
     * @brief Método público que define o CPF da conta.
     * @param cpf Objeto `Ncpf` contendo o CPF a ser atribuido.
     */
    void setNcpf(Ncpf);

    /**
     * @brief Método público que retorna o CPF armazenado na conta.
     * @return Objeto `Ncpf` com o CPF do usuário.
     */
    Ncpf getNcpf();

    /**
     * @brief Método público que define o nome do titular da conta.
     * @param nome Objeto `Nome` contendo o nome a ser atribuido.
     */
    void setNome(Nome);

    /**
     * @brief Método público que retorna o nome do titular da conta.
     * @return Objeto `Nome` com o nome do usuário.
     */
    Nome getNome();

    /**
     * @brief Método público que define a senha da conta.
     * @param senha Objeto `Senha` contendo a senha a ser atribuida.
     */
    void setSenha(Senha);

    /**
     * @brief Método público que retorna a senha armazenada na conta.
     * @return Objeto `Senha` com a senha do usuário.
     */
    Senha getSenha();
};
//---------------------------------------------------------------------

// Implementações inline dos métodos da classe Conta
//---------------------------------------------------------------------
/**
 * @brief Atribui um objeto `Ncpf` ao atributo `cpf`.
 * @param cpf Objeto do domínio `Ncpf`.
 */
inline void Conta::setNcpf(Ncpf cpf)
{
    this->cpf = cpf;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o CPF da conta.
 * @return Objeto `Ncpf`.
 */
inline Ncpf Conta::getNcpf()
{
    return cpf;
}

//---------------------------------------------------------------------
/**
 * @brief Atribui um objeto `Nome` ao atributo `nome`.
 * @param nome Objeto do domínio `Nome`.
 */
inline void Conta::setNome(Nome nome)
{
    this->nome = nome;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o nome da conta.
 * @return Objeto `Nome`.
 */
inline Nome Conta::getNome()
{
    return nome;
}

//---------------------------------------------------------------------
/**
 * @brief Atribui um objeto `Senha` ao atributo `senha`.
 * @param senha Objeto do domínio `Senha`.
 */
inline void Conta::setSenha(Senha senha)
{
    this->senha = senha;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna a senha da conta.
 * @return Objeto `Senha`.
 */
inline Senha Conta::getSenha()
{
    return senha;
}

///---------------------------------------------------------------------
// Entidade: Carteira   (Responsável: Bruno 241022460)
/**
 * @class Carteira
 * @brief Classe que representa a estrutura ou composição dos diferentes ativos de investimentos (como ações,
 * títulos públicos, fundos, imoveis, etc.) pertencentes a um investidor no sistema.
 *
 * A classe `Carteira` encapsula os dados relacionados a uma carteira de investimentos,
 * sendo ela uma instância que agrupa produtos ou aplicações financeiras sob um perfil
 * de investidor especifico.
 *
 * Esta entidade e essencial para controlar, organizar, acompanhar e gerenciar aplicações das carteiras criadas
 * pelos usuários, conforme seu perfil de risco e objetivos financeiros. Permite identificar sua designacao,
 * código e o tipo de perfil ao qual se relaciona.
 *
 * Atributos:
 * - `código`: Código identificador único da carteira (domínio `Código`).
 * - `nome`: Nome ou designacao da carteira (domínio `Nome`).
 * - `perfil`: Tipo de perfil do investidor associado (domínio `TipoPerfil`).
 *
 * Métodos públicos:
 * - `setCodigo(Codigo)`: Define o código da carteira.
 * - `getCodigo()`: Retorna o código armazenado.
 * - `setNome(Nome)`: Define o nome da carteira.
 * - `getNome()`: Retorna o nome armazenado.
 * - `setTipoPerfil(TipoPerfil)`: Define o tipo de perfil associado.
 * - `getTipoPerfil()`: Retorna o tipo de perfil associado.
 */
class Carteira
{
  private:
    /**
     * @brief Objeto do domínio `Codigo` representando o código da carteira.
     */
    Codigo codigo;

    /**
     * @brief Objeto do domínio `Nome` representando o nome da carteira.
     */
    Nome nome;

    /**
     * @brief Objeto do domínio `TipoPerfil` representando o perfil de investidor da carteira.
     */
    TipoPerfil perfil;

  public:
    /**
     * @brief Método público que define o codigo da carteira.
     * @param código Objeto `Codigo` a ser atribuido.
     */
    void setCodigo(Codigo);

    /**
     * @brief Método público que retorna o codigo da carteira.
     * @return Objeto `Codigo` com o valor atribuido.
     */
    Codigo getCodigo();

    /**
     * @brief Método público que define o nome da carteira.
     * @param nome Objeto `Nome` a ser atribuido.
     */
    void setNome(Nome);

    /**
     * @brief Método público que retorna o nome da carteira.
     * @return Objeto `Nome` com o valor atribuido.
     */
    Nome getNome();

    /**
     * @brief Método público que define o tipo de perfil do investidor associado a carteira.
     * @param perfil Objeto `TipoPerfil` a ser atribuido.
     */
    void setTipoPerfil(TipoPerfil);

    /**
     * @brief Método público que retorna o tipo de perfil associado a carteira.
     * @return Objeto `TipoPerfil` com o valor atribuido.
     */
    TipoPerfil getTipoPerfil();
};
//---------------------------------------------------------------------

// Implementações inline dos métodos da classe Carteira
//---------------------------------------------------------------------
/**
 * @brief Atribui um objeto `Codigo` ao atributo `codigo`.
 * @param codigo Objeto do domínio `Codigo`.
 */
inline void Carteira::setCodigo(Codigo codigo)
{
    this->codigo = codigo;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o codigo da carteira.
 * @return Objeto `Codigo`.
 */
inline Codigo Carteira::getCodigo()
{
    return codigo;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o codigo da carteira.
 * @return Objeto `Codigo`.
 */
inline void Carteira::setNome(Nome nome)
{
    this->nome = nome;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o nome da carteira.
 * @return Objeto `Nome`.
 */
inline Nome Carteira::getNome()
{
    return nome;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o nome da carteira.
 * @return Objeto `Nome`.
 */
inline void Carteira::setTipoPerfil(TipoPerfil perfil)
{
    this->perfil = perfil;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o nome da carteira.
 * @return Objeto `Nome`.
 */
inline TipoPerfil Carteira::getTipoPerfil()
{
    return perfil;
}

///---------------------------------------------------------------------
// Entidade: Ordem   (Responsável: Karina 231006140)
/**
 * @class Ordem
 * @brief Classe que representa uma instrução formal enviada por um investidor (ou sistema automatizado)
 * para comprar ou vender ativos financeiros (como ações, fundos, títulos ou criptomoedas)
 * na plataforma de negociacao.
 *
 * A classe `Ordem` armazena os dados essenciais para registrar uma ordem realizada por um usuário,
 * como o código da ordem, o código do ativo negociado, a data, o valor financeiro e a quantidade.
 *
 * Esta entidade e fundamental para o controle de transacoes no sistema, garantindo rastreabilidade
 * e integridade nas operacoes.
 *
 * Atributos:
 * - `codigo`: Codigo identificador único da ordem (domínio `Codigo`).
 * - `codigoNeg`: Codigo do ativo negociado (domínio `CodigoNeg`).
 * - `data`: Data da realizacao da ordem (domínio `Data`).
 * - `dinheiro`: Valor financeiro da ordem (domínio `Dinheiro`).
 * - `quantidade`: Quantidade de ativos envolvidos (domínio `Quantidade`).
 *
 * Métodos públicos:
 * - `setCodigo(Codigo)`: Define o codigo da ordem.
 * - `getCodigo()`: Retorna o codigo da ordem.
 * - `setCodigoNeg(CodigoNeg)`: Define o codigo do ativo negociado.
 * - `getCodigoNeg()`: Retorna o codigo do ativo negociado.
 * - `setData(Data)`: Define a data da ordem.
 * - `getData()`: Retorna a data da ordem.
 * - `setDinheiro(Dinheiro)`: Define o valor da ordem.
 * - `getDinheiro()`: Retorna o valor da ordem.
 * - `setQuantidade(Quantidade)`: Define a quantidade de ativos.
 * - `getQuantidade()`: Retorna a quantidade de ativos.
 */
class Ordem
{
  private:
    /**
     * @brief Objeto do domínio `Codigo` representando o codigo da ordem.
     */
    Codigo codigo;

    /**
     * @brief Objeto do domínio `CodigoNeg` representando o codigo do ativo negociado.
     */
    CodigoNeg codigoNeg;

    /**
     * @brief Objeto do domínio `Data` representando a data da ordem.
     */
    Data data;

    /**
     * @brief Objeto do domínio `Dinheiro` representando o valor financeiro da ordem.
     */
    Dinheiro dinheiro;

    /**
     * @brief Objeto do domínio `Quantidade` representando a quantidade de ativos.
     */
    Quantidade quantidade;

  public:
    /**
     * @brief Método público que define o codigo da ordem.
     * @param codigo Objeto `Codigo` a ser atribuido.
     */
    void setCodigo(Codigo);

    /**
     * @brief Método público que retorna o codigo da ordem.
     * @return Objeto `Codigo`.
     */
    Codigo getCodigo();

    /**
     * @brief Método público que define o codigo do ativo negociado.
     * @param codigoNeg Objeto `CodigoNeg` a ser atribuido.
     */
    void setCodigoNeg(CodigoNeg);

    /**
     * @brief Método público que retorna o codigo do ativo negociado.
     * @return Objeto `CodigoNeg`.
     */
    CodigoNeg getCodigoNeg();

    /**
     * @brief Método público que define a data da ordem.
     * @param data Objeto `Data` a ser atribuido.
     */
    void setData(Data);

    /**
     * @brief Método público que retorna a data da ordem.
     * @return Objeto `Data`.
     */
    Data getData();

    /**
     * @brief Método público que define o valor financeiro da ordem.
     * @param dinheiro Objeto `Dinheiro` a ser atribuido.
     */
    void setDinheiro(Dinheiro);

    /**
     * @brief Método público que retorna o valor financeiro da ordem.
     * @return Objeto `Dinheiro`.
     */
    Dinheiro getDinheiro();

    /**
     * @brief Método público que define a quantidade de ativos negociados.
     * @param quantidade Objeto `Quantidade` a ser atribuido.
     */
    void setQuantidade(Quantidade);

    /**
     * @brief Método público que retorna a quantidade de ativos negociados.
     * @return Objeto `Quantidade`.
     */
    Quantidade getQuantidade();
};
//---------------------------------------------------------------------

// Implementações inline dos métodos da classe Ordem
//---------------------------------------------------------------------
/**
 * @brief Define o codigo da ordem.
 * @param codigo Objeto do domínio Codigo a ser atribuido.
 */
inline void Ordem::setCodigo(Codigo codigo)
{
    this->codigo = codigo;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o codigo da ordem.
 * @return Objeto do domínio Codigo.
 */
inline Codigo Ordem::getCodigo()
{
    return codigo;
}

//---------------------------------------------------------------------
/**
 * @brief Define o codigo do ativo negociado.
 * @param codigoNeg Objeto do domínio CodigoNeg a ser atribuido.
 */
inline void Ordem::setCodigoNeg(CodigoNeg codigoNeg)
{
    this->codigoNeg = codigoNeg;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o codigo do ativo negociado.
 * @return Objeto do domínio CodigoNeg.
 */
inline CodigoNeg Ordem::getCodigoNeg()
{
    return codigoNeg;
}

//---------------------------------------------------------------------
/**
 * @brief Define a data da ordem.
 * @param data Objeto do domínio Data a ser atribuido.
 */
inline void Ordem::setData(Data data)
{
    this->data = data;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna a data da ordem.
 * @return Objeto do domínio Data.
 */
inline Data Ordem::getData()
{
    return data;
}

//---------------------------------------------------------------------
/**
 * @brief Define o valor financeiro da ordem.
 * @param dinheiro Objeto do domínio Dinheiro a ser atribuido.
 */
inline void Ordem::setDinheiro(Dinheiro dinheiro)
{
    this->dinheiro = dinheiro;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna o valor financeiro da ordem.
 * @return Objeto do domínio Dinheiro.
 */
inline Dinheiro Ordem::getDinheiro()
{
    return dinheiro;
}

//---------------------------------------------------------------------
/**
 * @brief Define a quantidade de ativos da ordem.
 * @param quantidade Objeto do domínio Quantidade a ser atribuido.
 */
inline void Ordem::setQuantidade(Quantidade quantidade)
{
    this->quantidade = quantidade;
}

//---------------------------------------------------------------------
/**
 * @brief Retorna a quantidade de ativos da ordem.
 * @return Objeto do domínio Quantidade.
 */
inline Quantidade Ordem::getQuantidade()
{
    return quantidade;
}

///---------------------------------------------------------------------

#endif // ENTIDADES_HPP_INCLUDED
