#include "Source/Service/AuthenticationSer.cpp"
#include "Tests/Test.hpp"

class TestMakeAccount : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandMakeAccount->execute";
            typeTest = ValidArgument();
            in = "Cpf: 842.259.180-41 | Senha: B1g#ji | Nome: Ze de Fulano";
            expected = "void";

            // Criando as variáveis do teste
            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            // Rodando o teste
            try{
                ctrAuthen.makeAccount(cpf, senha, nome);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();
                delete contexto;
                return;
            }

            // Verificando os dados;
            Conta *userContext = contexto->getUser();

            if(userContext->getNcpf().getValor() == cpf.getValor() and
                userContext->getSenha().getValor() == senha.getValor() and
                userContext->getNome().getValor() == nome.getValor())
            {
                out = "void";
                result = ResultPass();
            } else {
                out = "void, but value error.";
                result = ResultFail();
            };

            // Limpando os Dados;
            sqlite3_exec(
                DB::getInstance()->getDB(),
                "DELETE FROM Contas WHERE CPF = \"842.259.180-41\";",
                nullptr, nullptr, nullptr
            );
            delete contexto;
        }
};

class TestMakeAccountF : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandMakeAccountF->execute";
            typeTest = InvalidArgument();
            in = "Cpf: 842.259.180-41 | Senha: B1g#ji | Nome: Ze de Fulano";
            expected = "O CPF já está sendo utilizado.";

            // Criando as variáveis do teste
            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            // Configurando DB.
            string insertNewAccount_s = "INSERT INTO Contas (CPF, SENHA, NOME) VALUES (\"" +
                                        cpf.getValor() + "\", \"" + senha.getValor() + "\", \"" +
                                        nome.getValor() +
                                        "\")";
            const char *insertNewAccount = insertNewAccount_s.c_str();
            bool exc_result = sqlite3_exec(DB::getInstance()->getDB(), insertNewAccount, nullptr, 0, nullptr);

            // Rodando o teste
            try{
                ctrAuthen.makeAccount(cpf, senha, nome);
            } catch (runtime_error &x) {
                out = x.what();
                if(out == expected)
                    result = ResultPass();
                else
                    result = ResultFail();

                // Limpando os dados
                sqlite3_exec(
                    DB::getInstance()->getDB(),
                    "DELETE FROM Contas WHERE CPF = \"842.259.180-41\";",
                    nullptr, nullptr, nullptr
                );
                delete contexto;
                return;
            }

            // Verificando os dados;
            result = ResultFail();
            out = "void";

            // Limpando os Dados;
            sqlite3_exec(
                DB::getInstance()->getDB(),
                "DELETE FROM Contas WHERE CPF = \"842.259.180-41\";",
                nullptr, nullptr, nullptr
            );
            delete contexto;
        }
};

class TestMakeLogin : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandLogin->execute";
            typeTest = ValidArgument();
            in = "Cpf: 842.259.180-41 | Senha: B1g#ji";
            expected = "void";

            // Criando as variáveis do teste
            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            
            // Insere a conta no DB.
            string insertNewAccount_s = "INSERT INTO Contas (CPF, SENHA, NOME) VALUES (\""
                                    + cpf.getValor() + "\", \"" + senha.getValor() + "\", \"" + nome.getValor() + "\")";
            const char *insertNewAccount = insertNewAccount_s.c_str();
            bool exc_result = sqlite3_exec(DB::getInstance()->getDB(), insertNewAccount, nullptr, 0, nullptr);

            // Roda o teste
            try{
                ctrAuthen.login(cpf, senha);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();
                // Limpando os dados
                sqlite3_exec(
                    DB::getInstance()->getDB(),
                    "DELETE FROM Contas WHERE CPF = \"842.259.180-41\";",
                    nullptr, nullptr, nullptr
                );
                delete contexto;
                return;
            };
            
            // Verificando os dados;
            Conta *userContext = contexto->getUser();

            if(userContext->getNcpf().getValor() == cpf.getValor() and
                userContext->getSenha().getValor() == senha.getValor() and
                userContext->getNome().getValor() == nome.getValor())
            {
                out = "void";
                result = ResultPass();
            } else {
                out = "void, but value error.";
                result = ResultFail();
            };

            // Limpando os Dados;
            sqlite3_exec(
                DB::getInstance()->getDB(),
                "DELETE FROM Contas WHERE CPF = \"842.259.180-41\";",
                nullptr, nullptr, nullptr
            );
            delete contexto;
        }
};
