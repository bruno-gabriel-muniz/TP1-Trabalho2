#include "Service/InvestmentSer.cpp"
#include "Tests/Test.hpp"

class TestMakeOrder : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->InvestmentCommandMakeOrder";
            typeTest = ValidArgument();
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

class TestRemoveOrder : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->InvestmentCommandRemoveOrder";
            typeTest = ValidArgument();
            in = "codNeg: 'SAPR11F     '";
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

            // Cria os dados da ordem
            CodigoNeg codNeg;
            codNeg.setValor("SAPR11F     ");
            Data data;
            data.setValor("20250110");
            Quantidade qtd;
            qtd.setValor("2");

            // Insere a Ordem no DB;
            string makeOrder =
                "INSERT INTO Ordens (CODIGO, \"CODIGO NEG\", DATA, PRECO, QUANTIDADE) VALUES (\"" +
                carteira->getCodigo().getValor() + "\", \"" + codNeg.getValor() + "\", \"" +
                data.getValor() + "\", \"2585\", \"" + qtd.getValor() +
                "\")";
            db->exec(makeOrder, resultSql, "Erro ao adicionar a ordem de teste no DB: ");

            makeOrder =
                "INSERT INTO Ordens (CODIGO, \"CODIGO NEG\", DATA, PRECO, QUANTIDADE) VALUES (\"" +
                carteira->getCodigo().getValor() +
                "\", \"HYPE3       \", \"20250102\", \"2585\", \"3\")";
            db->exec(makeOrder, resultSql, "Erro ao adicionar a ordem controle no DB: ");

            // Executa o teste;
            try{
                ctrInvestment.removeOrder(codNeg);
            } catch(runtime_error &x){
                out = x.what();
                result = ResultFail();
                
                //Limpa os dados;
                db->exec("DELETE FROM Ordens;", resultSql, "Erro ao limpar os dados do teste: ");
                delete contexto;
                delete resultSql;
                return ;
            }
            
            // Valida os dados;
            result = ResultPass();
            out = "void, but incorret data.";
            
            db->exec("SELECT * FROM Ordens;", resultSql, "Erro ao procurar as ordens no DB: ");

            if(
                resultSql->size() != 1 or
                resultSql[0][0]["CODIGO NEG"] != "HYPE3       "
            ) result = ResultFail();
            else out = "void";

            //Limpa os dados;
            db->exec("DELETE FROM Ordens;", resultSql, "Erro ao limpar os dados do teste: ");
            delete contexto;
            delete resultSql;
            return ;
        }
};

class TestListOrders : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->InvestmentCommandListOrders";
            typeTest = ValidArgument();
            in = "void";
            expected = "vector<Ordem>";

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

            // Configura os valores de teste no DB;

            string makeOrder =
                "INSERT INTO Ordens (CODIGO, \"CODIGO NEG\", DATA, PRECO, QUANTIDADE) VALUES (\"" +
                carteira->getCodigo().getValor() +
                "\", \"HYPE3       \", \"20250102\", \"2585\", \"3\")";
            db->exec(makeOrder, resultSql, "Erro ao adicionar a ordem controle no DB: ");

            makeOrder =
                "INSERT INTO Ordens (CODIGO, \"CODIGO NEG\", DATA, PRECO, QUANTIDADE) VALUES (\"" +
                carteira->getCodigo().getValor() +
                "\", \"HYPE3 TESTE \", \"20250102\", \"42585\", \"3\")";
            db->exec(makeOrder, resultSql, "Erro ao adicionar a ordem controle no DB: ");

            makeOrder =
                "INSERT INTO Ordens (CODIGO, \"CODIGO NEG\", DATA, PRECO, QUANTIDADE) VALUES (\"" +
                carteira->getCodigo().getValor() +
                "\", \"HYPE3 TESTE1\", \"20250105\", \"192585\", \"3\")";
            db->exec(makeOrder, resultSql, "Erro ao adicionar a ordem controle no DB: ");

            vector<Ordem> listOrdens;

            try{
                listOrdens = ctrInvestment.listOrders();
            } catch(runtime_error &x){
                out = x.what();
                result = ResultFail();

                // Limpa os dados;
                db->exec("DELETE FROM Ordens;", resultSql, "Erro ao limpar os dados: ");
                delete resultSql;
                delete contexto;
                return ;
            }
            
            // Verifica os dados;
            result = ResultPass();
            out = "vector<Ordem>, but incorret data";

            if(
                listOrdens[0].getDinheiro().getValor() != "25,85" or
                listOrdens[1].getCodigoNeg().getValor() != "HYPE3 TESTE " or
                listOrdens[2].getData().getValor() != "20250105" or
                listOrdens[2].getDinheiro().getValor() != "1.925,85"
            ) result = ResultFail();
            else out = "vector<Ordem>";
            
            // Limpa os dados;
            db->exec("DELETE FROM Ordens;", resultSql, "Erro ao limpar os dados: ");
            delete resultSql;
            delete contexto;
            return ;
        }
};

class TestEdidWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->InvestmentCommandEditWallet";
            typeTest = ValidArgument();
            in = "nome: Conta Emergencia / perfil: Conservador";
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

            nomeCarteira.setValor("Conta Rendimento");
            perfil.setValor("Moderado");
            codigo.setValor(gerarCodigo());

            user->setNcpf(cpf);
            user->setSenha(senha);
            user->setNome(nomeUser);

            carteira->setNome(nomeCarteira);
            carteira->setTipoPerfil(perfil);
            carteira->setCodigo(codigo);

            contexto->setUser(user);
            contexto->setCarteira(carteira);

            Nome novoNome;
            TipoPerfil novoPerfil;
            
            novoNome.setValor("Conta Emergencia");
            novoPerfil.setValor("Conservador");

            // Configura os dados no DB
            string insertWalletS = 
                "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"Conta Rendimento\", \"" +
                codigo.getValor() + "\", \"Moderado\", \"842.259.180-41\")";
            db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");

            // Executando o teste
            try{
                ctrInvestment.editWallet(&novoNome, &novoPerfil);
            } catch (runtime_error &x){
                out = x.what();
                result = ResultFail();

                // Limpa os dados;
                db->exec("DELETE FROM Carteiras;", resultSql, "Erro ao limpar os dados: ");
                delete resultSql;
                delete contexto;
                return ;
            }

            // Valida os dados;
            result = ResultPass();
            out = "void, but incorret data.";

            db->exec(
                "SELECT * FROM Carteiras WHERE NOME = \"Conta Emergencia\" AND PERFIL = \"Conservador\";",
                resultSql,
                "Erro ao validar as alterações no DB: "
            );

            if(
                contexto->getCarteira()->getNome().getValor() != "Conta Emergencia" or
                contexto->getCarteira()->getTipoPerfil().getValor() != "Conservador" or
                resultSql->size() != 1
            ) result = ResultFail();
            else out = "void";

            // Limpa os dados;
            db->exec("DELETE FROM Carteiras;", resultSql, "Erro ao limpar os dados: ");
            delete resultSql;
            delete contexto;
            return ;
        }
};
