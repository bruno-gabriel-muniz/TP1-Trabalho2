# include <fstream>
# include <unordered_set>

# include "DB.cpp"

int main(){
    // Configura os dados do DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Abre o arquivo;
    ifstream Arquivo("DADOS_HISTORICOS.txt");

    // Comandos SQL
    string insertDado, CodigoNeg, Data, Preco, linha;

    // Codigos escolhidos
    unordered_set<string> codigos;

    // insere eles no set
    codigos.insert("AALR3       ");
    codigos.insert("SAPR11F     ");
    codigos.insert("HYPE3       ");
    codigos.insert("JBSS3       ");
    codigos.insert("MLAS3       ");
    codigos.insert("MRFG3       ");
    codigos.insert("REIT11      ");
    codigos.insert("MNDL3       ");
    codigos.insert("CRPG5       ");
    codigos.insert("ABCB4       ");

    while (getline(Arquivo, linha)){
        // Coleta os dados da Ordem;
        CodigoNeg = linha.substr(12, 12);
        Data = linha.substr(2, 8);
        Preco = linha.substr(113, 13);
        
        // Verifica se a folha eh permitida
        if(codigos.count(CodigoNeg)){
            // Insere no DB
            insertDado =
                "INSERT INTO DadosHistoricos (\"CODIGO NEG\", DATA, PRECO) VALUES (\"" +
                CodigoNeg + "\", " + Data + ", " + Preco + ");";
            
            db->exec(insertDado, resultSql, "Erro ao inserir um dado histórico: ");
        }
    }
    return 0;
}