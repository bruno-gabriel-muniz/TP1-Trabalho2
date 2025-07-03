#include "Source/Service/AuthenticationSer.cpp"
#include "Tests/Test.hpp"

class TestMakeAccount : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandMakeAccount";
            typeTest = ValidArgument();
            in = "Cpf: 842.259.180-41 / Senha: B1g#ji / Nome: Ze de Fulano";
            expected = "void";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            // Roda o teste
            try{
                ctrAuthen.makeAccount(cpf, senha, nome);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();
                
                // Limpa os Dados;
                db->exec("DELETE FROM Contas WHERE CPF = \"842.259.180-41\";", resultSql, "Erro ao excluir a conta: ");
                delete contexto;
                return ;
            }

            // Verifica os dados;
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

            // Limpa os Dados;
            db->exec("DELETE FROM Contas WHERE CPF = \"842.259.180-41\";", resultSql, "Erro ao excluir a conta: ");
            delete contexto;
        }
};

class TestMakeAccountF : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandMakeAccountF";
            typeTest = InvalidArgument();
            in = "Cpf: 842.259.180-41 / Senha: B1g#ji / Nome: Ze de Fulano";
            expected = "O CPF já está sendo utilizado.";

            // Criando as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            // Configurando DB.
            string insertNewAccountS = "INSERT INTO Contas (CPF, SENHA, NOME) VALUES (\"" +
                                        cpf.getValor() + "\", \"" + senha.getValor() + "\", \"" +
                                        nome.getValor() +
                                        "\")";
            db->exec(insertNewAccountS, resultSql, "Erro ao inserir carteira para o teste: ");


            // Roda o teste
            try{
                ctrAuthen.makeAccount(cpf, senha, nome);
            } catch (runtime_error &x) {
                out = x.what();
                if(out == expected) result = ResultPass();
                else result = ResultFail();

                // Limpa os dados
                db->exec("DELETE FROM Contas WHERE CPF = \"842.259.180-41\";", resultSql, "Erro ao excluir a conta: ");
                delete contexto;
                return;
            }

            // Verificando os dados;
            result = ResultFail();
            out = "void";

            // Limpa os Dados;
            db->exec("DELETE FROM Contas WHERE CPF = \"842.259.180-41\";", resultSql, "Erro ao excluir a conta: ");
            delete contexto;
        }
};

class TestMakeLogin : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandLogin";
            typeTest = ValidArgument();
            in = "Cpf: 842.259.180-41 / Senha: B1g#ji";
            expected = "void";

            // Criando as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            
            // Insere a conta no DB.
            string insertNewAccountS = "INSERT INTO Contas (CPF, SENHA, NOME) VALUES (\""
                                    + cpf.getValor() + "\", \"" + senha.getValor() + "\", \"" + nome.getValor() + "\")";
            db->exec(insertNewAccountS, resultSql, "Erro ao inserir a conta para o teste: ");
            // Roda o teste
            try{
                ctrAuthen.login(cpf, senha);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();
                
                // Limpa os dados
                db->exec("DELETE FROM Contas WHERE CPF = \"842.259.180-41\";", resultSql, "Erro ao excluir a conta: ");
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

            // Limpa os Dados;
            db->exec("DELETE FROM Contas WHERE CPF = \"842.259.180-41\";", resultSql, "Erro ao excluir a conta: ");
            delete contexto;
        }
};

class TestMakeLoginF : public Test{
    public:
        void exec(){
            // Definindo os dados do teste.
            nameTest = "Teste->AuthentCommandLoginF";
            typeTest = InvalidArgument();
            in = "Cpf: 842.259.180-41 / Senha: B1g#ji";
            expected = "CPF não encontrado.";

            // Criando as variáveis do teste
            CtrState *contexto = new CtrState();
            AuthenticationSer ctrAuthen = AuthenticationSer(contexto);
            Ncpf cpf;
            Senha senha;
            Nome nome;
            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nome.setValor("Ze de Fulano");

            
            // Roda o teste
            try{
                ctrAuthen.login(cpf, senha);
            } catch (runtime_error &x) {
                out = x.what();
                if(out == expected) result = ResultPass();
                else result = ResultFail();
                
                // Limpa os dados
                delete contexto;
                return;
            };
            
            out = "void";
            result = ResultFail();

            delete contexto;
        }
};
