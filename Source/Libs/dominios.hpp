/**
 * @file dominios.hpp
 * @brief Biblioteca de dominios do sistema de investimentos financeiros.
 *
 * Este arquivo define os tipos fundamentais utilizados como base para
 * validação e representação de valores primitivos com regras de negócio
 * específicas no sistema de investimentos.
 *
 * Cada domínio encapsula um tipo básico (como string) com regras
 * de validação próprias, garantindo a integridade e a consistência dos dados
 * desde sua criação até o uso nas entidades do sistema.
 *
 * @details
 * Os domínios foram projetados para validar automaticamente os valores
 * atribuidos a eles, evitando inconsistências e entradas invalidas no sistema.
 * Exemplos incluem CPF, nome, senha, codigo de ativos, datas, quantidades,
 * valores monetários e tipos de perfil.
 *
 * Estes tipos são amplamente utilizados nas entidades do sistema, como
 * @ref Conta, @ref Carteira e @ref Ordem, promovendo reutilização e seguranca
 * de dados nas operacoes financeiras.
 *
 * @see entidades.hpp
 */
//---------------------------------------------------------------------
#ifndef DOMINIOS_HPP_INCLUDED
#define DOMINIOS_HPP_INCLUDED

//---------------------------------------------------------------------
#include <iomanip>
#include <iostream>
#include <regex>
#include <set>
#include <stdexcept>
#include <string>

using namespace std;

///---------------------------------------------------------------------
//  Domínio Código     (Responsável: Micaele 231021450)
/**
 * @class Codigo
 * @brief Classe que representa uma sequência numerica única de identificação, com exatamente 5 digitos numericos.
 *
 * Esta classe e utilizada para representar um valor único (código) no sistema de investimentos,
 * podendo estar associado a Carteiras de investimento ou Ordens de compra/venda. Ela garante que os valores
 * dos códigos obedecam a um formato estrito: exatamente 5 caracteres, todos digitos de 0 a 9.
 *
 * A classe e usada para armazenar e validar um valor (código) representado como uma string, que deve
 * obedecer a regras específicas de formato, garantindo que o valor interno sempre esteja em conformidade
 * com as regras estabelecidas.
 *
 * Regras de validação:
 * - O código deve conter exatamente 5 caracteres.
 * - Todos os caracteres devem ser digitos numericos.
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que atribui um novo valor ao código, após validação.
 * - `getValor`: Método público que retorna o valor atual armazenado.
 *
 * O codigo inválido resultara em uma exceção `std::invalid_argument`.
 */
class Codigo
{
  private:
    /**
     * @brief Quantidade fixa de digitos exigidos para o codigo.
     */
    static const int Q_DIGITOS = 5;

    /**
     * @brief Armazena o valor do codigo após validação.
     */
    string valor;

    /**
     * @brief Método privado que valida se o valor fornecido atende ao formato correto para a classe Codigo.
     *
     * Este método verifica se a string fornecida tem exatamente 5 caracteres
     * e se todos os caracteres são digitos numericos (0 a 9).
     * Lanca uma exceção se o valor for inválido
     *
     * @param valor Valor de codigo a ser validado.
     * @throw std::invalid_argument Se o valor nao tiver 5 digitos ou contiver caracteres nao numericos.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que define o valor do codigo após realizar validação.
     *
     * Utiliza o método interno `validar` para garantir que o valor esteja correto
     * antes de armazena-lo.
     *
     * @param valor Valor de codigo a ser atribuido.
     * @throw std::invalid_argument Se o valor for inválido.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o valor atual do codigo.
     *
     * @return string contendo Valor do codigo armazenado.
     */
    string getValor() const;
};

//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método getValor.
 *
 * Retorna o valor atualmente armazenado no objeto.
 *
 * @return Valor do codigo como string.
 */
