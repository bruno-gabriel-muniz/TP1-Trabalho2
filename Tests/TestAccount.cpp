#include "Source/Service/AccountSer.cpp"
#include "Tests/Test.hpp"

class TestMakeWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandMakeWallet";
            typeTest = ValidArgument();
            in = "Cpf: 842.259.180-41 / Nome: Carteira Agresiva / TipoPerfil: Agressivo";
            expected = "void";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();

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
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\" AND NOME = \"Carteira Agresiva\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };

            Carteira *carteira = contexto->getCarteira();
            
            string findWalletS = "SELECT NOME, CODIGO, PERFIL, CPF FROM Carteiras WHERE CPF = \"" + cpf.getValor() +
                        "\" AND NOME = \"" + nome.getValor() +"\"";
            db->exec(findWalletS, resultSql, "Erro ao procurar a carteira criada no teste.");
            
            if(resultSql[0][0]["NOME"] != nome.getValor()) result = ResultFail();
            else if(resultSql[0][0]["PERFIL"] != perfil.getValor()) result = ResultFail();
            else if(resultSql[0][0]["CPF"] != cpf.getValor()) result = ResultFail();
            else result = ResultPass();

            out = "Void";

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\" AND NOME = \"Carteira Agresiva\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};

class TestMakeWalletFDuplicate : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandMakeWallet (Duplicate)";
            typeTest = InvalidArgument();
            in = "Cpf: 842.259.180-41 / Nome: Carteira Agresiva / TipoPerfil: Agressivo";
            expected = "Erro: outra carteira já possui esse nome.";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();

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

            string codigoF = gerarCodigo();

            string insertWalletS = 
                "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"Carteira Agresiva\", \"" +
                codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
            db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");


            // Roda o teste
            try {
                ctrAccount.makeWallet(nome, perfil);
            } catch (runtime_error &x) {
                out = x.what();
                if(out == expected) result = ResultPass();
                else result = ResultFail();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\" AND NOME = \"Carteira Agresiva\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };

            out = "void";
            result = ResultFail();

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\" AND NOME = \"Carteira Agresiva\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};

class TestMakeWalletFLimitWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandMakeWallet (LimitWallet)";
            typeTest = InvalidArgument();
            in = "Cpf: 842.259.180-41 / Nome: Carteira Agresiva / TipoPerfil: Agressivo";
            expected = "Erro: limite de Carteiras atingido.";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();

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

            for(int i = 0; i < 5; i++){
                string codigoF = gerarCodigo();
                string insertWalletS = 
                    "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"" + to_string(i) + "\", \"" +
                    codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
                db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");
            }

            // Roda o teste
            try {
                ctrAccount.makeWallet(nome, perfil);
            } catch (runtime_error &x) {
                out = x.what();
                if(out == expected) result = ResultPass();
                else result = ResultFail();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };

            out = "void";
            result = ResultFail();

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};



class TestManageWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandManageWallet";
            typeTest = ValidArgument();
            in = "Nome: Carteira Agresiva";
            expected = "*InvestmentPre";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();

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

            // Configura os dados no DB
            string codigoF = gerarCodigo();
            string insertWalletS = 
                "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"Carteira Agresiva\", \"" +
                codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
            db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");

            for(int i = 0; i < 4; i++){
                string codigoF = gerarCodigo();
                string insertWalletS = 
                    "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"" + to_string(i) + "\", \"" +
                    codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
                db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");
            }

            // Roda o teste
            try {
                PresentationInte *a = ctrAccount.manageWallet(nome);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };
            
            out = "*InvestmentPre, but incorret data";
            
            // Verfica os dados da carteira
            Carteira *carteiraResult = contexto->getCarteira();

            if(carteiraResult->getNome().getValor() != nome.getValor()) result = ResultFail();
            else if (carteiraResult->getTipoPerfil().getValor() != perfil.getValor()) result = ResultFail();
            else {
                result = ResultPass();
                out = "*InvestmentPre";
            }

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};

class TestManageWalletNotFound : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandManageWallet (Not Found)";
            typeTest = InvalidArgument();
            in = "Nome: Carteira Conserv";
            expected = "Erro: carteira não encontrada.";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();

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
            nome.setValor("Carteira Conserv");

            // Configura os dados no DB
            string codigoF = gerarCodigo();
            string insertWalletS = 
                "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"Carteira Agresiva\", \"" +
                codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
            db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");

            for(int i = 0; i < 4; i++){
                string codigoF = gerarCodigo();
                string insertWalletS = 
                    "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"" + to_string(i) + "\", \"" +
                    codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
                db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");
            }

            // Roda o teste
            try {
                PresentationInte *a = ctrAccount.manageWallet(nome);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultPass();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };
            
            out = "*InvestmentPre";
            result = ResultFail();

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};



class TestListWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandListWallet";
            typeTest = ValidArgument();
            in = "void";
            expected = "vector<Carteira>";

            // Cria as variáveis do teste
            DB *db = DB::getInstance(); // DB sqlite
            Tabela *resultSql = new Tabela(); // Result query sql

            CtrState *contexto = new CtrState();
            AccountSer ctrAccount = AccountSer(contexto);
            Conta *user = new Conta();

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
            
            // Configura os dados no DB
            string codigoF = gerarCodigo();
            string insertWalletS = 
                "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"Carteira Agresiva\", \"" +
                codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
            db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");

            for(int i = 0; i < 4; i++){
                string codigoF = gerarCodigo();
                string insertWalletS = 
                    "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"" + to_string(i) + "\", \"" +
                    codigoF + "\", \"Agressivo\", \"842.259.180-41\")";
                db->exec(insertWalletS, resultSql, "Erro ao inserir a carteira: ");
            }

            // Roda o teste
            vector<Carteira> a;
            try {
                a = ctrAccount.listWallets();
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };
            
            out = "vector<Carteira>";
            result = ResultPass();
            
            // Verfica os dados das carteiras

            Carteira carteiraResult = a[0];
            if(
                carteiraResult.getNome().getValor() != nome.getValor() or
                carteiraResult.getTipoPerfil().getValor() != perfil.getValor()
            ) {
                result = ResultFail();
                out = "vector<Carteira>, but incorret data";
                
                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                    resultSql,
                    "Erro ao limpar os dados do teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            }

            for(int i = 1; i < 5; i++){
                carteiraResult = a[i];

                if (carteiraResult.getTipoPerfil().getValor() != perfil.getValor()){
                    result = ResultFail();
                    out = "vector<Carteira>, but incorret data";
                    break;
                }
            }
            // Limpa os Dados;
            db->exec(
                "DELETE FROM Carteiras WHERE CPF = \"842.259.180-41\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};
