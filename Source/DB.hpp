#pragma once

#include <iostream>
#include <sqlite3.h>
#include <map>
#include <vector>

using namespace std;

using Linha = map<string, string>;
using Tabela = vector<Linha>;

int callback(void *Data, int QuantColumns, char** valores, char** colunas);


class DB {
private:
    static DB* instance;     // Ponteiro para o Singleton
    sqlite3* db;             // Conexão com o banco
    const char* name_db = "DB.sqlite";

    // Construtor privado
    DB();

public:
    // Impede cópia
    DB(const DB&) = delete;
    DB& operator=(const DB&) = delete;

    // Método de acesso ao Singleton
    static DB* getInstance();

    // Retorna ponteiro para a conexão
    sqlite3* getDB() const;

    bool exec(string sqlQueryS, Tabela *result, string errMsg);

    ~DB();
};

class Inicializador {
public:
    Inicializador();
};

static Inicializador _auto_exec;
