# include "Source/DB.cpp"

int main(){
    // Inicia o DB;
    DB *db = DB::getInstance();

    // Executa os comandos;
    string deleteContas, deleteCarteiras, deleteOrdens;
    deleteContas = "DELETE FROM Contas;";
    db->exec(deleteContas, nullptr, "Erro ao limpar os dados do teste (Contas): ");
    deleteCarteiras = "DELETE FROM Carteiras;";
    db->exec(deleteContas, nullptr, "Erro ao limpar os dados do teste (Carteiras): ");
    deleteOrdens = "DELETE FROM Ordens;";
    db->exec(deleteContas, nullptr, "Erro ao limpar os dados do teste (Ordens): ");

    return 0;
}
