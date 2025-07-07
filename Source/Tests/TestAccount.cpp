#include "Service/AccountSer.cpp"
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

class TestListWalletEmpty : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Teste->AccountCommandListWallet (Sem Carteiras)";
            typeTest = ValidArgument();
            in = "void";
            expected = "vector<Carteira> (empty)";

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

            // Roda o teste
            vector<Carteira> a;
            try {
                a = ctrAccount.listWallets();
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();

                // Limpa os Dados;
                delete contexto;
                delete resultSql;
                return ;
            };
            
            // Verifica os dados;
            if(resultSql->size() != 0) {
                result = ResultFail();
                out = "vector<Carteira> (not empty)";
            } else {
                result = ResultPass();
                out = "vector<Carteira> (empty)";
            }

            // Limpa os Dados;
            delete contexto;
            delete resultSql;
        }
};



class TestChangeSenha : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Test->AccountCommandChangeSenha";
            typeTest = ValidArgument();
            in = "Senha: Ef1*gh";
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

            Senha novaSenha;
            novaSenha.setValor("Ef1#gh");

            db->exec(
                "INSERT INTO Contas (NOME, CPF, SENHA) VALUES (\"" + nomeUser.getValor() +
                "\", \"" + cpf.getValor() + "\", \"" + senha.getValor() +
                "\")",
                resultSql,
                "Erro ao inserir a conta de teste: "
            );

            // Roda o teste
            try {
                ctrAccount.changeSenha(novaSenha);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Contas WHERE CPF = \"" + cpf.getValor() + "\"",
                    resultSql,
                    "Erro ao limpar os dados do teste"
                );
                delete contexto;
                delete resultSql;
                return ;
            };
            
            result = ResultPass();
            out = "void, but incorret data.";

            db->exec(
                "SELECT SENHA FROM Contas WHERE CPF = \"" + cpf.getValor() + "\";",
                resultSql,
                "Erro ao procurar a nova senha: "
            );

            if(resultSql[0][0]["SENHA"] != novaSenha.getValor()) result = ResultFail();
            else out = "void";

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Contas WHERE CPF = \"" + cpf.getValor() + "\";",
                resultSql,
                "Erro ao limpar os dados do teste: "
            );
            delete contexto;
            delete resultSql;
        }
};



class TestChangeNome : public Test{
        public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Test->AccountCommandChangeNome";
            typeTest = ValidArgument();
            in = "Nome: Jose";
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

            Nome novoNome;
            novoNome.setValor("Jose");

            db->exec(
                "INSERT INTO Contas (NOME, CPF, SENHA) VALUES (\"" + nomeUser.getValor() +
                "\", \"" + cpf.getValor() + "\", \"" + senha.getValor() +
                "\")",
                resultSql,
                "Erro ao inserir a conta de teste: "
            );

            // Roda o teste
            try {
                ctrAccount.changeName(novoNome);
            } catch (runtime_error &x) {
                out = x.what();
                result = ResultFail();

                // Limpa os Dados;
                db->exec(
                    "DELETE FROM Contas WHERE CPF = \"" + cpf.getValor() + "\"",
                    resultSql,
                    "Erro ao limpar os dados do Teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            };
            
            result = ResultPass();
            out = "void, but incorret data.";

            db->exec(
                "SELECT NOME FROM Contas WHERE CPF = \"" + cpf.getValor() + "\";",
                resultSql,
                "Erro ao procurar a nova senha: "
            );

            if(resultSql[0][0]["NOME"] != novoNome.getValor()) result = ResultFail();
            else out = "void";

            // Limpa os Dados;
            db->exec(
                "DELETE FROM Contas WHERE CPF = \"" + cpf.getValor() + "\"",
                resultSql,
                "Erro ao limpar os dados do Teste: "
            );
            delete contexto;
            delete resultSql;
        }
};



class TestRemoveAccount : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Test->AccountCommandRemoveAccount";
            typeTest = ValidArgument();
            in = "void";
            expected = "PresentationInte*";

            // Configura variaveis do teste;
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

            db->exec(
                "INSERT INTO Contas (NOME, CPF, SENHA) VALUES (\"" + nomeUser.getValor() +
                "\", \"" + cpf.getValor() + "\", \"" + senha.getValor() +
                "\")",
                resultSql,
                "Erro ao inserir a conta de teste: "
            );

            // Roda o teste;
            PresentationInte* retorno;
            try{
                retorno = ctrAccount.removeAccount();
            } catch (runtime_error &x){
                out = x.what();
                result = ResultFail();
                
                //Limpa os dados
                db->exec(
                    "DELETE FROM Contas WHERE CPF = \"" + cpf.getValor() + "\"",
                    resultSql,
                    "Erro ao limpar os dados do Teste: "
                );
                delete contexto;
                delete resultSql;
                return ;
            }

            result = ResultPass();
            out = "PresentationInte*, but incorret data.";

            db->exec(
                "SELECT NOME FROM Contas WHERE CPF = \"" + cpf.getValor() + "\";",
                resultSql,
                "Erro ao verificar a deleção da conta do teste: "
            );

            if(
                resultSql->size() != 0 or
                contexto->getCarteira() != nullptr or
                contexto->getUser() != nullptr
            ) result = ResultFail();
            else out = "PresentationInte*";

            // Limpa os dados;
            delete contexto;
            delete resultSql;
        }
};



class TestLogOut : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Test->AccountCommandLogOut";
            typeTest = ValidArgument();
            in = "void";
            expected = "PresentationInte*";

            // Configura variaveis do teste;
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

            // Roda o teste;
            try{
                ctrAccount.logOut();
            } catch (runtime_error &x){
                out = x.what();
                result = ResultFail();

                // Limpa os dados do teste;
                delete contexto;
                return ;
            }

            result = ResultPass();
            out = "PresentationInte*, but incorret data.";

            if(
                contexto->getUser() != nullptr or
                contexto->getCarteira() != nullptr
            ) result = ResultFail();
            else out = "PresentationInte*";

            delete contexto;
        }
};

class TestRemoveWallet : public Test{
    public:
        void exec(){
            // Define os dados do Teste.
            nameTest = "Test->AccountCommandRemoveWallet";
            typeTest = ValidArgument();
            in = "Nome: Test";
            expected = "void";

            // Configura variaveis do teste;
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

            db->exec(
                "INSERT INTO Carteiras (NOME, CODIGO, PERFIL, CPF) VALUES (\"Test\", 00005, Agreseivo, \"842.259.180-41\")",
                resultSql,
                "Erro ao inserir dados de teste no DB: "
            );
            Nome nomeInput;
            nomeInput.setValor("Test");

            // Roda o teste;
            try{
                ctrAccount.removeWallet(nomeInput);
            } catch (runtime_error &x){
                out = x.what();
                result = ResultFail();

                // Limpa os dados do teste;
                db->exec("DELETE FROM Carteiras", resultSql, "Erro ao limpar dados do test: ");
                delete resultSql;
                delete contexto;
                return ;
            }

            // Valida os dados do Test.
            result = ResultPass();
            out = "void, but incorret data.";

            db->exec("SELCET * FROM Carteiras;", resultSql, "Erro ao procurar a carteira no DB para validar os dados: ");

            if(resultSql->size() > 0) result = ResultFail();
            else out = "void";

            // Limpa os dados do teste;
            db->exec("DELETE FROM Carteiras", resultSql, "Erro ao limpar dados do test: ");
            delete resultSql;
            delete contexto;
            return ;
        }
};
