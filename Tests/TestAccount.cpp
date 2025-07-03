#include "Source/Service/AccountSer.cpp"
#include "Tests/Test.hpp"

class TestMakeWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandMakeWallet->execute";
            typeTest = ValidArgument();
            in = "Cpf: 842.259.180-41 / Nome: Carteira Agresiva / TipoPerfil: Agressivo";
            expected = "void";

            // Cria as variáveis do teste
            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();
            Tabela resultSql;

            Ncpf cpf;
            Senha senha;
            Nome nomeUser;

            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nomeUser.setValor("Ze de Fulano");

            user->setNcpf(cpf);
            user->setSenha(senha);
            user->setNome(nomeUser);

            contexto->setUser(user);

            TipoPerfil perfil;
            Nome nome;
            perfil.setValor("Agressivo");
            nome.setValor("Carteira Agresiva");

            // Roda o teste

            try {
                ctrAccount.makeWallet(nome, perfil);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();
                
                // Limpa os Dados;
                sqlite3_exec(
                    DB::getInstance()->getDB(),
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\" AND NOME = Carteira Agresiva;",
                    nullptr, nullptr, nullptr
                );
                delete contexto;
                return ;
            };

            Carteira *carteira = contexto->getCarteira();
            
            string findWalletS = "SELECT NOME, CODIGO, PERFIL, CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() +
                        "\" AND NOME = \"" + nome.getValor() +"\"";
            const char *findWallet = findWalletS.c_str();

            bool excResult = sqlite3_exec(DB::getInstance()->getDB(), findWallet, callback, &resultSql, nullptr);
            
            if(resultSql[0]["NOME"] != nome.getValor()) result = ResultFail();
            else if(resultSql[0]["PERFIL"] != perfil.getValor()) result = ResultFail();
            else if(resultSql[0]["CPF"] != cpf.getValor()) result = ResultFail();
            else result = ResultPass();

            out = "Void";

            // Limpa os Dados;
            sqlite3_exec(
                DB::getInstance()->getDB(),
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                nullptr, nullptr, nullptr
            );
        }
};