inline string Codigo::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
//  Domínio Codigo Negociação     (Responsável: Maria 231021431)
/**
 * @class CodigoNeg
 * @brief Classe que representa uma sequência única de identificação, com exatamente 12 caracteres alfanuméricos ou
 * espaços.
 *
 * Esta classe e utilizada para representar um valor único (código de negociação) no sistema de investimentos,
 * podendo estar associado a Ordens de compra/venda. Ela garante que os valores dos códigos de negociação obedecam a um
 * formato estrito: exatamente 12 caracteres, podendo conter letras, numeros e espaços.
 *
 * A classe e usada para armazenar e validar um valor (código de negociação) representado como uma string, que
 * deve obedecer a regras específicas de formato, garantindo que o valor interno sempre esteja em conformidade
 * com as regras estabelecidas.
 *
 * Regras de validação:
 * - O código deve conter exatamente 12 caracteres.
 * - Os caracteres devem ser alfanuméricos (letras e/ou numeros) ou espaços em branco.
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que atribui um novo valor ao código de negociação, após validação.
 * - `getValor`: Método público que retorna o valor atual armazenado.
 *
 * Códigos inválidos resultam em uma exceção `std::invalid_argument`.
 */
class CodigoNeg
{
  private:
    /**
     * @brief Quantidade fixa de caracteres exigidos para o código de negociação.
     */
    static const int Q_DIGITOS = 12;

    /**
     * @brief Armazena o valor do código de negociação após validação.
     */
    string valor;

    /**
     * @brief Método privado responsável por validar se o valor fornecido atende o formato correto para o código de
     * negociação.
     *
     * Verifica se a string tem exatamente 12 caracteres e se todos são alfanuméricos ou espaços em branco.
     * Lanca uma exceção se o valor for inválido
     *
     * @param valor Valor de código de negociação a ser atribuido.
     * @throws std::invalid_argument Se o valor nao tiver 12 caracteres ou contiver caracteres inválidos.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que atribui um valor ao código de negociação, após validação.
     *
     * Utiliza o método `validar()` para verificar se o valor atende aos criterios definidos.
     *
     * @param valor Valor de código de negociação a ser atribuido.
     * @throws std::invalid_argument Se o valor nao for valido.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o valor atual do código de negociação.
     *
     * @return string contendo o código de negociação armazenado.
     */
    string getValor() const;
};

//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que recupera o valor do código de negociação.
 *
 * @return string com o valor atual do código de negociação.
 */
inline string CodigoNeg::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
//  Domínio CPF   (Responsável: Karina 231006140)
/**
 * @class Ncpf
 * @brief Classe que representa uma sequência única de identificação, com exatamente 14 caracteres no formato
 * XXX.XXX.XXX-XX.
 *
 * Esta classe e utilizada para representar um CPF (Cadastro de Pessoa Fisica) no sistema de investimentos,
 * conforme as regras de formatação estabelecidas pela Receita Federal do Brasil. O CPF pode estar associado, por
 * exemplo, a contas de usuario.
 *
 * O valor deve seguir rigorosamente o formato padrao: três blocos de três digitos separados por pontos,
 * seguidos por um bloco de dois digitos separado por hifen.
 *
 * A classe `Ncpf` e responsável por armazenar e validar um numero de CPF, garantindo que o valor interno esteja em
 * conformidade com o formato e que os digitos verificadores sejam válidos conforme regras oficiais.
 *
 * Regras de validação:
 * - Deve conter exatamente 14 caracteres no formato XXX.XXX.XXX-XX.
 * - Apenas caracteres numericos, pontos e hifens são permitidos nas posicoes corretas.
 * - Os digitos verificadores (os dois últimos) devem ser válidos de acordo com o algoritmo oficial do CPF.
 * - CPFs com todos os digitos iguais são inválidos (ex: "111.111.111-11").
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que atribui um novo valor ao CPF, após validação.
 * - `getValor`: Método público que retorna o valor atual do CPF armazenado.
 *
 * Lanca `std::invalid_argument` em caso de formato incorreto ou CPF inválido.
 */
class Ncpf
{
  private:
    /**
     * @brief Quantidade fixa de caracteres exigidos para um CPF formatado (incluindo pontos e hifen).
     */
    static const int Q_DIGITOS = 14;

    /**
     * @brief Armazena o valor do CPF após validação.
     */
    string valor;

