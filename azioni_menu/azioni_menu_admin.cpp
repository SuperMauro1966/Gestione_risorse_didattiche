#include <iostream>
#include <sqlite3.h>

void AccettaOEliminaProposta(const std::string& matricola, int risorsa, bool accetta) {
    sqlite3* db;
    int rc = sqlite3_open("./db/risorse_didattiche.db", &db);
    if (rc) {
        std::cerr << "Impossibile aprire il database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string sql;
    if (accetta) {
        sql = "INSERT INTO tb_elenco_risorse_disponibili (ID_risorse, matricola) VALUES (:ID_RISORSE, :MATRICOLA);";
    } else {
        sql = "DELETE FROM tb_elenco_risorse_disponibili WHERE ID_risorse = :ID_RISORSE AND matricola = :MATRICOLA;";
    }

    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Errore nella preparazione della query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    sqlite3_bind_int(stmt, 1, risorsa);
    sqlite3_bind_text(stmt, 2, matricola.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Errore nell'esecuzione della query: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    if (accetta) {
        std::cout << "La risorsa proposta è stata accettata." << std::endl;
    } else {
        std::cout << "La proposta di risorsa è stata eliminata." << std::endl;
    }
}

void MostraRisorseProposte() {
    sqlite3* db;
    int rc = sqlite3_open("./db/risorse_didattiche.db", &db);
    if (rc) {
        std::cerr << "Impossibile aprire il database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::string sql = "SELECT ID_risorse, matricola FROM tb_elenco_risorse_disponibili;";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Errore nella preparazione della query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        std :: string matricola;
        int risorsa = sqlite3_column_int(stmt, 0);
        const char* matricola = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::cout << "ID Risorsa: " << risorsa << ", Matricola: " << matricola << std::endl;
        std::cout << "Accettare (a) o eliminare (e) la proposta di risorsa? ";
        char scelta;
        std::cin >> scelta;
        if (scelta == 'a') {
            AccettaOEliminaProposta(matricola, risorsa, true);
        } else if (scelta == 'e') {
            AccettaOEliminaProposta(matricola, risorsa, false);
        } else {
            std::cerr << "Scelta non valida. Nessuna azione eseguita." << std::endl;
        }
    }

