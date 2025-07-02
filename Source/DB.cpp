#include <iostream>
#include <sqlite3.h>
#include <map>
#include <vector>

using namespace std;

using Linha = map<string, string>;
using Tabela = vector<Linha>;

class DB {
private:
    static DB* instance;     // Ponteiro para o Singleton
    sqlite3* db;             // Conexão com o banco
    const char* name_db = "Source/DB.sqlite";

    // Construtor privado
    DB() {
        int result = sqlite3_open(name_db, &db);
        if (result != SQLITE_OK) {
            throw runtime_error(sqlite3_errmsg(db));
        }
    }

public:
    // Impede cópia
    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;

    // Método de acesso ao Singleton
    static DB* getInstance() {
        if (!instance) {
            instance = new DB();
        }
        return instance;
    }

    // Retorna ponteiro para a conexão
    sqlite3* getDB() const {
        return db;
    }

    ~DB() {
        sqlite3_close(db);
    }
};


int callback(void *Data, int QuantColumns, char** valores, char** colunas){
    Tabela* tabela = static_cast<Tabela *>(Data);
    Linha linha; 
    
    for(int i = 0; i < QuantColumns; i++){
        linha[colunas[i]] = valores[i];
    }
    
    tabela->push_back(linha);

    return 0;
}

// Inicialização do ponteiro estático
DB* DB::instance = nullptr;

class Inicializador {
public:
    Inicializador() {
        DB *Db = DB::getInstance();
        char *errorMsg = nullptr;
        
        // Cria a tabela de contas
        const char *createContas = "CREATE TABLE IF NOT EXISTS \"Contas\" ("
            "\"NOME\"	TEXT NOT NULL,"
            "\"CPF\"	TEXT NOT NULL UNIQUE,"
            "\"SENHA\"	TEXT NOT NULL,"
            "PRIMARY KEY(\"CPF\")"
        ")";
        bool result = sqlite3_exec(Db->getDB(), createContas, nullptr, 0, &errorMsg);
        if(result != SQLITE_OK){
            cerr << "Erro ao criar tabela de contas: " << errorMsg << "\n";
            sqlite3_free(errorMsg);
        }
        
        // Cria a tabale de carteiras
        const char *createCarteiras = "CREATE TABLE IF NOT EXISTS \"Carteiras\" ("
            "\"NOME\"	TEXT NOT NULL,"
            "\"CODIGO\"	TEXT NOT NULL,"
            "\"PERFIL\"	TEXT NOT NULL,"
            "\"CPF\"	TEXT NOT NULL,"
            "PRIMARY KEY(\"CODIGO\" AUTOINCREMENT),"
            "FOREIGN KEY(\"CPF\") REFERENCES \"Contas\"(\"CPF\")"
        ")";
        result = sqlite3_exec(Db->getDB(), createCarteiras, nullptr, 0, &errorMsg);
        if(result != SQLITE_OK){
            cerr << "Erro ao criar tabela de carteiras: " << errorMsg << "\n";
            sqlite3_free(errorMsg);
        }

        // Criar a tabela de ordens
        const char *createOrdens = "CREATE TABLE IF NOT EXISTS \"Ordens\" ("
            "\"CODIGO\"	TEXT NOT NULL,"
            "\"CODIGO NEG\"	TEXT NOT NULL,"
            "\"DATA\"	TEXT NOT NULL,"
            "\"PRECO\"	TEXT NOT NULL,"
            "\"QUANTIDADE\"	TEXT NOT NULL,"
            "FOREIGN KEY(\"CODIGO\") REFERENCES \"Carteiras\"(\"CODIGO\"),"
	        "PRIMARY KEY(\"CODIGO NEG\")"
        ")";
        result = sqlite3_exec(Db->getDB(), createOrdens, nullptr, 0, &errorMsg);
        if(result != SQLITE_OK){
            cerr << "Erro ao criar tabela de ordens: " << errorMsg << "\n";
            sqlite3_free(errorMsg);
        }
    }
};

static Inicializador _auto_exec;