    /**
     * @brief Método privado responsável por verificar se o valor fornecido atende o formato correto do CPF.
     *
     * Verifica se a string possui exatamente 14 caracteres no formato XXX.XXX.XXX-XX; se o formato contem
     * pontos e hifen nas posicoes corretas; se contem 11 digitos numericos válidos; se possui digitos verificadores
     * corretos; e rejeita CPFs com todos os digitos iguais. Lanca excecoes se:
     * - O tamanho for diferente de 14 caracteres;
     * - O formato for incorreto;
     * - Todos os digitos forem iguais;
     * - Os digitos verificadores nao forem válidos.
     *
     * @param valor String contendo o CPF a ser validado.
     * @throws std::invalid_argument Se o CPF estiver em formato inválido ou for matematicamente incorreto.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que atribui um CPF ao objeto após validar seu conteudo.
     *
     * Chama internamente o método `validar()` para garantir a conformidade do valor
     * com o formato e regras do CPF.
     *
     * @param valor CPF no formato XXX.XXX.XXX-XX.
     * @throws std::invalid_argument Se o CPF for inválido.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o CPF armazenado.
     *
     * @return string com o CPF armazenado no formato XXX.XXX.XXX-XX.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna o valor do CPF.
 *
 * @return string CPF armazenado, no formato XXX.XXX.XXX-XX.
 */
inline string Ncpf::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
//  Domínio Data   (Responsável: Bruno 241022460)
/**
 * @class Data
 * @brief Classe que representa uma abstração de tempo por meio de uma sequência de 8 digitos numericos no formato
 * AAAAMMDD.
 *
 * Esta classe e utilizada para representar uma data relevante para operacoes no sistema de investimentos,
 * correspondendo ao calendario gregoriano,e composta por ano, mes e dia, conforme as regras de formatação
 * estabelecidas. Ela e usada para registrar eventos como: data de transacoes (compra/venda), vencimentos de aplicacoes,
 * agendamentos futuros, entre outros.
 *
 * A classe `Data` e responsável por armazenar uma data em formato numerico (string com 8 digitos) e garantir que
 * essa data seja valida de acordo com as regras do calendario gregoriano. A data e representada no formato
 * "AAAAMMDD", onde:
 * - AAAA: ano (quatro digitos)
 * - MM: mes (01 a 12)
 * - DD: dia (dependendo do mes e se o ano e bissexto)
 *
 * Regras de validação:
 * - Verificação se a string possui exatamente 8 caracteres numericos.
 * - Validação do intervalo valido para ano, mes e dia.
 * - Validação do numero de dias permitido para o mes especifico.
 * - Verificação de ano bissexto em fevereiro.
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que define o valor da data após validar.
 * - `getValor`: Método público que retorna a data armazenada como string.
 *
 * Em caso de valor inválido, lanca `std::invalid_argument`.
 */
class Data
{
  private:
    /**
     * @brief Quantidade fixa de caracteres exigidos para o formato AAAAMMDD.
     */
    static const int Q_DIGITOS = 8;

    /**
     * @brief Armazena a data como string no formato AAAAMMDD.
     */
    string valor;

    /**
     * @brief Método privado responsável por validar a data fornecida.
     *
     * Realiza as seguintes validacoes:
     * - Verifica se a string contem exatamente 8 caracteres numericos.
     * - Extrai ano, mes e dia da string e valida se estao dentro das faixas permitidas.
     * - Verifica se o numero de dias e compativel com o mes e se o ano e bissexto, quando aplicavel.
     *
     * @param valor String representando a data no formato AAAAMMDD.
     * @throws std::invalid_argument Se a data estiver fora do formato ou for invalida.
     */
    void validar(const string &);

  public:
    /**
     *@brief Método público que define o valor da data, validando antes de armazenar.
     *
     * Utiliza o método `validar()` para garantir que a data esteja dentro dos criterios exigidos.
     * Armazena o valor apenas se a validação for bem-sucedida.
     *
     * @param valor String com a data no formato AAAAMMDD.
     * @throws std::invalid_argument Se o valor nao representar uma data valida.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna a data armazenada no formato AAAAMMDD.
     *
     * @return string representando a data.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna o valor data.
 *
 * @return string data armazenada, no formato AAAAMMDD
 */
inline string Data::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
// Domínio Nome   (Responsável: Jorge 241004686)
/**
 * @class Nome
 * @brief Classe que representa a identificação textual de uma pessoa, objeto ou entidade.
 * Pode ser composta por um ou mais componentes, com ate 20 caracteres alfanuméricos e espaços.
 *
 * Esta classe e utilizada para representar nomes de usuários ou clientes no sistema de investimentos,
 * responsaveis por transacoes ou beneficiarios. Ela garante que o nome informado siga um padrao estabelecido
 * que assegura legibilidade e integridade nos registros.
 *
 * A classe `Nome` e responsável por armazenar uma sequência de caracteres alfanuméricos (e espaços simples),
 * com um limite de ate 20 caracteres. O nome pode conter letras, numeros e espaços, desde que obedeca as
 * restricoes de formatação.
 *
 * Regras de validação:
 * - O nome deve conter no maximo 20 caracteres.
 * - So são permitidos caracteres alfanuméricos (letras e digitos) e espaços.
 * - Nao são permitidos dois espaços consecutivos.
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que define o valor do nome após validar.
 * - `getValor`: Método público que retorna o nome armazenado como string.
 *
 * Em caso de valor inválido, lanca `std::invalid_argument`.
 */
class Nome
{
  private:
    /**
     * @brief Quantidade maxima de caracteres permitida em um nome.
     */
    static const int Q_CARATERES = 20;

