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