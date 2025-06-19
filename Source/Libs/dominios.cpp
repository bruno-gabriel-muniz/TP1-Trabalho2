#include "dominios.hpp"

//  Domínio Código
//---------------------------------------------------------------------
// Implementação do método privado que verifica se o valor fornecido atende
// ao formato correto para a classe codigo
void Codigo::validar(const string &valor)
{
    // Verifica a quantidade de dígitos
    if (valor.length() != Q_DIGITOS)
    {
        throw invalid_argument("Argumento inválido! O código deve conter exatamente 5 caracteres.");
    }
    // Verifica se todos são dígitos numericos
    for (char d : valor)
    {
        if (!isdigit(d))
        {
            throw invalid_argument("Argumento inválido! O código deve conter apenas dígitos.");
        }
    }
}
//---------------------------------------------------------------------
// Implementação do método público que define e valida o valor do codigo
// Chama internamente o método validar() para garantir conformidade antes de atribuir o valor
void Codigo::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Codigo Negociação
//---------------------------------------------------------------------
// Implementação do método privado que verifica se o valor fornecido atende
// ao formato correto para a classe codigo de negociação
void CodigoNeg::validar(const string &valor)
{
    // Verifica a quantidade de dígitos
    if (valor.length() != Q_DIGITOS)
    {
        throw invalid_argument("Argumento inválido! O codigo de negociação deve conter exatamente 12 caracteres.");
    }
    // Verifica se todos os caracteres so alfanuméricos ou espacos em branco
    for (char d : valor)
    {
        if (!(isalnum(d) || isspace(d)))
        {
            throw invalid_argument("Argumento inválido! O codigo de negociação deve conter apenas caracteres "
                                   "alfanuméricos ou espacos brancos.");
        }
    }
}
//---------------------------------------------------------------------
// Implementação do método público que define e valida o valor do codigo de negociação
// Chama internamente o método validar() para garantir conformidade antes de atribuir o valor
void CodigoNeg::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio CPF
//---------------------------------------------------------------------
// Implementação do método privado que verifica se o valor fornecido esta
// conforme regras de formatacao e calculo dos dígitos verificadores.
void Ncpf::validar(const string &valor)
{
    // Verifica a quantidade de dígitos
    if (valor.length() != Q_DIGITOS)
    {
        throw invalid_argument("Argumento inválido! O CPF deve conter 14 caracteres no formato XXX.XXX.XXX-XX.");
    }

    // Verifica o formato XXX.XXX.XXX-XX
    for (size_t i = 0; i < valor.size(); ++i)
    {
        if (i == 3 || i == 7)
        {
            if (valor[i] != '.')
                throw invalid_argument("Argumento inválido! CPF fora do formato XXX.XXX.XXX-XX.");
        }
        else if (i == 11)
        {
            if (valor[i] != '-')
                throw invalid_argument("Argumento inválido! CPF fora do formato XXX.XXX.XXX-XX.");
        }
        else
        {
            if (!isdigit(valor[i]))
                throw invalid_argument("Argumento inválido! CPF fora do formato XXX.XXX.XXX-XX.");
        }
    }

    // Extrai apenas os numeros
    string numeros;
    for (char d : valor)
        if (isdigit(d))
        {
            numeros.push_back(d);
        }

    if (numeros.size() != 11)
    {
        throw invalid_argument("Argumento inválido! CPF deve conter exatamente 11 dígitos.");
    }

    // Verifica se todos os dígitos so iguais
    bool todosIguais = true;
    for (int i = 1; i < 11; ++i)
    {
        if (numeros[i] != numeros[0])
        {
            todosIguais = false;
            break;
        }
    }
    if (todosIguais)
    {
        throw invalid_argument("Argumento inválido! Todos os dígitos so iguais.");
    }

    // Calculo do primeiro dígito verificador
    int soma = 0;
    for (int i = 0; i < 9; i++)
    {
        soma += (numeros[i] - '0') * (10 - i);
    }
    int digito1 = (soma * 10) % 11;
    if (digito1 == 10)
        digito1 = 0;

    // Calculo do segundo dígito verificador
    soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma += (numeros[i] - '0') * (11 - i);
    }
    int digito2 = (soma * 10) % 11;
    if (digito2 == 10)
        digito2 = 0;

    // Verifica se os dígitos calculados batem com os fornecidos
    if ((digito1 != numeros[9] - '0') || (digito2 != numeros[10] - '0'))
    {
        throw invalid_argument("Argumento inválido! Os dígitos verificadores do CPF nao conferem.");
    }
}
//---------------------------------------------------------------------
// Método que define o valor cpf apos validar se esta dentro do formato e regras oficiais.
// Chama internamente o método `validar` para garantir que o valor passado seja um CPF valido antes de armazena-lo.
void Ncpf::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Data
//---------------------------------------------------------------------
// Verifica se um ano e bissexto
bool isBissexto(int ano)
{
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

// Valida se ano, m�s e dia representa uma data valida
void dataValida(int ano, int mes, int dia)
{
    // Verifica se o ano, m�s e dia estao dentro das faixas validas
    if (ano < 1 || mes < 1 || mes > 12 || dia < 1)
    {
        throw invalid_argument("Argumento inválido! Data fora da faixa.");
    }

    // Define a quantidade de dias segundo cada m�s
    int diasMes = 0;
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
    {
        diasMes = 31;
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
    {
        diasMes = 30;
    }
    if (mes == 2)
    {
        if (isBissexto(ano))
        {
            diasMes = 29;
        }
        else
        {
            diasMes = 28;
        }
    }

    // Valida se o dia informado esta dentro da faixa do m�s correspondente.
    if (dia > diasMes)
    {
        throw invalid_argument("Argumento inválido! Data fora da faixa.");
    }
}

// Implementação do método privado que verifica se o valor fornecido atende
// ao formato correto para data AAAAMMDD
void Data::validar(const string &valor)
{
    // Verifica a quantidade de dígitos
    if (valor.length() != Q_DIGITOS)
    {
        throw invalid_argument("Argumento inválido! Data deve conter exatamente 8 dígitos.");
    }

    // Verifica se todos so dígitos numericos
    for (char d : valor)
    {
        if (!isdigit(d))
        {
            throw invalid_argument("Argumento inválido! Data deve conter apenas dígitos.");
        }
    }

    // Extrai ano, m�s e dia a partir da string, assumindo o formato "AAAAMMDD"
    int ano = stoi(valor.substr(0, 4));
    int mes = stoi(valor.substr(4, 2));
    int dia = stoi(valor.substr(6, 2));
    dataValida(ano, mes, dia);
}
//---------------------------------------------------------------------
// Método que define o valor data apos validar se esta conforme o formato permitido
// Chama o método `validar` para garantir que a data fornecida esteja
// dentro do formato e das regras estabelecidas para o calendario.
void Data::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Nome
//---------------------------------------------------------------------
// Implementação de Método privado que valida o nome fornecido conforme
// as regras estabelecidas.
void Nome::validar(const string &valor)
{
    // Verifica se o comprimento e de no maximo 20 caracteres
    if (valor.length() > Q_CARATERES)
    {
        throw invalid_argument("Argumento inválido! Nome excede o limite de 20 caracteres.");
    }

    // Verifica se todos os caracteres so alfanuméricos ou espacos em branco
    // e garante que **nao ha dois espacos em branco consecutivos**.
    char anterior = '\0';
    for (char atual : valor)
    {
        if (!(isalnum(atual) || isspace(atual)))
        {
            throw invalid_argument("Argumento inválido! Nome com caractere nao permitido.");
        }
        if (isspace(atual) && isspace(anterior))
        {
            throw invalid_argument("Argumento inválido! Nome com dois espacos brancos consecutivos.");
        }
        anterior = atual;
    }
}
//---------------------------------------------------------------------
// Método que define o valor do nome apos validacao.
// Chama o método `validar()` para garantir que o valor esteja conforme as regras de formatacao.
void Nome::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Perfil   (Responsavel: Micaele 231021450)
//---------------------------------------------------------------------
// Implementação do método privado que valida o valor do perfil de investimento, considerando
// as opcoes validas: "Conservador", "Moderado" ou "Agressivo".
void TipoPerfil::validar(const string &valor)
{
    // Verifica se o valor passado e um dos tr�s perfis validos: "Conservador", "Moderado" ou "Agressivo"
    if (valor != "Conservador" && valor != "Moderado" && valor != "Agressivo")
    {
        throw invalid_argument("Argumento inválido! Opcoes permitidas: Conservador, Moderado ou Agressivo.");
    }
}
//---------------------------------------------------------------------
// Método que define o valor do perfil apos validacao.
// Chama o método `validar()` para garantir que o valor esteja dentro das opcoes permitidas.
void TipoPerfil::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Dinheiro
//---------------------------------------------------------------------
// Constantes de intervalo para valores monetarios validos
const float Dinheiro::MINIMO = 0.01f;
const float Dinheiro::MAXIMO = 1000000.00f;
//---------------------------------------------------------------------
// Implementação do método privado que valida o valor monetario fornecido.
void Dinheiro::validar(const string &valor)
{
    // Verifica se o valor esta no formato `#.###.###,##`, validado por expresso regular;
    regex formato_valido(R"(^(0,\d{2}|[1-9]\d{0,2}(\.\d{3})*,\d{2})$)");
    if (!regex_match(valor, formato_valido))
    {
        throw invalid_argument("Argumento inválido! Fora do formato #.###.###,##.");
    }

    // Extrai apenas a parte numerica da string. Remove os pontos e substitui a virgula por ponto para converso
    string valorNumerico = valor;
    valorNumerico.erase(remove(valorNumerico.begin(), valorNumerico.end(), '.'), valorNumerico.end());
    replace(valorNumerico.begin(), valorNumerico.end(), ',', '.');

    // Converte para float
    float numero = stof(valorNumerico);

    // Verifica intervalo permitido
    if (numero < MINIMO || numero > MAXIMO)
    {
        throw invalid_argument("Argumento inválido! Valor fora do intervalo permitido (0,01 a 1.000.000,00).");
    }
}
//---------------------------------------------------------------------
// Método que define o valor monetario apos validacao
// Chama o método `validar()` para verificar formato e intervalo antes de armazenar.
void Dinheiro::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Quantidade
//---------------------------------------------------------------------
// Implementação do método privado que valida o valor da quantidade fornecida
// no formato `#.###.###` e intervalo permitdo
void Quantidade::validar(const string &valor)
{
    // Regex para validar apenas numeros inteiros, sem casas decimais (formato #.###.###)
    regex formato_valido(R"(^[1-9]\d{0,2}(\.\d{3})*$)");
    if (!regex_match(valor, formato_valido))
    {
        throw invalid_argument("Argumento inválido! Fora do formato #.###.###.");
    }

    // Extrai apenas a parte numerica da string, removendo os pontos
    string numeroValor = valor;
    numeroValor.erase(remove(numeroValor.begin(), numeroValor.end(), '.'), numeroValor.end());

    // Converte para inteiro
    int numero = stoi(numeroValor);

    // Verifica intervalo permitido  (1 a 1.000.000)
    if (numero < MINIMO || numero > MAXIMO)
    {
        throw invalid_argument("Argumento inválido! Valor fora do intervalo permitido (1 e 1.000.000).");
    }
}
//---------------------------------------------------------------------
// Método que define o valor da quantidade apos validar apos validacao.
// Chama o método validar()` para verificar se o valor fornecido esta em conformidade
// com o formato e intervalo esperados. Apenas valores validos so armazenados.
void Quantidade::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------

//  Domínio Senha
//---------------------------------------------------------------------
// Implementação do método que valida a senha de acordo com critérios de segurança
void Senha::validar(const string &valor)
{
    // Verifica se a senha possui exatamente 6 caracteres
    if (valor.length() != Q_CARATERES)
    {
        throw invalid_argument("Argumento inválido! A senha deve conter exatamente 6 caracteres.");
    }

    // Flags para verificar os requisitos da senha
    bool tem_maiuscula = false;
    bool tem_minuscula = false;
    bool tem_digito = false;
    bool tem_especial = false;

    // Conjunto para garantir que nao haja caracteres duplicados
    set<char> caracteres;

    // Verifica se o caractere e alfanumerico ou um dos caracteres especiais
    for (char c : valor)
    {
        if (!(isalnum(c) || c == '#' || c == '$' || c == '%' || c == '&'))
        {
            throw invalid_argument(
                "Argumento inválido! A senha so pode conter letras, dígitos e os caracteres especiais: #, $, %, &.");
        }

        // Verifica se o caractere ja apareceu na senha
        if (caracteres.count(c) > 0)
        {
            throw invalid_argument("Argumento inválido! A senha nao pode conter caracteres repetidos.");
        }

        // Insere o caractere no conjunto
        caracteres.insert(c);

        // Verifica se e um dígito, letra maiuscula, letra minuscula ou caractere especial
        if (isdigit(c))
            tem_digito = true;
        else if (isupper(c))
            tem_maiuscula = true;
        else if (islower(c))
            tem_minuscula = true;
        else if (c == '#' || c == '$' || c == '%' || c == '&')
            tem_especial = true;
    }

    // Verifica se todos os requisitos de segurança são atendidos
    if (!(tem_maiuscula && tem_minuscula && tem_digito && tem_especial))
    {
        throw invalid_argument("Argumento inválido! A senha deve conter ao menos: 1 letra maiuscula, 1 letra "
                               "minuscula, 1 dígito e 1 dos caracteres especiais permitidos: #, $, %, &.");
    }
}
//---------------------------------------------------------------------
// Método que define o valor Senha apos validar
// Chama o método validar() para verificar se o valor fornecido  atende os critérios
// de segurança antes de atribuir o valor da senha.
void Senha::setValor(const string &valor)
{
    validar(valor);
    this->valor = valor;
}
//---------------------------------------------------------------------