    /**
     * @brief Armazena o valor do nome validado.
     */
    string valor;

    /**
     * @brief Método privado responsável por verificar se o nome fornecido esta de acordo com as regras da aplicação.
     *
     * Regras de validação:
     * - Deve conter no maximo 20 caracteres;
     * - Apenas caracteres alfanuméricos e espaços são permitidos;
     * - Nao pode conter dois espaços consecutivos.
     *
     * @param valor Nome a ser validado.
     * @throws std::invalid_argument Se o nome for inválido.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que define o valor do nome após validação.
     *
     * Utiliza o método `validar()` para garantir que o nome esteja dentro dos criterios exigidos.
     * Armazena o valor apenas se a validação for bem-sucedida.
     *
     * @param valor Nome a ser definido.
     * @throws std::invalid_argument Se o nome nao atender aos criterios de validação.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o valor atual do nome.
     *
     * @return std::string Valor do nome armazenado.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna o valor do nome.
 *
 * @return std::string Nome armazenado, com ate 20 caracteres.
 */
inline string Nome::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
// Domínio Perfil   (Responsável: Micaele 231021450)
/**
 * @class TipoPerfil
 * @brief Classe que representa o tipo de investidor de um usuario.
 *
 * Esta classe e utilizada no sistema de investimentos para indicar o perfil do investidor de
 * um usuario, levando em conta sua disposição para correr riscos, objetivos financeiros e tempo que
 * pretende deixar o dinheiro investido. Ela permite que recomendacoes e decisoes financeiras sejam
 * personalizadas conforme o grau de tolerancia a riscos e preferencias pessoais.
 *
 * O perfil do investidor pode ser classificado em uma das seguintes categorias:
 * - "Conservador"
 * - "Moderado"
 * - "Agressivo"
 *
 * A classe `TipoPerfil` e responsável por armazenar e validar o valor do perfil atribuido ao investidor,
 * garantindo que ele esteja entre as opcoes validas predefinidas pelo sistema.
 *
 * Regras de validação:
 * - O valor deve ser exatamente uma das três strings: "Conservador", "Moderado" ou "Agressivo".
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que define o perfil após validar.
 * - `getValor`: Método público que retorna o perfil atualmente armazenado.
 *
 * Em caso de valor inválido, lanca `std::invalid_argument`.
 */
class TipoPerfil
{
  private:
    /**
     * @brief Armazena o valor do perfil de investimento validado.
     */
    string valor;

