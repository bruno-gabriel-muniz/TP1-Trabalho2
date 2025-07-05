#include "Source/Service/InvestmentSer.cpp"
#include "Tests/Test.hpp"

class TestMakeOrder : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->InvestmentCommandMakeOrder";
            typeTest = InvalidArgument();
            in = "codNeg: 'SAPR11F     ' / Data: 20250110 / Quantidade: 2";
            expected = "void";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            // Organiza as variáveis do teste;
            CtrState *contexto = new CtrState();
            InvestmentSer ctrInvestment = InvestmentSer(contexto);

            Conta *user = new Conta();
            Carteira *carteira = new Carteira();

            Ncpf cpf;
            Senha senha;
            Nome nomeUser;

            Nome nomeCarteira;
            TipoPerfil perfil;
            Codigo codigo;

            cpf.setValor("842.259.180-41");
            senha.setValor("B1g#ji");
            nomeUser.setValor("Ze de Fulano");

            nomeCarteira.setValor("Conservadora");
            perfil.setValor("Conservador");
            codigo.setValor(gerarCodigo());

            user->setNcpf(cpf);
            user->setSenha(senha);
            user->setNome(nomeUser);

            carteira->setNome(nomeCarteira);
            carteira->setTipoPerfil(perfil);
            carteira->setCodigo(codigo);

            contexto->setUser(user);
            contexto->setCarteira(carteira);

            // Cria os Inputs
            CodigoNeg codNeg;
            codNeg.setValor("SAPR11F     ");
            Data data;
            data.setValor("20250110");
            Quantidade qtd;
            qtd.setValor("2");

            // Executa o teste
            try{
                ctrInvestment.makeOrder(codNeg, qtd, data);
            } catch (runtime_error &x){
                out = x.what();
                result = ResultFail();

                // Limpa os dados;
                delete contexto;
                delete resultSql;
                return ;
            }

            // Valida os dados
            string findOrdem = "SELECT * FROM Ordens;";
            db->exec(findOrdem, resultSql, "Erro ao procurar a carteira do Teste: ");

            result = ResultPass();
            out = "void, but incorret data.";

            if(
                resultSql->size() != 1 or
                resultSql[0][0]["PRECO"] != "2585" or
                resultSql[0][0]["QUANTIDADE"] != qtd.getValor() or
                resultSql[0][0]["CODIGO"] != codigo.getValor()
            ) result = ResultFail();
            else out = "void";

            //Limpa os dados;
            db->exec("DELETE FROM Ordens;", resultSql, "Erro ao limpar os dados do teste: ");
            delete contexto;
            delete resultSql;
            return ;
        };
};
