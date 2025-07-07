# include <fstream>

# include "DB.cpp"

int main(){
    // Configura os dados do DB;
    DB *db = DB::getInstance();
    Tabela *resultSql = new Tabela();

    // Abre o arquivo;
    ifstream Arquivo("Source/DADOS_HISTORICOS.txt");

    // Comandos SQL
    string insertDado, CodigoNeg, Data, Preco, linha;

    while (getline(Arquivo, linha)){
        // Coleta os dados da Ordem;
        CodigoNeg = linha.substr(12, 12);
        Data = linha.substr(2, 8);
        Preco = linha.substr(113, 13);
        // Insere no DB
        insertDado =
            "INSERT INTO DadosHistoricos (\"CODIGO NEG\", DATA, PRECO) VALUES (\"" +
            CodigoNeg + "\", " + Data + ", " + Preco + ");";
        db->exec(insertDado, resultSql, "Erro ao inserir um dado histórico: ");
    }
    return 0;
}