    /**
     * @brief Método privado responsável por validar se o valor fornecido corresponde a um perfil permitido.
     *
     * Regras de validação:
     * - Deve ser exatamente "Conservador", "Moderado" ou "Agressivo".
     *
     * @param valor String contendo o perfil a ser validado.
     * @throws std::invalid_argument Se o valor nao corresponder a um perfil valido.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que define o valor do perfil após validação.
     *
     * Utiliza o método `validar()` para assegurar que o valor esta dentro das opcoes permitidas.
     * O valor e armazenado somente se a validação for bem-sucedida.
     *
     * @param valor String contendo o perfil a ser atribuido.
     * @throws std::invalid_argument Se o valor for inválido.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o perfil armazenado.
     *
     * @return std::string Valor do perfil de investimento atual.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna o valor do perfil de investimento.
 *
 * @return std::string Valor atual do perfil ("Conservador", "Moderado" ou "Agressivo").
 */
inline string TipoPerfil::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
// Domínio Dinheiro   (Responsável: Karina 231006140)
/**
 * @class Dinheiro
 * @brief Classe que representa um valor monetário ou recurso financeiro aplicado, resgatado e movimentado
 * pelos usuários, em formato textual.
 *
 * Esta classe e utilizada no sistema de investimentos para armazenar valores que o investidor aplica
 * em produtos financeiros, como acoes, titulos, fundos ou poupanca, representados no formato brasileiro
 * com separadores de milhar e virgula como separador decimal.
 * Ela garante que os valores informados estejam no formato correto e dentro do intervalo permitido
 * para operacoes financeiras no sistema.
 *
 * O valor deve estar no seguinte formato: `#.###.###,##`, contendo:
 * - Separadores de milhar com pontos (`.`)
 * - Duas casas decimais separadas por virgula (`,`), obrigatoriamente
 *
 * A classe `Dinheiro` e responsável por armazenar uma string que representa um valor monetário
 * valido, realizando a validação do formato e convertendo internamente para numero real para verificar
 * se esta dentro dos limites estabelecidos.
 *
 * Regras de validação:
 * - O valor deve estar no formato: `#.###.###,##`
 * - Deve estar no intervalo entre 0,01 e 1.000.000,00 inclusive
 * - Aceita ate 6 digitos antes da virgula e 2 após
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que define o valor monetário após validação.
 * - `getValor`: Método público que retorna o valor monetário armazenado como string.
 *
 * Em caso de valor inválido, lanca `std::invalid_argument`.
 */
class Dinheiro
{
  private:
    /**
     * @brief Valor minimo permitido (inclusive): R$ 0,01.
     */
    static const float MINIMO;

    /**
     * @brief Valor maximo permitido (inclusive): R$ 1.000.000,00.
     */
    static const float MAXIMO;

    /**
     * @brief Armazena o valor monetário validado no formato `#.###.###,##`.
     */
    string valor;

    /**
     * @brief Método privado responsável por validar o formato e intervalo do valor monetário.
     *
     * Regras de validação:
     * - O valor deve obedecer ao formato `#.###.###,##`;
     * - Deve conter apenas digitos, pontos como separador de milhar e virgula como separador decimal;
     * - O valor numerico (após a conversão) deve estar no intervalo [0,01, 1.000.000,00].
     *
     * @param valor String representando um valor monetário a ser validado.
     * @throws std::invalid_argument Se o formato ou valor numerico estiver fora das regras.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que define o valor monetário após validação.
     *
     * Utiliza o método `validar()` para garantir que o valor esteja corretamente formatado
     * e dentro do intervalo permitido. O valor e armazenado apenas se a validação for bem-sucedida.
     *
     * @param valor String com o valor a ser atribuido, no formato `#.###.###,##`.
     * @throws std::invalid_argument Se o valor for inválido.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o valor monetário armazenado.
     *
     * @return std::string Valor no formato `#.###.###,##`.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna o valor monetário.
 *
 * @return std::string Valor armazenado no formato `#.###.###,##`.
 */
inline string Dinheiro::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
// Domínio Quantidade   (Responsável: Bruno 241022460)
/**
 * @class Quantidade
 * @brief Classe que representa o numero inteiro  de unidades de um ativo financeiro, adquiridas,
 * utilizadas ou mantidas por um investidor em transacoes financeiras.
 *
 * Esta classe e utilizada no sistema de investimentos para representar quantidades inteiras de ativos ou unidades
 * movimentadas por usuários, como acoes compradas ou cotas de fundos. A quantidade deve estar em um formato legivel,
 * com separador de milhar, e respeitar o intervalo permitido.
 *
 * O valor e fornecido como uma string formatada com pontos como separadores de milhar, por exemplo:
 * - "1.000"
 * - "10.000"
 * - "999.999"
 *
 * A classe `Quantidade` e responsável por armazenar essa string, garantindo que esteja corretamente formatada
 * e que o numero representado esteja dentro do intervalo permitido.
 *
 * Regras de validação:
 * - O valor deve estar no formato: `#.###.###` (apenas digitos com separadores de milhar).
 * - Deve representar um numero inteiro entre 1 e 1.000.000 (inclusive).
 * - Nao são permitidas casas decimais ou simbolos fora do padrao numerico.
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que define a quantidade após validação.
 * - `getValor`: Método público que retorna a quantidade armazenada como string.
 *
 * Em caso de valor inválido, lanca `std::invalid_argument`.
 */
class Quantidade
{
  private:
    /**
     * @brief Valor minimo permitido: 1.
     */
    static const int MINIMO = 1;

