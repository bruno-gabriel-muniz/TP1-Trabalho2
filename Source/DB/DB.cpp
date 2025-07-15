#include "DB.hpp"

using namespace std;

int callback(void *Data, int QuantColumns, char** valores, char** colunas){
    Tabela* tabela = static_cast<Tabela *>(Data);
    Linha linha; 
    
    for(int i = 0; i < QuantColumns; i++){
        string nomeColuna = colunas[i] ? colunas[i] : "";
        string valor = valores[i] ? valores[i] : "";
        linha[nomeColuna] = valor;
    }
    
    tabela->push_back(linha);

    return 0;
}


// Construtor privado
DB::DB() {
        int result = sqlite3_open(name_db, &db);
        if (result != SQLITE_OK) {
            throw runtime_error(sqlite3_errmsg(db));
        }
}

// Método de acesso ao Singleton
DB* DB::getInstance() {
    if (!instance) {
        instance = new DB();
    }
    return instance;
}

// Retorna ponteiro para a conexão
sqlite3* DB::getDB() const {
    return db;
}

bool DB::exec(string sqlQueryS, Tabela *result, string errMsg){
    if (!instance) throw runtime_error("Instancia DB ainda não foi iniciada.");

    const char *sqlQuery = sqlQueryS.c_str();
    if(result) result->clear();
    char *errorMsg;

    bool exc_result = sqlite3_exec(db, sqlQuery, callback, result, &errorMsg);
    if(exc_result != SQLITE_OK){
        string sqlError = errorMsg ? string(errorMsg) : "Erro desconhecido.";
        sqlite3_free(errorMsg);
        throw runtime_error(errMsg + "sql_error: " + sqlError);
    }
    return exc_result;
};

DB::~DB() {
    sqlite3_close(db);
}


// Inicialização do ponteiro estático
DB* DB::instance = nullptr;

Inicializador::Inicializador() {
    DB *db = DB::getInstance();
    
    // Cria a tabela de contas
    string createContas = "CREATE TABLE IF NOT EXISTS \"Contas\" ("
        "\"NOME\"	TEXT NOT NULL,"
        "\"CPF\"	TEXT NOT NULL UNIQUE,"
        "\"SENHA\"	TEXT NOT NULL,"
        "PRIMARY KEY(\"CPF\")"
    ")";
    db->exec(createContas, nullptr, "Erro ao criar tabela de contas: ");
    
    // Cria a tabale de carteiras
    string createCarteiras = "CREATE TABLE IF NOT EXISTS \"Carteiras\" ("
        "\"NOME\"	TEXT NOT NULL,"
        "\"CODIGO\"	TEXT NOT NULL,"
        "\"PERFIL\"	TEXT NOT NULL,"
        "\"CPF\"	TEXT NOT NULL,"
        "PRIMARY KEY(\"CODIGO\"),"
        "FOREIGN KEY(\"CPF\") REFERENCES \"Contas\"(\"CPF\")"
    ")";
    db->exec(createCarteiras, nullptr, "Erro ao criar tabela de carteiras: ");

    // Criar a tabela de ordens
    string createOrdens = "CREATE TABLE IF NOT EXISTS \"Ordens\" ("
        "\"CODIGO\"	TEXT NOT NULL,"
        "\"CODIGO NEG\"	TEXT NOT NULL,"
        "\"DATA\"	TEXT NOT NULL,"
        "\"PRECO\"	TEXT NOT NULL,"
        "\"QUANTIDADE\"	TEXT NOT NULL,"
        "FOREIGN KEY(\"CODIGO\") REFERENCES \"Carteiras\"(\"CODIGO\"),"
        "PRIMARY KEY(\"CODIGO NEG\")"
    ")";
    db->exec(createOrdens, nullptr, "Erro ao criar tabela de ordens: ");

    // Criar a tabela dos dados históricos
    string createDadosHistoricos = "CREATE TABLE IF NOT EXISTS DadosHistoricos ("
        "\"CODIGO NEG\"	TEXT NOT NULL,"
        "\"DATA\"	TEXT NOT NULL,"
        "\"PRECO\"	TEXT NOT NULL"
    ")";
    db->exec(createDadosHistoricos, nullptr, "Erro ao criar tabela de ordens: ");
}