    /**
     * @brief Valor maximo permitido: 1.000.000.
     */
    static const int MAXIMO = 1000000;

    /**
     * @brief Armazena a quantidade validada no formato `#.###.###`.
     */
    string valor;

    /**
     * @brief Método privado responsável por validar o formato e intervalo da quantidade.
     *
     * Regras de validação:
     * - Deve obedecer ao formato `#.###.###`, com pontos como separadores de milhar;
     * - Deve conter apenas digitos e pontos;
     * - O numero convertido deve estar no intervalo entre 1 e 1.000.000.
     *
     * @param valor String representando a quantidade a ser validada.
     * @throws std::invalid_argument Se o valor estiver em formato inválido ou fora do intervalo.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que define o valor da quantidade após validação.
     *
     * Utiliza o método `validar()` para garantir que a quantidade esteja no formato correto e no intervalo permitido.
     * O valor e armazenado somente se a validação for bem-sucedida.
     *
     * @param valor String com a quantidade a ser definida.
     * @throws std::invalid_argument Se o valor for inválido.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna a quantidade armazenada.
     *
     * @return std::string Valor atual da quantidade no formato `#.###.###`.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna a quantidade armazenada.
 *
 * @return std::string Quantidade no formato `#.###.###`.
 */
inline string Quantidade::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------
// Domínio Senha   (Responsável: Jorge 241004686)
/**
 * @class Senha
 * @brief Classe que representa um conjunto de caracteres usado para autenticar a identidade de um usuario no sistema de
 * investimentos.
 *
 * A classe `Senha` e utilizada para armazenar e validar uma senha segura composta exatamente por 6 caracteres.
 * O objetivo e garantir a seguranca de autenticação, assegurando que a senha atenda aos requisitos minimos
 * de complexidade definidos pelo sistema.
 *
 * Regras de validação:
 * - A senha deve conter exatamente 6 caracteres.
 * - Deve incluir pelo menos:
 *    - 1 letra maiuscula
 *    - 1 letra minuscula
 *    - 1 digito numerico
 *    - 1 caractere especial permitido: `#`, `$`, `%`, `&`
 * - Todos os caracteres devem ser distintos (sem repetição).
 * - Apenas caracteres alfanuméricos e os especiais acima são permitidos.
 *
 * Métodos disponíveis:
 * - `setValor`: Método público que define a senha após validação.
 * - `getValor`: Método público que retorna a senha armazenada como string.
 *
 * Em caso de valor inválido, lanca `std::invalid_argument`.
 */
class Senha
{
  private:
    /**
     * @brief Quantidade exata de caracteres exigida na senha.
     */
    static const int Q_CARATERES = 6;

    /**
     * @brief Armazena o valor validado da senha.
     */
    string valor;

    /**
     * @brief Método privado que valida os criterios de seguranca da senha.
     *
     * Regras de validação:
     * - A senha deve conter exatamente 6 caracteres;
     * - Deve incluir pelo menos:
     *    - 1 letra maiuscula
     *    - 1 letra minuscula
     *    - 1 digito numerico
     *    - 1 caractere especial permitido: `#`, `$`, `%`, `&`
     * - Nao deve conter caracteres repetidos;
     * - Apenas os caracteres alfanuméricos e os especiais permitidos: `#`, `$`, `%`, `&`.
     *
     * @param valor String com a senha a ser validada.
     * @throws std::invalid_argument Se a senha violar qualquer uma das regras.
     */
    void validar(const string &);

  public:
    /**
     * @brief Método público que define o valor da senha após validação.
     *
     * Chama o método `validar()` para garantir que a senha esta em conformidade
     * com os criterios de seguranca. Armazena a senha apenas se a validação for bem-sucedida.
     *
     * @param valor String contendo a senha a ser definida.
     * @throws std::invalid_argument Se a senha for invalida.
     */
    void setValor(const string &);

    /**
     * @brief Método público que retorna o valor da senha armazenada.
     *
     * @return std::string Senha atualmente armazenada.
     */
    string getValor() const;
};
//---------------------------------------------------------------------
/**
 * @brief Implementação inline do método que retorna o valor da senha.
 *
 * @return std::string Senha armazenada.
 */
inline string Senha::getValor() const
{
    return valor;
}

///---------------------------------------------------------------------

#endif // DOMINIOS_HPP_INCLUDED
